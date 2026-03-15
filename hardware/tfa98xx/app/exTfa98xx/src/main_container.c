#include <assert.h>
#include <string.h>
#if defined(WIN32) || defined(_X64)
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <NXP_I2C.h>

#include <pthread.h>

#define LOG_TAG "exTfa98xx"
#include <cutils/log.h>

#ifndef LOGD
#define LOGD(...) ALOGD(__VA_ARGS__)
#endif

#ifndef WIN32
#include <inttypes.h>
#endif
#include "tfa.h" /* top tfa interface */
#include "tfaContUtil.h"
#include "tfa_container.h"
#include "dbgprint.h"
#include "tfaOsal.h" /* tfaReadFile */
#include "tfa98xxLiveData.h"
#include "Tfa98API.h"
#include "tfa_service.h"
#include "tfa98xxCalibration.h"
#include "tfa98xx_cust.h"
#include "exTfa98xx.h"

#ifndef WIN32
#define Sleep(ms) usleep((ms)*1000)
#define _GNU_SOURCE   /* to avoid link issues with sscanf on NxDI? */
#endif

#define MAX_DEVICES 4

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Forward declarations of helper functions */
static int get_impedance(int dev_idx, float *imp);
static int find_live_data_item_index(Tfa98xx_handle_t handle, const char *item_name);

int load_container_file(char *fname,  nxpTfaContainer_t **buffer) {
	int size;

	size = tfaReadFile(fname, (void**) buffer); //mallocs file buffer

	if ( size==0 )
		printf("error reading %s\n", fname);

	return size;
}

/*------------------------------------------------------------------------------
 * Improved recordLiveData: obtains the index of the requested live data item
 * per device, then reads and prints the value for each device.
 *------------------------------------------------------------------------------*/
enum tfa_error recordLiveData(char* item_name) {
	Tfa98xx_Error_t err = Tfa98xx_Error_Ok;
	Tfa98xx_handle_t handles[MAX_DEVICES];
	unsigned char slaveAddress;
	int i, maxdev = tfa98xx_cnt_max_device();
	int item_index[MAX_DEVICES];          /* index of the item for each device */
	float live_data[MEMTRACK_MAX_WORDS] = {0};
	int nr_of_items;

	if (maxdev > MAX_DEVICES)
		maxdev = MAX_DEVICES;

	/* Open all devices */
	for (i = 0; i < maxdev; i++) {
		tfaContGetSlave(i, &slaveAddress);
		err = Tfa98xx_Open(slaveAddress * 2, &handles[i]);
		if (err != Tfa98xx_Error_Ok) {
			ALOGE("Failed to open device %d (addr 0x%02x)", i, slaveAddress);
			goto error_close;
		}
	}

	/* For each device, find the index of the requested live data item */
	for (i = 0; i < maxdev; i++) {
		item_index[i] = find_live_data_item_index(handles[i], item_name);
		if (item_index[i] < 0) {
			ALOGE("Item '%s' not found for device %d", item_name, i);
			err = Tfa98xx_Error_Bad_Parameter;
			goto error_close;
		}
	}

	/* Enable live data streaming */
	err = tfa98xx_set_live_data(handles);
	if (err != Tfa98xx_Error_Ok) {
		ALOGE("tfa98xx_set_live_data failed: %d", err);
		goto error_close;
	}

	/* Read and print the live data value for each device */
	for (i = 0; i < maxdev; i++) {
		tfaContGetSlave(i, &slaveAddress);
		err = tfa98xx_get_live_data(handles, i, live_data, &nr_of_items);
		if (err != Tfa98xx_Error_Ok) {
			ALOGE("tfa98xx_get_live_data failed for device %d: %d", i, err);
			goto error_close;
		}
		if (item_index[i] < nr_of_items) {
			printf("%s [0x%02x]: %f\n", item_name, slaveAddress, live_data[item_index[i]]);
		} else {
			ALOGE("Item index %d out of range (max %d) for device %d",
			      item_index[i], nr_of_items-1, i);
		}
	}

error_close:
	for (i = 0; i < maxdev; i++) {
		if (handles[i] != -1)
			Tfa98xx_Close(handles[i]);
	}
	return (enum tfa_error)err;
}

/*------------------------------------------------------------------------------
 * Helper: find the index of a named live data item for a given device handle.
 * Returns the index (>=0) on success, -1 on failure.
 *------------------------------------------------------------------------------*/
static int find_live_data_item_index(Tfa98xx_handle_t handle, const char *item_name) {
	char buffer[256];
	char *item;
	int idx = 0;

	buffer[0] = '\0';
	/* Get the comma-separated list of live data items for this device.
	 * Note: tfa98xx_get_live_data_items() expects an array of handles,
	 * but we only care about the first device. We'll pass a temporary array.
	 */
	Tfa98xx_handle_t handles[2] = {handle, -1};
	Tfa98xx_Error_t err = tfa98xx_get_live_data_items(handles, 0, buffer);
	if (err != Tfa98xx_Error_Ok) {
		ALOGE("tfa98xx_get_live_data_items failed: %d", err);
		return -1;
	}

	/* Tokenize the string (it is comma-separated) */
	item = strtok(buffer, ",");
	while (item) {
		if (strstr(item, item_name) != NULL) {
			return idx;
		}
		idx++;
		item = strtok(NULL, ",");
	}
	return -1;
}

/*------------------------------------------------------------------------------
 * Replacement for the original tfa_enable function.
 * Uses the exTfa98xx API to control NXP TFA98xx devices.
 *
 * Parameters:
 *   ctx - pointer to a context structure (must contain at least):
 *         byte 0:    enabled flag (1 = on, 0 = off)
 *         float at offset 100: impedance value (initialized to -1.0)
 *         int at offset 108:   audio mode (profile)
 *         int at offset 112:   volume step
 *         int at offset 116:   device index (default 13, overwritten later)
 *         int at offset 120:   flag (0 = attenuation only, non-zero = volume step)
 *   on  - non-zero to turn on, zero to turn off
 *
 * Returns 0 on success, non-zero on error.
 *------------------------------------------------------------------------------*/
int tfa_enable(unsigned char *ctx, int on) {
	int ret = 0;
	float impedance_val;
	int mode;
	int volume_step;
	int some_flag;
	int dev_idx;
	int i;

	/* Extract fields from the context structure */
	int is_on = (ctx[0] != 0);
	mode = *((int *)ctx + 27);          // offset 108
	float *imp_ptr = (float *)(ctx + 100); // offset 100
	volume_step = *((int *)ctx + 28);   // offset 112
	dev_idx = *((int *)ctx + 29);       // offset 116
	some_flag = *((int *)ctx + 30);     // offset 120

	ALOGD("[NXP] %s: turning tfa %s (dev_idx=%d)\n", "tfa_enable", on ? "on" : "off", dev_idx);

	if (on) {
		// ----- TURN ON -----
		static int calibrated = 0;          // has cold boot been done?
		static int prev_mode = -1;           // last used mode
		static int enable_cnt = 0;
		static int coldboot_cnt = 0;
		static int coldboot_flag = 0;

		if (is_on && mode == prev_mode) {
			ALOGD("[NXP] %s: Tfa is already turned on", "tfa_enable");
			return 0;
		}

		enable_cnt++;
		ALOGD("[NXP] %s: tfa_log_enable_cnt = %d\n", "tfa_enable", enable_cnt);

		if (!calibrated) {
			// ----- COLD BOOT -----
			coldboot_cnt++;
			ALOGD("[NXP] %s: cold boot\n", "tfa_enable");
			ALOGD("[NXP] %s: tfa_log_coldboot_cnt = %d\n", "tfa_enable", coldboot_cnt);
			ALOGD("[NXP] %s: ic stable time 80 ms\n", "tfa_enable");
			usleep(80 * 1000);

			// Run calibration (exTfa98xx_init loads container and calibrates)
			ret = exTfa98xx_init();
			if (ret != 0) {
				ALOGE("[NXP] %s: calibration failed, retrying...", "tfa_enable");
				usleep(1000);
				usleep(1000);
				ret = exTfa98xx_init();
				if (ret != 0) {
					ALOGE("[NXP] %s: calibration failed for second time", "tfa_enable");
					return ret;
				}
			}
			calibrated = 1;

			// After calibration, turn on the speaker (exTfa98xx_init leaves device stopped)
			ret = exTfa98xx_speakeron(mode);
			if (ret != 0) {
				ALOGE("[NXP] %s: speakeron after calibration failed", "tfa_enable");
				return ret;
			}

			// If impedance not yet set, read it (using the device index from context)
			if (*imp_ptr == -1.0f) {
				if (get_impedance(dev_idx, &impedance_val) == 0) {
					*imp_ptr = impedance_val;
					ALOGD("[NXP] %s: impedance = %f", "tfa_enable", impedance_val);
				} else {
					*imp_ptr = 0.0f;
					ALOGE("[NXP] %s: get impedance error ! impedance = %f", "tfa_enable", 0.0f);
				}
			}

			ctx[0] = 1;
			prev_mode = mode;
			coldboot_flag = 1;
		} else {
			// ----- WARM BOOT -----
			ALOGD("[NXP] %s: warm boot\n", "tfa_enable");
			ALOGD("[NXP] %s: ic stable time 80 ms\n", "tfa_enable");
			usleep(80 * 1000);

			ALOGD("[NXP] %s: Tfa mode would be switched. prev = %d, current = %d",
			      "tfa_enable", prev_mode, mode);

			if (!coldboot_flag) {
				coldboot_flag = 1;
				coldboot_cnt++;
				ALOGD("[NXP] %s: check cold startup condition\n", "tfa_enable");
			}

			// Turn on speaker with the requested mode
			ret = exTfa98xx_speakeron(mode);
			if (ret != 0) {
				ALOGE("[NXP] %s: speakeron failed, retrying...", "tfa_enable");
				usleep(100 * 1000);   // 100 ms
				ret = exTfa98xx_speakeron(mode);
				if (ret != 0) {
					ALOGE("[NXP] %s: speakeron failed for second time", "tfa_enable");
					return ret;
				}
			}

			// If impedance not yet set, read it
			if (*imp_ptr == -1.0f) {
				if (get_impedance(dev_idx, &impedance_val) == 0) {
					*imp_ptr = impedance_val;
					ALOGD("[NXP] %s: impedance = %f", "tfa_enable", impedance_val);
				} else {
					*imp_ptr = 0.0f;
					ALOGE("[NXP] %s: get impedance error ! impedance = %f", "tfa_enable", 0.0f);
				}
			}

			ctx[0] = 1;
			prev_mode = mode;
		}

		// ----- SET VOLUME (common after both cold and warm boot) -----
		int maxdev = tfa98xx_cnt_max_device();
		int vsteps[MAX_DEVICES];
		for (i = 0; i < maxdev && i < MAX_DEVICES; i++) {
			vsteps[i] = volume_step;
		}

		if (some_flag) {
			ALOGD("[NXP] %s: tfaVolume : %d", "tfa_enable", volume_step);
		} else {
			ALOGD("[NXP] %s: tfaVolume : %d only attenuation", "tfa_enable", volume_step);
		}
		if (tfa_start(mode, vsteps) != tfa_error_ok) {
			ALOGE("[NXP] %s: failed to set volume step", "tfa_enable");
			// Non-fatal, continue
		}
	} else {
		// ----- TURN OFF -----
		ALOGD("[NXP] %s: turning tfa off", "tfa_enable");
		if (!is_on) {
			ALOGD("[NXP] %s: Tfa is already turned off", "tfa_enable");
			return 0;
		}
		ctx[0] = 0;
		exTfa98xx_speakeroff();
		ret = 0;
	}

	ALOGD("[NXP] %s: end\n", "tfa_enable");
	return ret;
}

/*------------------------------------------------------------------------------
 * Helper: get impedance for a given device index using live data.
 * Returns 0 on success, -1 on error.
 *------------------------------------------------------------------------------*/
static int get_impedance(int dev_idx, float *imp) {
	Tfa98xx_Error_t err;
	Tfa98xx_handle_t handle = -1;
	unsigned char slaveAddress;
	float live_data[MEMTRACK_MAX_WORDS] = {0};
	int nr_of_items = 0;
	int item_idx;

	if (dev_idx < 0 || dev_idx >= tfa98xx_cnt_max_device())
		return -1;

	tfaContGetSlave(dev_idx, &slaveAddress);
	err = Tfa98xx_Open(slaveAddress * 2, &handle);
	if (err != Tfa98xx_Error_Ok) {
		ALOGE("get_impedance: cannot open device %d (addr 0x%02x)", dev_idx, slaveAddress);
		return -1;
	}

	/* Find the index of the "Impedance" live data item */
	item_idx = find_live_data_item_index(handle, "Impedance");
	if (item_idx < 0) {
		ALOGE("get_impedance: 'Impedance' not found for device %d", dev_idx);
		Tfa98xx_Close(handle);
		return -1;
	}

	/* Enable live data and read current values */
	Tfa98xx_handle_t handles[2] = {handle, -1};
	err = tfa98xx_set_live_data(handles);
	if (err != Tfa98xx_Error_Ok) {
		ALOGE("get_impedance: tfa98xx_set_live_data failed: %d", err);
		Tfa98xx_Close(handle);
		return -1;
	}

	err = tfa98xx_get_live_data(handles, 0, live_data, &nr_of_items);
	if (err != Tfa98xx_Error_Ok || item_idx >= nr_of_items) {
		ALOGE("get_impedance: tfa98xx_get_live_data failed or index out of range");
		Tfa98xx_Close(handle);
		return -1;
	}

	*imp = live_data[item_idx];
	Tfa98xx_Close(handle);
	return 0;
}

/*------------------------------------------------------------------------------
 * Context layout offsets (used by tfa_device_open and function implementations)
 *------------------------------------------------------------------------------*/
#define CTX_ENABLED         0   // byte: 1 = on, 0 = off
#define CTX_UNKNOWN1         4   // int
#define CTX_UNKNOWN2         8   // 16 bytes (two qwords) – keep zero
#define CTX_UNKNOWN3        24   // 12 bytes (three ints) – keep zero
#define CTX_UNKNOWN4        36   // 16 bytes (two qwords) – keep zero
#define CTX_UNKNOWN5        52   // ... (further zeros up to offset 96)
#define CTX_BYTE_96         96   // byte (unknown)
#define CTX_IMPEDANCE      100   // float: measured impedance
#define CTX_MODE           108   // int: current audio mode (profile)
#define CTX_VOLUME         112   // int: volume step
#define CTX_DEVICE_INDEX   116   // int: device index (default 13, overwritten later)
#define CTX_FLAG_120       120   // int: 0 = attenuation only, non-zero = volume step
#define CTX_BYTE_124       124   // byte (unknown)
#define CTX_FUNC_TABLE     128   // 6 function pointers (each 4 bytes on 32-bit)

/*------------------------------------------------------------------------------
 * Implementations of the function pointers stored in the context.
 * All take the context pointer as first argument.
 *------------------------------------------------------------------------------*/

static int tfa_getImpedance_impl(unsigned char *ctx, float *imp) {
	int dev_idx = *(int*)(ctx + CTX_DEVICE_INDEX);
	ALOGD("tfa_getImpedance: dev_idx=%d", dev_idx);
	return get_impedance(dev_idx, imp);
}

static int tfa_calibrateImpedance_impl(unsigned char *ctx, int flag) {
	ALOGD("tfa_calibrateImpedance: flag=%d", flag);
	return exTfa98xx_init();
}

static int tfa_setvolumestep_impl(unsigned char *ctx, int left, int right) {
	int mode = *(int*)(ctx + CTX_MODE);
	int maxdev = tfa98xx_cnt_max_device();
	int vsteps[MAX_DEVICES];
	int i;

	ALOGD("tfa_setvolumestep: mode=%d, left=%d, right=%d", mode, left, right);
	for (i = 0; i < maxdev && i < MAX_DEVICES; i++)
		vsteps[i] = left;

	*(int*)(ctx + CTX_VOLUME) = left;

	return (tfa_start(mode, vsteps) == tfa_error_ok) ? 0 : -1;
}

static int tfa_setvolumeattenuation_impl(unsigned char *ctx, int left, int right) {
	int mode = *(int*)(ctx + CTX_MODE);
	int maxdev = tfa98xx_cnt_max_device();
	int vsteps[MAX_DEVICES];
	int i;

	ALOGD("tfa_setvolumeattenuation: mode=%d, left=%d, right=%d", mode, left, right);
	for (i = 0; i < maxdev && i < MAX_DEVICES; i++)
		vsteps[i] = left;

	*(int*)(ctx + CTX_VOLUME) = left;

	return (tfa_start(mode, vsteps) == tfa_error_ok) ? 0 : -1;
}

static int tfa_mute_impl(unsigned char *ctx, int mute) {
	ALOGD("tfa_mute: mute=%d", mute);
	if (mute) {
		tfa_stop();
	} else {
		int mode = *(int*)(ctx + CTX_MODE);
		int vol = *(int*)(ctx + CTX_VOLUME);
		int maxdev = tfa98xx_cnt_max_device();
		int vsteps[MAX_DEVICES];
		int i;
		for (i = 0; i < maxdev && i < MAX_DEVICES; i++)
			vsteps[i] = vol;
		tfa_start(mode, vsteps);
	}
	return 0;
}

/*------------------------------------------------------------------------------
 * Replacement for tfa_device_open – initializes the context structure.
 *------------------------------------------------------------------------------*/
int tfa_device_open(unsigned char *ctx) {
	ALOGD("[NXP] %s %s: begin", "[MAR 28, 2017]", "tfa_device_open");

	// Clear the entire context (size at least 152 bytes, we'll zero 160 for safety)
	memset(ctx, 0, 160);

	// Set default values according to original disassembly
	*(int*)(ctx + 4) = 0;
	*(ctx + 96) = 0;
	*(int*)(ctx + 108) = 0;                 // default mode (Audio_Mode_Music_Normal = 0)
	*(float*)(ctx + 100) = -1.0f;            // impedance = -1.0
	*(ctx + 124) = 0;
	*(int*)(ctx + 116) = 13;                 // default device index (may be overwritten later)

	// Function pointers (standard C calling convention)
	*(void**)(ctx + 128) = (void*)tfa_enable;
	*(void**)(ctx + 132) = (void*)tfa_getImpedance_impl;
	*(void**)(ctx + 136) = (void*)tfa_calibrateImpedance_impl;
	*(void**)(ctx + 140) = (void*)tfa_setvolumestep_impl;
	*(void**)(ctx + 144) = (void*)tfa_setvolumeattenuation_impl;
	*(void**)(ctx + 148) = (void*)tfa_mute_impl;

	ALOGD("[NXP] %s: end", "tfa_device_open");
	return 0;
}

/*------------------------------------------------------------------------------
 * Main function (kept as originally provided, but with fixed recordLiveData)
 *------------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
	enum tfa_error err = tfa_error_ok;
	nxpTfaContainer_t *cntbuf;
	int length;
	int i = 0, j = 0, vsteps[MAX_DEVICES]={0,0,0,0};
	int profile;
	unsigned char  tfa98xxI2cSlave; // for i2c address

	char target[FILENAME_MAX];

	printf("Starting application.\n");

	/* Get the container file from command line */
	if ( argc < 2 ) {
		printf("Please supply a container file as command line argument.\n");
		return 0;
	} else if ( argc < 3 ) {
		strcpy(target, "dummy"); /* no target specified, use default*/
	} else {
		strncpy(target, argv[2], sizeof(target)); /* target specified */
	}
	//	tfa_cnt_verbose( argc>3);

	/* load the container file into the memory */
	length = load_container_file(argv[1], &cntbuf);
	if (length ==0)  { // read params
		fprintf(stderr, "Load container failed\n");
		return 1;
	} else {
		printf("Loaded container file %s.\n", argv[1]);
	}

	/* pass the container file to the tfa */
	tfa_load_cnt( (void*) cntbuf, length);

	/* open the target device */
	if (NXP_I2C_Open(target) == -1 ) { /* use input device */
		fprintf(stderr, "Could not open target device:%s.\n The second argument can be used to specify a device\n.", target);
		return 1;
	}
	NXP_I2C_Trace(0);

	/* Make sure device family type is set */
	if (tfa98xx_get_cnt() != NULL) {
		//tfa_soft_probe_all(tfa98xx_get_cnt());
		if( tfa_probe_all(tfa98xx_get_cnt()) != Tfa98xx_Error_Ok ) {
			goto error_exit;
		}
	}

	/* print container files details */
	// for debugging use: tfaContShowContainer();
	for (i=0; i < tfa98xx_cnt_max_device(); i++ ) {
		tfaContGetSlave(i, &tfa98xxI2cSlave); /* get device I2C address */
		printf("\tFound Device[%d]: %s at 0x%02x.\n", i, tfaContDeviceName(i), tfa98xxI2cSlave);
		for (j=0; j < tfaContMaxProfile(i); j++ )
			printf("\t\tProfile [%d]: %s, %d vsteps.\n", j, tfaContProfileName(i,j), tfacont_get_max_vstep(i,j));
	}

	printf ("Select a profile [0-%d]: ", (tfaContMaxProfile(0)-1));
	j = scanf ("%d", &profile);

	/* always load vstep[0] */
	err = tfa_start(profile, vsteps);

	/* loop up through all vsteps if > 0 */
	for(i=0;i<tfacont_get_max_vstep(0,profile);i++){
		for(j=0;j<tfa98xx_cnt_max_device();j++) /* put all to same vstep */
			vsteps[j]=i;
		err = tfa_start(profile, vsteps);
		if ( err!=tfa_error_ok)
			goto error_exit;
	}

	/* loop down through all vsteps if > 0 */
	for(i=tfacont_get_max_vstep(0,profile)-1;i>0;i--){
		for(j=0;j<tfa98xx_cnt_max_device();j++) /* put all to same vstep */
			vsteps[j]=i;
		err = tfa_start(profile, vsteps);
		if ( err!=tfa_error_ok)
			goto error_exit;
	}

	if (argc >= 4) {
		err = recordLiveData(argv[3]); /* third argument is the livedata item to be tracked */
		if (err != tfa_error_ok)
			goto error_exit;
	}

	printf ("Play music at 48kHz. Do you want to quit? [type number/char to quit] ");
	j = scanf ("%d", &i);
	if(!j) {
		/**** Erroneous input, get rid of it and retry! */
		scanf ("%*[^\n]");
	}

error_exit:
	if ( err!=tfa_error_ok) {
		printf("an error occured, code:%d\n",err );
	}
	printf ("\nPowering down.\n");

	tfa_stop();
	tfa_deinit();

	NXP_I2C_Close();

	return 0;
}

/*------------------------------------------------------------------------------
 * Calibration routine – runs calibration on all devices.
 *------------------------------------------------------------------------------*/
static int calibrationOnce(void)
{
	Tfa98xx_Error_t error = Tfa98xx_Error_Ok;
	unsigned char tfa98xxI2cSlave = 0;
	int maxdev = tfa98xx_cnt_max_device(), i = 0;
	Tfa98xx_handle_t handle;
	int ret = 0;

	if ( maxdev <= 0 ) {
		ALOGE("Please provide/load container file for calibration.");
		ret = -1;
		goto EXIT;
	}

	for (i=0; i < maxdev; i++ ) {
		tfaContGetSlave(i, &tfa98xxI2cSlave); /* get device I2C address */
		ALOGD("%s: Found Device[%d]: %s at 0x%02x.", __func__, i, tfaContDeviceName(i), tfa98xxI2cSlave);

		error = Tfa98xx_Open(tfa98xxI2cSlave*2, &handle);
		if (error != Tfa98xx_Error_Ok) {
			ALOGE("last status: %d (%s)", error, Tfa98xx_GetErrorString(error));
			ret = error;
			continue;
		}

		//run calibration (with profile 0)
		error = tfa98xxCalibration(&handle, i, 1, 0);
		if ( error!=Tfa98xx_Error_Ok ) {
			ALOGE("Calibration failed: error %d (%s)", error, Tfa98xx_GetErrorString(error));
			ret = error;
		}

		Tfa98xx_Close(handle);
	}
EXIT:
	return ret;
}

/*------------------------------------------------------------------------------
 * Public API functions (with mutex protection)
 *------------------------------------------------------------------------------*/
int exTfa98xx_check_tfaopen(void)
{
	int ret = 0;
	ALOGD("%s into\n", __func__);
	pthread_mutex_lock(&mutex);

	nxpTfaContainer_t *cntbuf =  tfa98xx_get_cnt();
	ret = (cntbuf != NULL) ? 1 : 0;

	ALOGD("%s out\n", __func__);
	pthread_mutex_unlock(&mutex);
	return ret;
}

int exTfa98xx_init()
{
	Tfa98xx_Error_t err = Tfa98xx_Error_Ok;
	nxpTfaContainer_t *cntbuf;
	int length;
	int ret = 0;

	ALOGD("%s into\n", __func__);
	pthread_mutex_lock(&mutex);

	/* open the target device */
	if (NXP_I2C_Open(TFA_I2CDEVICE) == -1 ) {
		ALOGE("Could not open target device:%s.", TFA_I2CDEVICE);
		ret = -1;
		goto EXIT;
	}

	NXP_I2C_Trace(0);

	/* load the container file into the memory */
	length = load_container_file(LOCATION_FILES CNT_FILENAME, &cntbuf);
	if (length == 0)  {
		ALOGE("Load container file %s failed.", LOCATION_FILES CNT_FILENAME);
		ret = -1;
		goto EXIT;
	}

	/* pass the container file to the tfa */
	tfa_load_cnt( (void*) cntbuf, length);

	ALOGE("will call calibration function\n");
	err = calibrationOnce();
	if (err) {
		NXP_I2C_Close();
		tfa_deinit();
		free(cntbuf);
		ret = -1;
		goto EXIT;
	}

	ALOGE("will stop tfa\n");
	tfa_stop();

EXIT:
	ALOGD("%s out\n", __func__);
	pthread_mutex_unlock(&mutex);
	return ret;
}

int exTfa98xx_deinit()
{
	int ret = 0;
	nxpTfaContainer_t *cntbuf =  tfa98xx_get_cnt();

	ALOGD("%s into\n", __func__);
	pthread_mutex_lock(&mutex);

	NXP_I2C_Close();
	tfa_deinit();

	if (cntbuf != NULL) {
		free(cntbuf);
	}

	ALOGD("%s out\n", __func__);
	pthread_mutex_unlock(&mutex);
	return ret;
}

/*------------------------------------------------------------------------------
 * Set samplerate – currently a placeholder.  If needed, store the value in a
 * global variable and use it in exTfa98xx_speakeron to select the profile.
 *------------------------------------------------------------------------------*/
void exTfa98xx_setSamplerate(int samplerate)
{
	ALOGV("%s into samplerate = %d", __func__, samplerate);
	pthread_mutex_lock(&mutex);
	// TODO: store samplerate in a global if needed for profile selection
	// (exTfa98xx_speakeron already receives a mode argument, so this may be unused)
	pthread_mutex_unlock(&mutex);
}

int exTfa98xx_speakeron(exTfa98xx_audio_mode_t mode)
{
	enum tfa_error err;
	int vsteps[MAX_DEVICES]={0,0,0,0};
	int ret = 0;

	ALOGD("%s into\n", __func__);
	pthread_mutex_lock(&mutex);

	/* always load vstep[0] */
	err = tfa_start((int)mode, vsteps);
	if (tfa_error_ok != err) {
		ALOGE("tfa_start failed, code:%d", err);
		tfa_stop();
		ret = -1;
	}

	ALOGD("%s out\n", __func__);
	pthread_mutex_unlock(&mutex);
	return ret;
}

void exTfa98xx_speakeroff()
{
	ALOGD("%s into\n", __func__);
	pthread_mutex_lock(&mutex);

	tfa_stop();

	ALOGD("%s out\n", __func__);
	pthread_mutex_unlock(&mutex);
}
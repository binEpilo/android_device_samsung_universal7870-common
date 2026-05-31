/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RADIOCONFIG_V1_1_H__
#define __RADIOCONFIG_V1_1_H__

#include <telephony/ril.h>

#define MAX_LOGICAL_MODEM_SIZE  4

typedef struct {
    /**
     * Logical modem ID.
     */
    uint8_t modemId;
} RIL_ModemInfo;

typedef struct {
    /**
     * maxActiveData defines how many logical modems can have
     * PS attached simultaneously. For example, for L+L modem it
     * should be 2.
     */
    uint8_t maxActiveData;
    /**
     * maxActiveData defines how many logical modems can have
     * internet PDN connections simultaneously. For example, for L+L
     * DSDS modem 1, and for DSDA modem 2.
     */
    uint8_t maxActiveInternetData;
    /**
     * Whether modem supports both internet PDN up so
     * that we can do ping test before tearing down the
     * other one.
     */
    bool isInternetLingeringSupported;
    /**
     * List of logical modem information.
     */
    uint32_t len_logicalModemList;
    RIL_ModemInfo logicalModemList[MAX_LOGICAL_MODEM_SIZE];
} RIL_PhoneCapability;

/**
 *
 * RIL_REQUEST_SET_PREFERRED_DATA_MODEM
 *
 * Set preferred data modem ID.
 * In a multi-SIM device, notify modem layer which logical modem will be used primarily
 * for data. It helps modem with resource optimization and decisions of what data connections
 * should be satisfied.
 *
 * @param serial Serial number of request.
 * @param modem ID the logical modem ID, which should match one of modem IDs returned
 * from getPhoneCapability().
 *
 * Response callback is IRadioConfigResponse.setPreferredDataModemResponse()
 *
 * Valid errors:
 * RadioError:NONE (SUCCESS)
 * RadioError:RADIO_NOT_AVAILABLE, NO_MEMORY, INTERNAL_ERR, MODEM_ERR, INVALID_ARGUMENTS
 */
#define RIL_REQUEST_SET_PREFERRED_DATA_MODEM 204

/**
 * RIL_REQUEST_GET_PHONE_CAPABILITY
 *
 * Request current phone capability.
 *
 * "data" is NULL
 *
 * "response" is a RIL_PhoneCapability
 *
 * Valid errors:
 *
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 *
 */
#define RIL_REQUEST_GET_PHONE_CAPABILITY 206

/**
 * Set modems configurations by specifying the number of live modems (i.e modems that are
 * enabled and actively working as part of a working telephony stack).
 *
 * Example: this interface can be used to switch to single/multi sim mode by specifying
 * the number of live modems as 1, 2, etc
 *
 * Note: by setting the number of live modems in this API, that number of modems will
 * subsequently get enabled/disabled
 *
 * @param serial serial number of request.
 * @param modemsConfig ModemsConfig object including the number of live modems
 *
 * Response callback is IRadioResponse.setModemsConfigResponse()
 */
#define RIL_REQUEST_SET_MODEMS_CONFIG 207

/**
 * Get modems configurations. This interface is used to get modem configurations
 * which includes the number of live modems (i.e modems that are
 * enabled and actively working as part of a working telephony stack)
 *
 * Note: in order to get the overall number of modems available on the phone,
 * refer to getPhoneCapability API
 *
 * @param serial Serial number of request.
 *
 * Response callback is IRadioResponse.getModemsConfigResponse() which
 * will return <@1.1::ModemsConfig>.
 */
#define RIL_REQUEST_GET_MODEMS_CONFIG 208

#endif // __RADIOCONFIG_V1_1_H__

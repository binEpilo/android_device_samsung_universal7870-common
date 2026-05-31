/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef ANDROID_RIL_EXT_H
#define ANDROID_RIL_EXT_H 1

#ifdef __cplusplus
extern "C" {
#endif

/** Used by RIL_REQUEST_DIAL_WITH_CALL_TYPE */
typedef struct {
    char * address;
    int clir;
            /* (same as 'n' paremeter in TS 27.007 7.7 "+CLIR"
             * clir == 0 on "use subscription default value"
             * clir == 1 on "CLIR invocation" (restrict CLI presentation)
             * clir == 2 on "CLIR suppression" (allow CLI presentation)
             */
    RIL_UUS_Info *  uusInfo;    /* NULL or Pointer to User-User Signaling Information */
    int callType;
} RIL_Dial_Ext;


typedef struct
{
  RIL_AppType      app_type;
  RIL_AppState     app_state;
  RIL_PersoSubstate perso_substate; /* applicable only if app_state ==
                                       RIL_APPSTATE_SUBSCRIPTION_PERSO */
  char             *aid_ptr;        /* null terminated string, e.g., from 0xA0, 0x00 -> 0x41,
                                       0x30, 0x30, 0x30 */
  char             *app_label_ptr;  /* null terminated string */
  int              pin1_replaced;   /* applicable to USIM, CSIM & ISIM */
  RIL_PinState     pin1;
  RIL_PinState     pin2;

  // S.LSI Extension
  int              pin1_remain_count;
  int              puk1_remain_count;
  int              pin2_remain_count;
  int              puk2_remain_count;
} RIL_AppStatus_Ext;

/**
 * Sim PhoneBook
 */
typedef enum {
    PB_EN,      /* 0x0 Emergency Number */
    PB_ADN_2G,  /* 0x1 2G phone book */
    PB_FDN,     /* 0x2 Fixed Dialing Number */
    PB_BDN,     /* 0x3 Barred Dialing Number */
    PB_SDN,     /* 0x4 Service Dialing Number */
    PB_LDN,     /* 0x5 Last Dialed Number */
    PB_ICI,     /* 0x6 Incoming Call INformation */
    PB_OCI,     /* 0x7 Outgoing Call Information */
    PB_MSISDN,  /* 0x8 Own numbers (MSISDMs) list */
    PB_ADN_3G,  /* 0x9 3G phone book */
    PB_AAS,     /* 0xA Additional NUmber Alpha String */
    PB_GAS,     /* 0xB Grouping Information Alpha String */
    PB_MBDN,    /* 0xC Mailbox Dialing Numbers */
}PB_TYPE;

typedef enum {
    UNKNOWN_TYPE,
    INTERNATIONAL,
    NATIONAL,
    NETWORK,
    DEDICATE,
}PB_NUMBER_TYPE;

typedef enum {
    ASCII = 1,
    GSM7BIT,
    UCS2,
    HEX,
}PB_TEXT_TYPE;

typedef enum {
    NAME = 1,
    NUMBER,
    ANR,
    EMAIL,
    SNE,
    GRP,
    PBC,
    ANRA,
    ANRB,
    ANRC,
    EMAILA,
    EMAILB,
    EMAILC,
    DATA_TIME,
    CALL_DURATION,
    CALL_STATUS,
    LINK_ENTRY,
    CC_PARAM,
    CMI_ALPHA,
    CMI_ID,
    EMS_CAT,
}PB_TYPE_TAG;

/* CDMA Hybrid mode */
typedef enum {
    HYBRID_MODE_1X_HRPD     = 0x1,
    HYBRID_MODE_1X_ONLY     = 0x2,
    HYBRID_MODE_HRPD_ONLY   = 0x3,
    HYBRID_MODE_1X_EHRPD    = 0x4,
    HYBRID_MODE_EHRPD_ONLY  = 0x5
} RIL_CdmaHybridMode;

/**
 * Used by RIL_REQUEST_READ_PB_ENTRY
 */
typedef struct {
    int type;
    int index;
} RIL_ReadPbEntryReq;

typedef struct {
    int num_len;
    int num_type;           /* refer to PB_NUMBER_TYPE */
    char *number;
    int text_len;
    int text_type;          /* refer to PB_TEXT_TYPE */
    char *text;
} RIL_PbEntry1;

typedef struct {
    int text_len;
    int text_type;          /* refer to PB_TEXT_TYPE */
    char *text;
} RIL_PbEntry2;

typedef struct {
    int type3g;             /* refer to pb_type_tag */
    int data_len;
    int data_type;
    char *data;
} RIL_3GPb;

typedef struct {
    int type;               /* refer to PB_TYPE */
    int index;              /* Lodation where the entry is stored in the storage */
    union {
        RIL_PbEntry1 pb1;
        RIL_PbEntry2 pb2;
        RIL_3GPb *pb3g;
    } entry;
} RIL_ReadPbEntry;

/**
 * Used by RIL_REQUEST_UPDATE_PB_ENTRY
 */
typedef struct {
    int mode;               /* 0x1: Add  / 0x2: Delete  / 0x3: Edit / 0x4: Delete All */
    int type;               /* refer to PB_TYPE */
    int index;
    int length;
    union {
        RIL_PbEntry1 pb1;
        RIL_PbEntry2 pb2;
        RIL_3GPb *pb3g;
    } entry;
} RIL_UpdatePbEntry;

typedef struct {
    int mode;
    int type;
    int index;
} RIL_UpdatePbRsp;

/**
 * Used by RIL_REQUEST_GET_PB_STORAGE_INFO
 */
typedef struct {
    int pb_type;            /* refer to PB_TYPE */
    int total_count;        /* Total number of the phonebook storage */
    int used_count;         /* Used number of the phonebook storage */
} RIL_PbStorageInfo;

/**
 * RIL_REQUEST_GET_PB_ENTRY_INFO
 */
typedef struct {
    int pb_type;           /* refer to PB_TYPE */
    int index_min;         /* Minimum index of phonebook entries */
    int index_max;         /* Maximum index of phonebook entries */
    int num_max;           /* Maximum length of number can be saved in phonebook entry */
    int text_max;          /* Maximum character length of test can be saved in phonebook entry */
} RIL_PbEntryInfo;

/**
 * SIM Lock Status
 */
enum {
    LOCK_TYPE_UNKNOWN = -1,
    LOCK_TYPE_UNLOCKED = 0,
    LOCK_TYPE_PN,
    LOCK_TYPE_PU,
    LOCK_TYPE_SP,
    LOCK_TYPE_CP,
    LOCK_TYPE_MAX,
};

#define DEFAULT_LOCK_CODE_SIZE    2
#define PN_LOCK_CODE_SIZE         6
#define MAX_LOCK_CODE_SIZE        1008

typedef struct {
    int policy;                    // SIM lock policy 0 to 11
    int status;                    // 0: unlocked, 1: locked
    int lockType;                  // 0: unlocked, 1: Network Lock(PN), 2: Network Subset Lock(PU),
                                   // 3: Service Provider Lock(SP), 4: Corporate Lock(CP)
    int maxRetryCount;             // max retry count
    int remainCount;               // remaining unlock retry count
    int numOfLockCode;             // total size of lock code entries.
                                   // max 168 for PN or 504 for other lock types(PU, SP, CP).
    char **lockCode;               // list of lock code as ASCII string
} RIL_SimLockStatus;

/**
 * RIL_REQUEST_GET_3G_PB_CAPA
 */
typedef struct {
    int pb_type;           /* refer to PB_TYPE */
    int index_max;         /* Maximum index of phonebook entries */
    int entry_max;         /* Maximum number of phonebook entries */
    int used_count;        /* Used phonebook entries */
} RIL_PbCapa;

/**
 * Used by RIL_REQUEST_SET_ACTIVATE_VSIM
 */
typedef struct {
    int simSlot;
    char *iccid;
    char *imsi;
    char *hplmn;
    int vsimState;
    int vsimCardType;
} RIL_SetActivateVsim;

/**
 * Used by RIL_REQUEST_GET_SMS_STORAGE_ON_SIM
 */
typedef struct
{
  int sim_id;    /* Sim type. 0x00:SIM, 0x01:RUIM */
  int total_num;    /* Total number of sms which can be stored*/
  int used_num;    /* Total used number of sms in the sim card*/
} RIL_StorageStatus;

#define RIL_REQUEST_EXTENSION_BASE 5000

/**
 * RIL_REQUEST_SWITCH_VOICE_CALL
 *
 * "data" is the SimCardNumber to switch destination
 * "response" is ?
 *
 */
#define RIL_REQUEST_SWITCH_VOICE_CALL (RIL_REQUEST_EXTENSION_BASE+1)
#define RIL_REQUEST_QUERY_COLP (RIL_REQUEST_EXTENSION_BASE + 2)
#define RIL_REQUEST_QUERY_COLR (RIL_REQUEST_EXTENSION_BASE + 3)
#define RIL_REQUEST_GET_ALLOW_DATA_STATE (RIL_REQUEST_EXTENSION_BASE+4)

/**
 * RIL_REQUEST_SIM_GET_ATR
 *
 * Retrieves the ATR from the UICC.
 *
 * "data" is null
 * "response" is const char * to the ATR.
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SIM_GET_ATR (RIL_REQUEST_EXTENSION_BASE+5)

/**
 * RIL_REQUEST_SEND_ENCODED_USSD
 *
 * Send a encoded USSD data
 *
 * Same as RIL_REQUEST_SEND_USSD usage
 *
 * "data" is const char **
 * ((const char **)data)[0] is two hexadecimal string. e.g., from 0xF0 -> "F0"
 * ((const char **)data)[1] is containing the USSD request in each DCS format
 *
 * "response" is NULL
 *
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  FDN_CHECK_FAILURE
 *  GENERIC_FAILURE
 */
#ifndef RIL_REQUEST_SEND_ENCODED_USSD
#define RIL_REQUEST_SEND_ENCODED_USSD (RIL_REQUEST_EXTENSION_BASE+6)
#endif

/**
 * RIL_REQUEST_SET_UPLMN
 *
 * Modify UPLMN list.
 *
 * "data" is const char **
 * ((char**)data)[0] indicating mode
 *                   1 - Add
 *                   2 - Edit
 *                   3 - Delete
 * ((char**)data)[1] indicating index
 * ((char**)data)[2] indicating 5 or 6 digit numeric code (MCC + MNC)
 * ((char**)data)[3] indicating Access Technology (can select multiple AcT with bitwise)
 *                   0 - Unknown
 *                   1 - GSM
 *                   2 - GSM Compact
 *                   4 - UTRAN
 *                   8 - EUTRAN
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 *
 */
#define RIL_REQUEST_SET_UPLMN (RIL_REQUEST_EXTENSION_BASE+7)

/**
 * RIL_REQUEST_GET_UPLMN
 *
 * Query UPLMN list
 *
  * "data" is NULL
 * "response" is const char ** that should be an array of n*3 strings,
 *  where n is the number of available PLMN
 *
 * For each available UPLMN:
 *
 * ((const char **)response)[n+0] is index of operator
 * ((const char **)response)[n+1] is 5 or 6 digit numeric code (MCC + MNC)
 * ((const char **)response)[n+2] is Access Technology (can be set multiple AcT with bitwise)
 *                                0 - Unknown
 *                                1 - GSM
 *                                2 - GSM Compact
 *                                4 - UTRAN
 *                                8 - EUTRAN
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_GET_UPLMN (RIL_REQUEST_EXTENSION_BASE+8)

/**
 * RIL_REQUEST_READ_PB_ENTRY
 *
 * "data" is RIL_ReadPbEntryReq *
 * "response" is RIL_ReadPbEntry *
 *   an array of RIL_3GPB if mode is PB_ADN_3G
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
*/
#define RIL_REQUEST_READ_PB_ENTRY (RIL_REQUEST_EXTENSION_BASE+9)

/**
 * RIL_REQUEST_UPDATE_PB_ENTRY
 *
 * "data" is RIL_UpdatePbEntry *
 *   an array of RIL_3GPB if mode is PB_ADN_3G
 * "response" is RIL_UpdatePbRsp *
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
*/
#define RIL_REQUEST_UPDATE_PB_ENTRY (RIL_REQUEST_EXTENSION_BASE+10)

/**
 * RIL_REQUEST_GET_PB_STORAGE_INFO
 *
 * Requests to get the phonebook storage information
 *
 * "data" is int * which is PhoneBook Type, refer to the  PB_TYPE
 * "response" is RIL_PbStorageInfo *
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
*/
#define RIL_REQUEST_GET_PB_STORAGE_INFO (RIL_REQUEST_EXTENSION_BASE+11)

/**
 * RIL_REQUEST_GET_PB_STORAGE_LIST
 *
 * Requests to get phonebook entry information
 *
 * "data" is NULL
 * "response" is int*
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_GET_PB_STORAGE_LIST (RIL_REQUEST_EXTENSION_BASE+12)


/**
 * RIL_REQUEST_GET_PB_ENTRY_INFO
 *
 * Requests to get phonebook entry information
 *
 * "data" is int * , refer to the PB_TYPE
 * "response" is RIL_PbEntryInfo *
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_GET_PB_ENTRY_INFO (RIL_REQUEST_EXTENSION_BASE+13)


/**
 * RIL_REQUEST_GET_3G_PB_CAPA
 *
 * Get 3G phonebook capability
 *
 * "data" is NULL
 * "response" is an array of RIL_PbCapa *
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
*/
#define RIL_REQUEST_GET_3G_PB_CAPA (RIL_REQUEST_EXTENSION_BASE+14)

/**
 * RIL_REQUEST_SET_CALL_CONFIRM
 *
 * Set call confirmation feature
 *
 * "data" is an int *
 * ((int *)data)[0] is 0 for "disable call confirm" and 1 for "enable call confirm"
 *
 * "response" is 0 for "fail" and 1 for "success"
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_CALL_CONFIRM (RIL_REQUEST_EXTENSION_BASE+15)

/**
 * RIL_REQUEST_SEND_CALL_CONFIRM
 *
 * Send call confirm
 *
 * "data" is NULL
 *
 * "response" is 0 for "fail" and 1 for "success"
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SEND_CALL_CONFIRM (RIL_REQUEST_EXTENSION_BASE+16)

/**
 * RIL_REQUEST_SET_DS_NETWORK_TYPE
 *
 * Set the preferred network type for searching and registering.
 * (CS/PS domain, RAT, and operation mode)
 *
 * "data" is int * which is RIL_DS_NetworkType
 * "response" is NULL
 *
 */
#define RIL_REQUEST_SET_DS_NETWORK_TYPE (RIL_REQUEST_EXTENSION_BASE+17)

/**
 * RIL_REQUEST_SET_WBAMR_CAPABILITY
 *
 * Set WBAMR capability
 *
 * "data" is an int *
 * (int *)data)[0] is
 *          0 for "3G Narrow & 2G Narrow"
 *          1 for "3G Wide & 2G Narrow"
 *          2 for "3G Narrow & 2G Wide"
 *          3 for "3G Wide & 2G Wide"
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */

#define RIL_REQUEST_SET_WBAMR_CAPABILITY (RIL_REQUEST_EXTENSION_BASE+18)

/**
 * RIL_REQUEST_GET_WBAMR_CAPABILITY
 *
 * Queries the current state of the uplink mute setting
 *
 * "data" is NULL
 * "response" is an int *
 * (int *)response)[0] is
 *          0 for "3G Narrow & 2G Narrow"
 *          1 for "3G Wide & 2G Narrow"
 *          2 for "3G Narrow & 2G Wide"
 *          3 for "3G Wide & 2G Wide"
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */

#define RIL_REQUEST_GET_WBAMR_CAPABILITY (RIL_REQUEST_EXTENSION_BASE+19)

/**
 * (reserved)
 * RIL_REQUEST_GET_DUPLEX_MODE
 *
 * Used to get duplex mode status.
 * "data" is NULL
 * "response" is an int *
 * ((int *)response)[0] is
 *          0 for "GLOBAL : 4G(FDD_TDD) & 3G(FDD_TDD)"
 *          1 for "LTG : 4G(TDD) & 3G(TDD)"
 *          2 for "LWG: 4G(FDD_TDD) & 3G(FDD)"
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_GET_DUPLEX_MODE (RIL_REQUEST_EXTENSION_BASE+20)

typedef enum {
    DUPLEX_MODE_GLOBAL,
    DUPLEX_MODE_LTG,
    DUPLEX_MODE_LWG,

    DUPLEX_MODE_INVALID
}DUPLEX_MODE;

/**
 * (reserved)
 * RIL_REQUEST_SET_DUPLEX_MODE
 *
 * Used to set duplex mode.
 * "data" is an int *
 * ((int *)data)[0] is
 *          0 for "GLOBAL : 4G(FDD_TDD) & 3G(FDD_TDD)"
 *          1 for "LTG : 4G(TDD) & 3G(TDD)"
 *          2 for "LWG: 4G(FDD_TDD) & 3G(FDD)"
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_DUPLEX_MODE (RIL_REQUEST_EXTENSION_BASE+21)

/**
 * RIL_LOCAL_REQUEST_VSIM_NOTIFICATION
 *
 *
 *
 * "data" is RIL_VsimEvent
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_LOCAL_REQUEST_VSIM_NOTIFICATION (RIL_REQUEST_EXTENSION_BASE+22)

typedef struct RIL_VsimEvent {
    int transaction_id;
    int eventId;
    int sim_type; //0: local sim, 1: remote sim
} RIL_VsimEvent;

enum EventTypeId {
    REQUEST_TYPE_ENABLE_EXTERNAL_SIM = 1,
    REQUEST_TYPE_DISABLE_EXTERNAL_SIM = 2,
    REQUEST_TYPE_PLUG_OUT = 3,
    REQUEST_TYPE_PLUG_IN = 4,
    REQUEST_TYPE_ATR_EVENT = 1,
    REQUEST_TYPE_APDU_EVENT = 2,
    REQUEST_TYPE_CARD_POWER_DOWN = 3,
};

/**
 * RIL_LOCAL_REQUEST_VSIM_OPERATION
 *
 *
 *
 * "data" is RIL_VsimOperationEvent
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */

#define RIL_LOCAL_REQUEST_VSIM_OPERATION (RIL_REQUEST_EXTENSION_BASE+23)

typedef struct {
    int transaction_id;
    int eventId;                         // 0: ATR, 1: APDU, 2: power down
    int result;                          // 0: successful, < 0: error cause
    int data_length;
    char *data;                          // It is ATR in case of reset response, APDU incase of APDU request
} RIL_VsimOperationEvent;


/**
 * RIL_REQUEST_QUERY_AVAILABLE_EMERGENCY_CALL_STATUS
 *
 * Used to query available emergency call status
 * (Status: 0x01=Emergency Call Start, RAT: 0xFF=Not specified)
 *
 * "data" is NULL
 * "response" is int *
 *
 */
#define RIL_REQUEST_QUERY_AVAILABLE_EMERGENCY_CALL_STATUS (RIL_REQUEST_EXTENSION_BASE+24)

/**
 * RIL_REQUEST_SET_EMERGENCY_CALL_STATUS
 *
 * Used to set available emergency call status
 *
 * "data" is int *
 * "response" is NULL
 *
 * Valid error:
 *  SUCCESS
 *  GENERIC_FAILURE
 *
 */
#define RIL_REQUEST_SET_EMERGENCY_CALL_STATUS (RIL_REQUEST_EXTENSION_BASE+25)

/**
 * (reserved)
 * RIL_REQUEST_SET_FEMTO_CELL_SRCH
 *
 * Used to set duplex mode.
 * "data" is an int *
 * ((int *)data)[0] is
 *          0 for "MANUAL MODE"
 *          1 for "AUTO MODE"
 *          2 for "CANCEL"
 * "response" is a "const char **"
 * ((const char **)response)[0] is search result
 *                   0 - SUCCESS
 *                   1 - NW_NOT_SUPPORT_MICROCELL
 *                   2 - SEARCH_MODE_NOT_AVAILABLE
 *                   3 - NO_MICROCELL_LIST
 *
 * ((const char **)response)[1] is 5 or 6 digit numeric code (MCC + MNC)
 *                                  or NULL if not found
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_FEMTO_CELL_SRCH (RIL_REQUEST_EXTENSION_BASE+26)

/**
 * Requests to set the cdma hybrid mode
 *
 * "data" is int * which is RIL_CdmaHybridMode
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_CDMA_HYBRID_MODE (RIL_REQUEST_EXTENSION_BASE+27)

/**
 * Requests to get the cdma hybrid mode
 *
 * "data" is NULL
 *
 * "response" is int * which is RIL_CdmaHybridMode
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_GET_CDMA_HYBRID_MODE (RIL_REQUEST_EXTENSION_BASE+28)

/**
 * RIL_REQUEST_SET_OPEN_CARRIER_INFO
 *
 * Used to set open carrier info. It is designed to use inside of Vendor RIL and Modem
 * There is no relationship to TFW.
 *
 * "data" is a "const char **"
 * ((const char **)data)[0] is operator index
 * ((const char **)data)[1] is 5 or 6 digit numeric code (MCC + MNC)
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_OPEN_CARRIER_INFO (RIL_REQUEST_EXTENSION_BASE+29)

/**
 * Requests to set preferred call capability
 *
 * "data" is NULL
 *
 * "data" is int *
 * ((int *)data)[0] is
 *          0 for "CS only"
 *          1 for "PS only" (not used)
 *          2 for "CS preferred" (not used)
 *          3 for "PS preferred"
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */

#define RIL_REQUEST_SET_VOICE_OPERATION (RIL_REQUEST_EXTENSION_BASE+30)

/**
 * Requests to set dual network mode & ps service
 *
 * ((int *)data)[0] is
 *                   0 for "PREF_NET_TYPE for Primary"
 *                   1 for "PREF_NET_TYPE for Secondary"
 *                   2 for "PS capability for Primary"
 *                   3 for "PS capability for Secondary"
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_DUAL_NETWORK_AND_ALLOW_DATA (RIL_REQUEST_EXTENSION_BASE+31)

/**
 * RIL_REQUEST_SIM_OPEN_CHANNEL
 *
 * Open a new logical channel and select the given application.
 *
 * "data" is const char * and set to AID value, See ETSI 102.221 and 101.220.
 * "p2" is the p2 byte to set
 *
 * "response" is int *
 * ((int *)data)[0] contains the session id of the logical channel.
 * ((int *)data)[1] onwards may optionally contain the select response for the
 *     open channel command with one byte per integer.
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 *  MISSING_RESOURCE
 *  NO_SUCH_ELEMENT
 */
#define RIL_REQUEST_SIM_OPEN_CHANNEL_WITH_P2 (RIL_REQUEST_EXTENSION_BASE+32)

/**
 * RIL_REQUEST_QUERY_BPLMN_SEARCH
 *
 * Scans for available networks
 *
 * "data" is NULL
 * "response" is const char ** that should be an array of n*5 strings, where
 *    n is the number of available networks
 * For each available network:
 *
 * ((const char **)response)[n+0] is long alpha ONS or EONS
 * ((const char **)response)[n+1] is short alpha ONS or EONS
 * ((const char **)response)[n+2] is 5 or 6 digit numeric code (MCC + MNC)
 * ((const char **)response)[n+3] is a string value of the status:
 * ((const char **)response)[n+4] is a string value of rat:
 *           "unknown"
 *           "available"
 *           "current"
 *           "forbidden"
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  OPERATION_NOT_ALLOWED
 *  ABORTED
 *  DEVICE_IN_USE
 *  INTERNAL_ERR
 *  NO_MEMORY
 *  MODEM_ERR
 *  REQUEST_NOT_SUPPORTED
 *  CANCELLED
 *  OPERATION_NOT_ALLOWED
 *
 */
#define RIL_REQUEST_QUERY_BPLMN_SEARCH (RIL_REQUEST_EXTENSION_BASE+33)

/**
 * RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL_WITH_RAT
 *
 * Manually select a specified network.
 *
 * "data" is const char **
 * ((const char **)data)[0] is specifying MCCMNC of network to select (eg "310170")
 * ((const char **)data)[1] is rat
 *
 * This request must not respond until the new operator is selected
 * and registered
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  ILLEGAL_SIM_OR_ME
 *  OPERATION_NOT_ALLOWED
 *  INVALID_STATE
 *  NO_MEMORY
 *  INTERNAL_ERR
 *  SYSTEM_ERR
 *  INVALID_ARGUMENTS
 *  MODEM_ERR
 *  REQUEST_NOT_SUPPORTED
 *
 * Note: Returns ILLEGAL_SIM_OR_ME when the failure is permanent and
 *       no retries needed, such as illegal SIM or ME.
 *
 */
#define RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL_WITH_RAT (RIL_REQUEST_EXTENSION_BASE+34)

/**
 * RIL_REQUEST_DIAL_WITH_CALL_TYPE
 *
 * Initiate voice call
 *
 * "data" is const RIL_Dial *
 * "response" is NULL
 *
 * This method is never used for supplementary service codes
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE (radio resetting)
 *  DIAL_MODIFIED_TO_USSD
 *  DIAL_MODIFIED_TO_SS
 *  DIAL_MODIFIED_TO_DIAL
 *  INVALID_ARGUMENTS
 *  NO_MEMORY
 *  INVALID_STATE
 *  NO_RESOURCES
 *  INTERNAL_ERR
 *  FDN_CHECK_FAILURE
 *  MODEM_ERR
 *  NO_SUBSCRIPTION
 *  NO_NETWORK_FOUND
 *  INVALID_CALL_ID
 *  DEVICE_IN_USE
 *  MODE_NOT_SUPPORTED
 *  ABORTED
 */
#define RIL_REQUEST_DIAL_WITH_CALL_TYPE (RIL_REQUEST_EXTENSION_BASE+35)

/**
 * RIL_REQUEST_CHANGE_BARRING_PASSWORD
 *
 * Change call barring facility password
 *
 * "data" is const char **
 *
 * ((const char **)data)[0] = facility string code from TS 27.007 7.4
 * (eg "AO" for BAOC)
 * ((const char **)data)[1] = old password
 * ((const char **)data)[2] = new password
 * ((const char **)data)[3] = again password
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  SS_MODIFIED_TO_DIAL
 *  SS_MODIFIED_TO_USSD
 *  SS_MODIFIED_TO_SS
 *  INVALID_ARGUMENTS
 *  NO_MEMORY
 *  MODEM_ERR
 *  INTERNAL_ERR
 *  SYSTEM_ERR
 *  FDN_CHECK_FAILURE
 *
 */
#define RIL_REQUEST_CHANGE_BARRING_PASSWORD_OVER_MMI (RIL_REQUEST_EXTENSION_BASE+36)

/*
 * RIL_REQUEST_SET_DEVICE_INFO
 *
 * Used to set device information to CP. It is designed to use inside of Vendor RIL and Modem
 * There is no relationship to TFW.
 *
 * "data" is a "const char **"
 * ((const char **)data)[0] is model string
 * ((const char **)data)[1] is sw ver. string
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_DEVICE_INFO (RIL_REQUEST_EXTENSION_BASE+37)

/**
 * RIL_REQUEST_DEACTIVATE_DATA_CALL_WITH_REASON
 *
 * Deactivate packet data connection and remove from the
 * data call list if SUCCESS is returned. Any other return
 * values should also try to remove the call from the list,
 * but that may not be possible. In any event a
 * RIL_REQUEST_RADIO_POWER off/on must clear the list. An
 * RIL_UNSOL_DATA_CALL_LIST_CHANGED is not expected to be
 * issued because of an RIL_REQUEST_DEACTIVATE_DATA_CALL_WITH_REASON.
 *
 * "data" is const char **
 * ((char**)data)[0] indicating CID
 * ((char**)data)[1] indicating Disconnect Reason
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INVALID_CALL_ID
 *  INVALID_STATE
 *  INVALID_ARGUMENTS
 *  REQUEST_NOT_SUPPORTED
 *
 * See also: RIL_REQUEST_SETUP_DATA_CALL
 */

// Deprecated from P, will be covered by updated DeactivateDataCall_v1_2
#define RIL_REQUEST_DEACTIVATE_DATA_CALL_WITH_REASON (RIL_REQUEST_EXTENSION_BASE+38)

/*
 * RIL_REQUEST_EMULATE_IND
 *
 * Trigger IND EMULATION
 *
 * "data" is int *
 * ((int *)data)data)[0] is Scenario Test Case No. Currently don't care only emulate one case
 *
 * "response" is NULL
 *
 * Valid errors:
 *
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_EMULATE_IND (RIL_REQUEST_EXTENSION_BASE+39)

/*
 * RIL_REQUEST_GET_SIM_LOCK_STATUS
 *
 * Get a current SIM lock status
 *
 * "data" is null
 *
 * "response" is RIL_SimLockStatus
 *
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 */
#define RIL_REQUEST_GET_SIM_LOCK_STATUS (RIL_REQUEST_EXTENSION_BASE+40)

/**
  * RIL_REQUEST_SET_INTPS_SERVICE
  * !DEPRECATED!
  * enable/disable default internet service
  *
  * "data" is int
  * "response" is NULL
  *
  * Valid errors:
  *  SUCCESS
  *  RIL_E_INTERNAL_ERR
  *  REQUEST_NOT_SUPPORTED
  */
#define RIL_REQUEST_SET_INTPS_SERVICE (RIL_REQUEST_EXTENSION_BASE+41)

/**
  * RIL_REQUEST_SET_ACTIVATE_VSIM
  *
  * set activate VSIM
  *
  * "data" is RIL_SetActivateVsim
  * "response" is int
  *
  * Valid errors:
  *  SUCCESS
  *  RIL_E_INTERNAL_ERR
  *  REQUEST_NOT_SUPPORTED
  */
#define RIL_REQUEST_SET_ACTIVATE_VSIM (RIL_REQUEST_EXTENSION_BASE+42)

/**
  * RIL_REQUEST_SET_ENDC_MODE
  *
  * enable/disable EN-DC mode
  *
  * "data" is int
  * "response" is NULL
  *
  * Valid errors:
  *  SUCCESS
  *  RIL_E_INTERNAL_ERR
  *  REQUEST_NOT_SUPPORTED
  */
#define RIL_REQUEST_SET_ENDC_MODE (RIL_REQUEST_EXTENSION_BASE+43)

/**
  * RIL_REQUEST_GET_ENDC_MODE
  *
  * get the current EN-DC mode
  *
  * "data" is NULL
  * "response" is int
  *
  * Valid errors:
  *  SUCCESS
  *  RIL_E_INTERNAL_ERR
  *  REQUEST_NOT_SUPPORTED
  */
#define RIL_REQUEST_GET_ENDC_MODE (RIL_REQUEST_EXTENSION_BASE+44)

/**
 * RIL_REQUEST_GET_SMS_STORAGE_ON_SIM
 *
 * Get sim sms capacity.
 *
 * "data" is int  *
 * ((int *)data)[0] is the store sim type.
 *
 * "response" is RIL_StorageStatus
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 *  NO_MEMORY
 *  NO_RESOURCES
 *  CANCELLED
 *  REQUEST_NOT_SUPPORTED
 *
 */
#define RIL_REQUEST_GET_SMS_STORAGE_ON_SIM (RIL_REQUEST_EXTENSION_BASE+45)

/***********************************************************************/


#define RIL_UNSOL_EXTENSION_BASE 6000

/**
 * RIL_UNSOL_SUPP_SVC_RETURN_RESULT
 *
 * Indicate when supplimentary service issue a return result to applications
 *
 * "data" is a const char * containing supplimentary service return result
 * in hexadecimal format string starting with command tag
 *
 */
#define RIL_UNSOL_SUPP_SVC_RETURN_RESULT (RIL_UNSOL_EXTENSION_BASE+1)

/**
 * RIL_UNSOL_PB_READY
 *
 * Indicate when PhoneBook is ready.
 *
 * "data" is a const int *
 * the value is 1 when phonebook is ready, the otherwise it is 0.
 *
*/
#define RIL_UNSOL_PB_READY (RIL_UNSOL_EXTENSION_BASE+2)

/**
 * RIL_UNSOL_CALL_PRESENT_IND
 *
 * Call present indication for an incoming call
 * if the "call confirm" is enabled.
 *
 * "data" is null for GSM
 *  We will not handle CDMA.
 */
#define RIL_UNSOL_CALL_PRESENT_IND (RIL_UNSOL_EXTENSION_BASE+3)

/**
 * RIL_UNSOL_WB_AMR_REPORT_IND
 *
 * report whether current vocoder rate is WB-AMR or not
 *
 * "data" is int *
 * ((int *)data)[0] is == 0 to indicate WB-AMR off
 * ((int *)data)[0] is == 1 to indicate WB-AMR on
 */
#define RIL_UNSOL_WB_AMR_REPORT_IND (RIL_UNSOL_EXTENSION_BASE+4)

/**
 * RIL_UNSOL_VSIM_OPERATION_INDICATION
 *
 *
 *
 * "data" is RIL_VsimOperationEvent
 */
#define RIL_UNSOL_VSIM_OPERATION_INDICATION (RIL_UNSOL_EXTENSION_BASE+5)

/**
 * RIL_UNSOL_NAS_TIMER_STATUS_IND
 *
 * "data" is int *
 * ((int *)data)data)[0] is type.  0 is invalid, 1 is T3346, 2 is T3396
 * ((int *)data)data)[1] is status. 0 is STARTED, 1 is STOPPED, 2 is EXPIRED
 * ((int *)data)data)[2] is value. timer value in seconds, invalid : 0xffffffff
 * ((char *)data)apn)[3] is apn name.
 *                              VZW - initial attach APN name
 *                              others - setup data call APN name
 */
 typedef struct {
    int type;
    int status;
    int value;
    char *apn;
} RIL_NasTimerStatus;
#define RIL_UNSOL_NAS_TIMER_STATUS_IND (RIL_UNSOL_EXTENSION_BASE+6)

/**
 * RIL_UNSOL_EMERGENCY_ACT_INFO
 *
 * "data" is int *
 * ((int *)data)[0] is RAT. 0x00 ~ 0x14 are UNKNOWN, GPRS, EDGE, UMTS, IS95A, IS95B, 1xRTT,
 *                                          EVDO_0, EVDO_A, HSDPA, HSUPA, HSPA, EVDO_B, EHRPD, LTE,
 *                                          HSPAP, GSM, IWLAN, TD_SCDMA, HSPADCPLUS, LTE_CA, respectively.
 *                          0xFF is Not specified.
 *
 */
#define RIL_UNSOL_EMERGENCY_ACT_INFO (RIL_UNSOL_EXTENSION_BASE+7)

/**
 * RIL_UNSOL_ICCID_INFO
 *
 *  This message is used to get information of ICCID
 *
 * "data" is a const char * containing Iccid
 * in hexadecimal format string starting with command tag
 *
 */
#define RIL_UNSOL_ICCID_INFO    (RIL_UNSOL_EXTENSION_BASE+8)

/**
 * RIL_UNSOL_ON_USSD_WITH_DCS
 *
 * Called when a new USSD message is received.
 *
 * "data" is const char **
 * ((const char **)data)[0] points to a type code, which is
 *  one of these string values:
 *      "0"   USSD-Notify -- text in ((const char **)data)[1]
 *      "1"   USSD-Request -- text in ((const char **)data)[1]
 *      "2"   Session terminated by network
 *      "3"   other local client (eg, SIM Toolkit) has responded
 *      "4"   Operation not supported
 *      "5"   Network timeout
 *
 * The USSD session is assumed to persist if the type code is "1", otherwise
 * the current session (if any) is assumed to have terminated.
 *
 * ((const char **)data)[1] points to a message string if applicable, which
 * should always be in UTF-8.
 * ((const char **)data)[2] points to a dcs string
 */
#define RIL_UNSOL_ON_USSD_WITH_DCS (RIL_UNSOL_EXTENSION_BASE+9)

/**
 * RIL_UNSOL_VOLTE_AVAILABLE_INFO
 *
 * This message is used to notify volte available info.
 *
 * "data" is const char **
 */
#define RIL_UNSOL_VOLTE_AVAILABLE_INFO (RIL_UNSOL_EXTENSION_BASE+10)

/**
 * RIL_UNSOL_EMERGENCY_SUPPORT_RAT_MODE
 *
 *  This message is to inform AP of available RAT for ecall of CP
 *
 */
#define RIL_UNSOL_EMERGENCY_SUPPORT_RAT_MODE (RIL_UNSOL_EXTENSION_BASE+11)

/**
 * RIL_UNSOL_USSD_CANCELED
 *
 *  This message is to inform AP for STK about canceled USSD operation.
 *  "data" is NULL
 *
 */
#define RIL_UNSOL_USSD_CANCELED (RIL_UNSOL_EXTENSION_BASE+12)

/**
 * RIL_REQUEST_OEM_ENABLE_EMBMS_SERVICE
 * RIL_REQUEST_OEM_DISABLE_EMBMS_SERVICE
 */

typedef struct {
    char *interfaceName;
    char *interfaceIndex;
    char *modemType;
} RIL_EmbmsService_Response;

#define EMBMS_MAX_FREQLIST_NUMBER       (8)
#define EMBMS_MAX_INTRA_SAILIST_NUMBER  (64)
#define EMBMS_MAX_IPADDR_LEN            (41)

typedef struct {
    uint32_t uSAICount;
    uint32_t nSAIList[EMBMS_MAX_INTRA_SAILIST_NUMBER];
    uint32_t uFreqCount;
    uint32_t nFreqList[EMBMS_MAX_FREQLIST_NUMBER];
} __attribute__((packed)) RIL_InfoBinding;

typedef struct {
    uint32_t state;
    uint8_t priority;
    uint64_t tmgi;               // Temporary Mobile Group Identity
    RIL_InfoBinding infobind;     // MAX_Count value
    uint32_t  infobindcount;
} __attribute__((packed)) RIL_EmbmsSessionData;

/**
 * RIL_UNSOL_NR_PHYSICAL_CHANNEL_CONFIGS
 *
 * Indicates current physical channel configuration.
 *
 * "data" is int *
 * ((int *)data)[0] rat
 * ((int *)data)[1] status
 */
#define RIL_UNSOL_NR_PHYSICAL_CHANNEL_CONFIGS (RIL_UNSOL_EXTENSION_BASE+13)

/**
 * RIL_UNSOL_IND_ENDC_CAPABILITY
 * This message is used to indicate network ENDC capability cause so that AP will enable/disable ENDC setting based on Cause field.
 * "data" is int *
 * ((int *)data)[0] is == 0x01 : Disable EDNC capability
 * ((int *)data)[0] is == 0x02 : Enable ENDC capability
 */
#define RIL_UNSOL_IND_ENDC_CAPABILITY (RIL_UNSOL_EXTENSION_BASE+14)

#ifdef __cplusplus
}
#endif

#endif  /*ANDROID_RIL_EXT_H*/

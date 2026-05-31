/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RADIO_V1_2_H__
#define __RADIO_V1_2_H__

#include <telephony/ril.h>

#define RADIO_ACCESS_SPECIFIER_MAX_SIZE 8,
#define MAX_ALPHA_OPERATOR_NAME_LEN 64

typedef struct
{
  RIL_CardState card_state;
  RIL_PinState  universal_pin_state;             /* applicable to USIM and CSIM: RIL_PINSTATE_xxx */
  int           gsm_umts_subscription_app_index; /* value < RIL_CARD_MAX_APPS, -1 if none */
  int           cdma_subscription_app_index;     /* value < RIL_CARD_MAX_APPS, -1 if none */
  int           ims_subscription_app_index;      /* value < RIL_CARD_MAX_APPS, -1 if none */
  int           num_applications;                /* value <= RIL_CARD_MAX_APPS */
  RIL_AppStatus applications[RIL_CARD_MAX_APPS];
  uint32_t physicalSlotId;
  char *atr;
  char *iccid;
} RIL_CardStatus_V1_2;

/**
 * Audio codec which is used on GSM, UMTS, and CDMA. These values must be opaque
 * to the Android framework. Only for display.
 */
typedef enum AudioQuality {
    UNSPECIFIED,  /*Unspecified audio codec */
    AMR,          /*AMR (Narrowband) audio codec */
    AMR_WB,       /*AMR (Wideband) audio codec */
    GSM_EFR,      /*GSM Enhanced Full-Rate audio codec */
    GSM_FR,       /*GSM Full-Rate audio codec */
    GSM_HR,       /*GSM Half-Rate audio codec */
    EVRC,         /*Enhanced Variable rate codec */
    EVRC_B,       /*Enhanced Variable rate codec revision B */
    EVRC_WB,      /*Enhanced Variable rate codec (Wideband) */
    EVRC_NW,      /*Enhanced Variable rate codec (Narrowband) */
} RIL_AudioQuality;

typedef struct {
    RIL_CallState   state;
    int             index;      /* Connection Index for use with, eg, AT+CHLD */
    int             toa;        /* type of address, eg 145 = intl */
    char            isMpty;     /* nonzero if is mpty call */
    char            isMT;       /* nonzero if call is mobile terminated */
    char            als;        /* ALS line indicator if available
                                   (0 = line 1) */
    char            isVoice;    /* nonzero if this is is a voice call */
    char            isVoicePrivacy;     /* nonzero if CDMA voice privacy mode is active */
    char *          number;     /* Remote party number */
    int             numberPresentation; /* 0=Allowed, 1=Restricted, 2=Not Specified/Unknown 3=Payphone */
    char *          name;       /* Remote party name */
    int             namePresentation; /* 0=Allowed, 1=Restricted, 2=Not Specified/Unknown 3=Payphone */
    RIL_UUS_Info *  uusInfo;    /* NULL or Pointer to User-User Signaling Information */
    RIL_AudioQuality audioQuality;
} RIL_Call_V1_2;

typedef struct {
    int signalStrength;  /* Valid values are (0-31, 99) as defined in TS 27.007 8.5 */
    int bitErrorRate;    /* bit error rate (0-7, 99) as defined in TS 27.007 8.5 */
    uint32_t rscp;       /* CPICH RSCP as defined in TS 25.215 5.1.1 */
                         /* Valid values are (0-96, 255) as defined in TS 27.007 8.69 */
    uint32_t ecno;       /* Ec/No value as defined in TS 25.215 5.1.5 */
                         /* Valid values are (0-49, 255) as defined in TS 27.007 8.69 */
} RIL_WCDMA_SignalStrength_V1_2;

typedef struct {
    /**
     * UTRA carrier RSSI as defined in TS 25.225 5.1.4
     * Valid values are (0-31, 99) as defined in TS 27.007 8.5
     */
    uint32_t signalStrength;
    /**
     * Transport Channel BER as defined in TS 25.225 5.2.5
     * Valid values are (0-7, 99) as defined in TS 27.007 8.5
     */
    uint32_t bitErrorRate;
    /**
     * P-CCPCH RSCP as defined in TS 25.225 5.1.1
     * Valid values are (0-96, 255) as defined in TS 27.007 8.69
     */
    uint32_t rscp;
} RIL_TD_SCDMA_SignalStrength_V1_2;

// To do:
// In 1.2 type.hal, SignalStrength is defined to use TdScdmaSignalStrength that is defined in 1.0.
// So, to match with there, RIL_TD_SCDMA_SignalStrength has been used instead of RIL_TD_SCDMA_SignalStrength_V1_2.
typedef struct {
    RIL_GSM_SignalStrength_v12  GSM_SignalStrength;
    RIL_CDMA_SignalStrength     CDMA_SignalStrength;
    RIL_EVDO_SignalStrength     EVDO_SignalStrength;
    RIL_LTE_SignalStrength_v8   LTE_SignalStrength;
    RIL_TD_SCDMA_SignalStrength TD_SCDMA_SignalStrength;
    RIL_WCDMA_SignalStrength_V1_2 WCDMA_SignalStrength;
} RIL_SignalStrength_V1_2;

typedef struct CellIdentityOperatorNames {
    char alphaLong[MAX_ALPHA_OPERATOR_NAME_LEN];
    char alphaShort[MAX_ALPHA_OPERATOR_NAME_LEN];;
} RIL_CellIdentityOperatorNames;

typedef struct {
    int mcc;    /* 3-digit Mobile Country Code, 0..999, INT_MAX if unknown */
    int mnc;    /* 2 or 3-digit Mobile Network Code, 0..999, INT_MAX if unknown */
    int lac;    /* 16-bit Location Area Code, 0..65535, INT_MAX if unknown  */
    int cid;    /* 16-bit GSM Cell Identity described in TS 27.007, 0..65535, INT_MAX if unknown  */
    int arfcn;  /* 16-bit GSM Absolute RF channel number; this value must be reported */
    uint8_t bsic; /* 6-bit Base Station Identity Code; 0xFF if unknown */
    RIL_CellIdentityOperatorNames operatorNames;
} RIL_CellIdentityGsm_V1_2;

typedef struct {
    int mcc;    /* 3-digit Mobile Country Code, 0..999, INT_MAX if unknown  */
    int mnc;    /* 2 or 3-digit Mobile Network Code, 0..999, INT_MAX if unknown  */
    int lac;    /* 16-bit Location Area Code, 0..65535, INT_MAX if unknown  */
    int cid;    /* 28-bit UMTS Cell Identity described in TS 25.331, 0..268435455, INT_MAX if unknown  */
    int psc;    /* 9-bit UMTS Primary Scrambling Code described in TS 25.331, 0..511; this value must be reported */
    int uarfcn; /* 16-bit UMTS Absolute RF Channel Number; this value must be reported */
    RIL_CellIdentityOperatorNames operatorNames;
} RIL_CellIdentityWcdma_V1_2;

typedef struct {
    int networkId;      /* Network Id 0..65535, INT_MAX if unknown */
    int systemId;       /* CDMA System Id 0..32767, INT_MAX if unknown  */
    int basestationId;  /* Base Station Id 0..65535, INT_MAX if unknown  */
    int longitude;      /* Longitude is a decimal number as specified in 3GPP2 C.S0005-A v6.0.
                         * It is represented in units of 0.25 seconds and ranges from -2592000
                         * to 2592000, both values inclusive (corresponding to a range of -180
                         * to +180 degrees). INT_MAX if unknown */

    int latitude;       /* Latitude is a decimal number as specified in 3GPP2 C.S0005-A v6.0.
                         * It is represented in units of 0.25 seconds and ranges from -1296000
                         * to 1296000, both values inclusive (corresponding to a range of -90
                         * to +90 degrees). INT_MAX if unknown */
    RIL_CellIdentityOperatorNames operatorNames;
} RIL_CellIdentityCdma_V1_2;

typedef struct {
    int mcc;    /* 3-digit Mobile Country Code, 0..999, INT_MAX if unknown  */
    int mnc;    /* 2 or 3-digit Mobile Network Code, 0..999, INT_MAX if unknown  */
    int ci;     /* 28-bit Cell Identity described in TS ???, INT_MAX if unknown */
    int pci;    /* physical cell id 0..503; this value must be reported */
    int tac;    /* 16-bit tracking area code, INT_MAX if unknown  */
    int earfcn; /* 18-bit LTE Absolute RF Channel Number; this value must be reported */
    RIL_CellIdentityOperatorNames operatorNames;
    int bandwidth;
} RIL_CellIdentityLte_V1_2;

typedef struct {
    int mcc;    /* 3-digit Mobile Country Code, 0..999, INT_MAX if unknown  */
    int mnc;    /* 2 or 3-digit Mobile Network Code, 0..999, INT_MAX if unknown  */
    int lac;    /* 16-bit Location Area Code, 0..65535, INT_MAX if unknown  */
    int cid;    /* 28-bit UMTS Cell Identity described in TS 25.331, 0..268435455, INT_MAX if unknown  */
    int cpid;    /* 8-bit Cell Parameters ID described in TS 25.331, 0..127, INT_MAX if unknown */
    int uarfcn;
    RIL_CellIdentityOperatorNames operatorNames;
} RIL_CellIdentityTdscdma_V1_2;

typedef struct {
  RIL_CellInfoType  cellInfoType;   /* cell type for selecting from union CellInfo */
  union {
    RIL_CellIdentityGsm_V1_2 cellIdentityGsm;
    RIL_CellIdentityWcdma_V1_2 cellIdentityWcdma;
    RIL_CellIdentityLte_V1_2 cellIdentityLte;
    RIL_CellIdentityTdscdma_V1_2 cellIdentityTdscdma;
    RIL_CellIdentityCdma_V1_2 cellIdentityCdma;
  };
}RIL_CellIdentity_V1_2;

typedef struct {
    RIL_RegState regState;                // Valid reg states are RIL_NOT_REG_AND_NOT_SEARCHING,
                                          // REG_HOME, RIL_NOT_REG_AND_SEARCHING, REG_DENIED,
                                          // UNKNOWN, REG_ROAMING defined in RegState
    RIL_RadioTechnology rat;              // indicates the available voice radio technology,
                                          // valid values as defined by RadioTechnology.
    int32_t cssSupported;                 // concurrent services support indicator. if
                                          // registered on a CDMA system.
                                          // 0 - Concurrent services not supported,
                                          // 1 - Concurrent services supported
    int32_t roamingIndicator;             // TSB-58 Roaming Indicator if registered
                                          // on a CDMA or EVDO system or -1 if not.
                                          // Valid values are 0-255.
    int32_t systemIsInPrl;                // indicates whether the current system is in the
                                          // PRL if registered on a CDMA or EVDO system or -1 if
                                          // not. 0=not in the PRL, 1=in the PRL
    int32_t defaultRoamingIndicator;      // default Roaming Indicator from the PRL,
                                          // if registered on a CDMA or EVDO system or -1 if not.
                                          // Valid values are 0-255.
    int32_t reasonForDenial;              // reasonForDenial if registration state is 3
                                          // (Registration denied) this is an enumerated reason why
                                          // registration was denied. See 3GPP TS 24.008,
                                          // 10.5.3.6 and Annex G.
                                          // 0 - General
                                          // 1 - Authentication Failure
                                          // 2 - IMSI unknown in HLR
                                          // 3 - Illegal MS
                                          // 4 - Illegal ME
                                          // 5 - PLMN not allowed
                                          // 6 - Location area not allowed
                                          // 7 - Roaming not allowed
                                          // 8 - No Suitable Cells in this Location Area
                                          // 9 - Network failure
                                          // 10 - Persistent location update reject
                                          // 11 - PLMN not allowed
                                          // 12 - Location area not allowed
                                          // 13 - Roaming not allowed in this Location Area
                                          // 15 - No Suitable Cells in this Location Area
                                          // 17 - Network Failure
                                          // 20 - MAC Failure
                                          // 21 - Sync Failure
                                          // 22 - Congestion
                                          // 23 - GSM Authentication unacceptable
                                          // 25 - Not Authorized for this CSG
                                          // 32 - Service option not supported
                                          // 33 - Requested service option not subscribed
                                          // 34 - Service option temporarily out of order
                                          // 38 - Call cannot be identified
                                          // 48-63 - Retry upon entry into a new cell
                                          // 95 - Semantically incorrect message
                                          // 96 - Invalid mandatory information
                                          // 97 - Message type non-existent or not implemented
                                          // 98 - Message type not compatible with protocol state
                                          // 99 - Information element non-existent or
                                          //      not implemented
                                          // 100 - Conditional IE error
                                          // 101 - Message not compatible with protocol state;
    RIL_CellIdentity_V1_2 cellIdentity;   // current cell information
}RIL_VoiceRegistrationStateResponse_V1_2;

typedef struct {
    RIL_RegState regState;                // Valid reg states are RIL_NOT_REG_AND_NOT_SEARCHING,
                                          // REG_HOME, RIL_NOT_REG_AND_SEARCHING, REG_DENIED,
                                          // UNKNOWN, REG_ROAMING defined in RegState
    RIL_RadioTechnology rat;              // indicates the available data radio technology,
                                          // valid values as defined by RadioTechnology.
    int32_t reasonDataDenied;             // if registration state is 3 (Registration
                                          // denied) this is an enumerated reason why
                                          // registration was denied. See 3GPP TS 24.008,
                                          // Annex G.6 "Additional cause codes for GMM".
                                          // 7 == GPRS services not allowed
                                          // 8 == GPRS services and non-GPRS services not allowed
                                          // 9 == MS identity cannot be derived by the network
                                          // 10 == Implicitly detached
                                          // 14 == GPRS services not allowed in this PLMN
                                          // 16 == MSC temporarily not reachable
                                          // 40 == No PDP context activated
    int32_t maxDataCalls;                 // The maximum number of simultaneous Data Calls that
                                          // must be established using setupDataCall().
    RIL_CellIdentity_V1_2 cellIdentity;   // Current cell information
}RIL_DataRegistrationStateResponse_V1_2;

typedef enum {
    /**
     * Cell is not a serving cell.
     */
    NONE = 0,
    /**
     * UE has connection to cell for signalling and possibly data (3GPP 36.331, 25.331).
     */
    PRIMARY_SERVING,
    /**
     * UE has connection to cell for data (3GPP 36.331, 25.331).
     */
    SECONDARY_SERVING,
} RIL_CellConnectionStatus;

typedef struct {
    RIL_CellIdentityGsm_V1_2   cellIdentityGsm;
    RIL_GSM_SignalStrength_v12 signalStrengthGsm;
} RIL_CellInfoGsm_V1_2;

typedef struct {
    RIL_CellIdentityCdma_V1_2      cellIdentityCdma;
    RIL_CDMA_SignalStrength   signalStrengthCdma;
    RIL_EVDO_SignalStrength   signalStrengthEvdo;
} RIL_CellInfoCdma_V1_2;

typedef struct {
    RIL_CellIdentityLte_V1_2    cellIdentityLte;
    RIL_LTE_SignalStrength_v8  signalStrengthLte;
} RIL_CellInfoLte_V1_2;

typedef struct {
    RIL_CellIdentityWcdma_V1_2 cellIdentityWcdma;
    RIL_WCDMA_SignalStrength_V1_2 signalStrengthWcdma;
} RIL_CellInfoWcdma_V1_2;

typedef struct {
    RIL_CellIdentityTdscdma_V1_2 cellIdentityTdscdma;
    RIL_TD_SCDMA_SignalStrength_V1_2 signalStrengthTdscdma;
} RIL_CellInfoTdscdma_V1_2;

typedef struct {
    RIL_CellInfoType  cellInfoType;   /* cell type for selecting from union CellInfo */
    int               registered;     /* !0 if this cell is registered 0 if not registered */
    RIL_TimeStampType timeStampType;  /* type of time stamp represented by timeStamp */
    uint64_t          timeStamp;      /* Time in nanos as returned by ril_nano_time */
    union {
        RIL_CellInfoGsm_V1_2 gsm;
        RIL_CellInfoCdma_V1_2 cdma;
        RIL_CellInfoLte_V1_2 lte;
        RIL_CellInfoWcdma_V1_2 wcdma;
        RIL_CellInfoTdscdma_V1_2 tdscdma;
    } CellInfo;
    RIL_CellConnectionStatus connectionStatus;
} RIL_CellInfo_V1_2;

typedef enum {
    NORMAL    = 0x01,
    SHUTDOWN  = 0x02,
    HANDOVER  = 0x03,
    PDP_RESET = 0x04
} RIL_DataRequestReason;


typedef enum {
    ACCESS_NETWORK_UNKNOWN   = 0,
    ACCESS_NETWORK_GERAN     = 1,
    ACCESS_NETWORK_UTRAN     = 2,
    ACCESS_NETWORK_EUTRAN    = 3,
    ACCESS_NETWORK_CDMA2000  = 4,
    ACCESS_NETWORK_IWLAN     = 5,
} RIL_AccessNetwork;

/**
 * values are in seconds
 */
enum {
    SCAN_INTERVAL_MIN = 5,
    SCAN_INTERVAL_MAX = 300,
} RIL_ScanIntervalRange;

/**
 * value are in seconds
 */
enum {
    MAX_SEARCH_TIME_MIN = 60,
    MAX_SEARCH_TIME_MAX = 3600,
} RIL_MaxSearchTimeRange;

/**
 * values are in seconds
 */
typedef enum {
    INCREMENT_PERIODIC_MIN = 1,
    INCREMENT_PERIODIC_MAX = 10,
} RIL_IncrementalResultsPeriodicityRange;

typedef struct {
    RIL_ScanType type;                        // Type of the scan
    int32_t interval;                         // Time interval in seconds
                                              // between periodic scans, only
                                              // valid when type=RIL_PERIODIC
    uint32_t specifiers_length;               // Length of specifiers
    RIL_RadioAccessSpecifier specifiers[MAX_RADIO_ACCESS_NETWORKS]; // Radio access networks
                                                                    // with bands/channels.
    int32_t maxSearchTime;                    // Maximum duration of the periodic search (in seconds).
                                              // Expected range for the input is [MaxSearchTimeRange:MIN - MaxSearchTimeRange:MAX]
                                              //If the search lasts maxSearchTime, it must be terminated.
    bool incrementalResults;                  // Indicates whether the modem must report incremental results of the network scan to the client.
                                              // 0 Incremental results must not be reported.
                                              // 1  Incremental must be reported.
    int32_t incrementalResultsPeriodicity;    // Indicates the periodicity with which the modem must report incremental results to
                                              // the client (in seconds).
                                              // Expected range for the input is
                                              // [RIL_IncrementalResultsPeriodicityRange:MIN - RIL_IncrementalResultsPeriodicityRange:MAX]
                                              // This value must be less than or equal to maxSearchTime.
    int32_t numOfMccMncs;                     // A size of vector of mccMncs.
    char **mccMncs;                           // Describes the List of PLMN ids (MCC-MNC)
                                              // If any PLMN of this list is found, search must end at that point and results with all
                                              // PLMN found until that point should be sent as response.
                                              // If the list is not sent, search to be completed until end and all PLMNs found to be reported.
} RIL_NetworkScanRequest_V1_2;

typedef struct {
    RIL_ScanStatus status;              // The status of the scan
    uint32_t network_infos_length;      // Total length of RIL_CellInfo
    RIL_CellInfo_V1_2* network_infos;   // List of network information
    RIL_Errno error;
} RIL_NetworkScanResult_V1_2;

typedef struct  {
    uint32_t downlinkCapacityKbps;
    uint32_t uplinkCapacityKbps;
} RIL_LinkCapacityEstimate;

typedef struct  {
    RIL_CellConnectionStatus status;
    int32_t cellBandwidthDownlink;
} RIL_PhysicalChannelConfig;

/**
 * RIL_REQUEST_SETUP_DATA_CALL
 *
 * Setup a packet data connection. If RIL_Data_Call_Response_v6.status
 * return success it is added to the list of data calls and a
 * RIL_UNSOL_DATA_CALL_LIST_CHANGED is sent. The call remains in the
 * list until RIL_REQUEST_DEACTIVATE_DATA_CALL is issued or the
 * radio is powered off/on. This list is returned by RIL_REQUEST_DATA_CALL_LIST
 * and RIL_UNSOL_DATA_CALL_LIST_CHANGED.
 *
 * The RIL is expected to:
 *  - Create one data call context.
 *  - Create and configure a dedicated interface for the context
 *  - The interface must be point to point.
 *  - The interface is configured with one or more addresses and
 *    is capable of sending and receiving packets. The prefix length
 *    of the addresses must be /32 for IPv4 and /128 for IPv6.
 *  - Must NOT change the linux routing table.
 *  - Support up to RIL_REQUEST_DATA_REGISTRATION_STATE response[5]
 *    number of simultaneous data call contexts.
 *
 * "data" is a const char **
 * ((const char **)data)[0] Radio technology to use: 0-CDMA, 1-GSM/UMTS, 2...
 *                          for values above 2 this is RIL_RadioTechnology + 2.
 * ((const char **)data)[1] is a RIL_DataProfile (support is optional)
 * ((const char **)data)[2] is the APN to connect to if radio technology is GSM/UMTS. This APN will
 *                          override the one in the profile. NULL indicates no APN overrride.
 * ((const char **)data)[3] is the username for APN, or NULL
 * ((const char **)data)[4] is the password for APN, or NULL
 * ((const char **)data)[5] is the PAP / CHAP auth type. Values:
 *                          0 => PAP and CHAP is never performed.
 *                          1 => PAP may be performed; CHAP is never performed.
 *                          2 => CHAP may be performed; PAP is never performed.
 *                          3 => PAP / CHAP may be performed - baseband dependent.
 * ((const char **)data)[6] is the non-roaming/home connection type to request. Must be one of the
 *                          PDP_type values in TS 27.007 section 10.1.1.
 *                          For example, "IP", "IPV6", "IPV4V6", or "PPP".
 * ((const char **)data)[7] is the roaming connection type to request. Must be one of the
 *                          PDP_type values in TS 27.007 section 10.1.1.
 *                          For example, "IP", "IPV6", "IPV4V6", or "PPP".
 * ((const char **)data)[8] is the bitmask of APN type in decimal string format. The
 *                          bitmask will encapsulate the following values:
 *                          ia,mms,agps,supl,hipri,fota,dun,ims,default.
 * ((const char **)data)[9] is the bearer bitmask in decimal string format. Each bit is a
 *                          RIL_RadioAccessFamily. "0" or NULL indicates all RATs.
 * ((const char **)data)[10] is the boolean in string format indicating the APN setting was
 *                           sent to the modem through RIL_REQUEST_SET_DATA_PROFILE earlier.
 * ((const char **)data)[11] is the mtu size in bytes of the mobile interface to which
 *                           the apn is connected.
 * ((const char **)data)[12] is the MVNO type:
 *                           possible values are "imsi", "gid", "spn".
 * ((const char **)data)[13] is MVNO match data in string. Can be anything defined by the carrier.
 *                           For example,
 *                           SPN like: "A MOBILE", "BEN NL", etc...
 *                           IMSI like: "302720x94", "2060188", etc...
 *                           GID like: "4E", "33", etc...
 * ((const char **)data)[14] is the boolean string indicating data roaming is allowed or not. "1"
 *                           indicates data roaming is enabled by the user, "0" indicates disabled.
 * ((const char **)data)[15] The request reason. Must be DataRequestReason.NORMAL(0x01) or DataRequestReason.HANDOVER(0x03).
 * ((const char **)data)[16] If the reason is DataRequestReason.HANDOVER, this indicates the list of link
 *                           addresses of the existing data connection. The format is IP address with optional "/"
 *                           prefix length (The format is defined in RFC-4291 section 2.3). For example, "192.0.1.3",
 *                           "192.0.1.11/16", or "2001:db8::1/64". Typically one IPv4 or one IPv6 or one of each. If
 *                           the prefix length is absent, then the addresses are assumed to be point to point with
 *                           IPv4 with prefix length 32 or IPv6 with prefix length 128. This parameter must be ignored
 * ((const char **)data)[17] If the reason is DataRequestReason.HANDOVER, this indicates the list of DNS
 *                           addresses of the existing data connection. The format is defined in RFC-4291 section
 *                           2.2. For example, "192.0.1.3" or "2001:db8::1". This parameter must be ignored unless
 *                           reason is DataRequestReason.HANDOVER.
 *
 * "response" is a RIL_Data_Call_Response_v11
 *
 * FIXME may need way to configure QoS settings
 *
 * Valid errors:
 *  SUCCESS should be returned on both success and failure of setup with
 *  the RIL_Data_Call_Response_v6.status containing the actual status.
 *  For all other errors the RIL_Data_Call_Resonse_v6 is ignored.
 *
 *  Other errors could include:
 *    RADIO_NOT_AVAILABLE, OP_NOT_ALLOWED_BEFORE_REG_TO_NW,
 *    OP_NOT_ALLOWED_DURING_VOICE_CALL, REQUEST_NOT_SUPPORTED,
 *    INVALID_ARGUMENTS, INTERNAL_ERR, NO_MEMORY, NO_RESOURCES,
 *    CANCELLED and SIM_ABSENT
 *
 * See also: RIL_REQUEST_DEACTIVATE_DATA_CALL
 */
#define RIL_REQUEST_SETUP_DATA_CALL 27


/**
 * RIL_REQUEST_DEACTIVATE_DATA_CALL
 *
 * Deactivate packet data connection and remove from the
 * data call list if SUCCESS is returned. Any other return
 * values should also try to remove the call from the list,
 * but that may not be possible. In any event a
 * RIL_REQUEST_RADIO_POWER off/on must clear the list. An
 * RIL_UNSOL_DATA_CALL_LIST_CHANGED is not expected to be
 * issued because of an RIL_REQUEST_DEACTIVATE_DATA_CALL.
 *
 * "data" is const char **
 * ((char**)data)[0] indicating CID
 * ((char**)data)[1] The request reason. Must be normal, handover, or shutdown.
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
 *  INTERNAL_ERR
 *  NO_MEMORY
 *  NO_RESOURCES
 *  CANCELLED
 *  SIM_ABSENT
 *
 * See also: RIL_REQUEST_SETUP_DATA_CALL
 */
#define RIL_REQUEST_DEACTIVATE_DATA_CALL 41

/**
 * RIL_REQUEST_SET_UNSOLICITED_RESPONSE_FILTER
 *
 * Sets the indication filter.
 *
 * Prevents the reporting of specified unsolicited indications from the radio. This is used
 * for power saving in instances when those indications are not needed. If unset, defaults to
 * @1.2::IndicationFilter:ALL.
 *
 * "data" is an int *
 *
 * ((int *)data)[0] 32-bit bitmap of IndicationFilter. Bits set to 1 indicate the
 *                  indications are enabled. See @1.2::IndicationFilter for the definition of each bit.
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  INVALID_ARGUMENTS (e.g. the requested filter doesn't exist)
 *  RADIO_NOT_AVAILABLE (radio resetting)
 *  NO_MEMORY
 *  INTERNAL_ERR
 *  SYSTEM_ERR
 *  REQUEST_NOT_SUPPORTED
 *  NO_RESOURCES
 *  CANCELLED
 */
#define RIL_REQUEST_SET_UNSOLICITED_RESPONSE_FILTER 139

/**
 * RIL_REQUEST_START_NETWORK_SCAN
 *
 * Starts a new network scan
 *
 * Request to start a network scan with specified radio access networks with frequency bands and/or
 * channels.
 *
 * "data" is a const RIL_NetworkScanRequest_V1_2 *.
 *        Defines the radio networks/bands/channels which need to be scanned.
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  OPERATION_NOT_ALLOWED
 *  DEVICE_IN_USE
 *  INTERNAL_ERR
 *  NO_MEMORY
 *  MODEM_ERR
 *  INVALID_ARGUMENTS
 *  REQUEST_NOT_SUPPORTED
 *  NO_RESOURCES
 *  CANCELLED
 *
 */
#define RIL_REQUEST_START_NETWORK_SCAN 142

typedef struct {
    uint32_t hysteresisMs;              // A hysteresis time in milliseconds to prevent flapping.
                                        // A value of 0 disables hysteresis.
    uint32_t hysteresisDb;              // An interval in dB defining the required magnitude change between reports.
                                        // hysteresisDb must be smaller than the smallest threshold delta.
                                        // An interval value of 0 disables hysteresis.
    uint32_t numOfThresholdsDbm;        // A size of vector of trigger thresholds.
    uint32_t *thresholdsDbm;            // A vector of trigger thresholds in dBm. A vector size of 0 disables the
                                        // use of thresholds for reporting.
    RIL_AccessNetwork accessNetwork;    // The type of network for which to apply these thresholds.
} RIL_SignalStrengthReportingCriteria_V1_2;

/**
 * RIL_REQUEST_SET_SIGNAL_STRENGTH_REPORTING_CRITERIA
 *
 * Sets the signal strength reporting criteria.
 *
 * The resulting reporting criteria are the AND of all the supplied criteria.
 *
 * Note: Reporting criteria must be individually set for each RAN. If unset, reporting criteria
 * for that RAN are implementation-defined.
 *
 * "data" is a const RIL_SignalStrengthReportingCriteria_V1_2 *.
 * "response" is NULL
 *
 * Valid errors returned:
 *   SUCCESS
 *   INVALID_ARGUMENTS
 *   RADIO_NOT_AVAILABLE
 *   INTERNAL_ERR
 */
#define RIL_REQUEST_SET_SIGNAL_STRENGTH_REPORTING_CRITERIA 202


typedef struct {
    uint32_t hysteresisMs;                // A hysteresis time in milliseconds to prevent flapping.
                                          // A value of 0 disables hysteresis.
    uint32_t hysteresisDlKbps;            // An interval in kbps defining the required magnitude change between DL reports.
                                          // hysteresisDlKbps must be smaller than the smallest threshold delta.
                                          // An interval value of 0 disables hysteresis.
    uint32_t hysteresisUlKbps;            // An interval in kbps defining the required magnitude change between UL reports.
                                          // hysteresisUlKbps must be smaller than the smallest threshold delta.
                                          // An interval value of 0 disables hysteresis.
    uint32_t numOfThresholdsDownlinkKbps; // A size of vector of trigger thresholdsDownlinkKbps.
    uint32_t* thresholdsDownlinkKbps;     // A vector of trigger thresholds in kbps for downlink reports.
                                          // A vector size of 0 disables the use of DL thresholds for reporting.
    uint32_t numOfThresholdsUplinkKbps;   // A size of vector of trigger thresholdsUplinkKbps.
    uint32_t* thresholdsUplinkKbps;       // A vector of trigger thresholds in kbps for uplink reports.
                                          // A vector size of 0 disables the use of UL thresholds for reporting.
    RIL_AccessNetwork accessNetwork;      // The type of network for which to apply these thresholds.
} RIL_LinkCapacityReportingCriteria_V1_2;

/**
 * RIL_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA
 *
 * Sets the link capacity reporting criteria.
 *
 * The resulting reporting criteria are the AND of all the supplied criteria.
 *
 * Note: Reporting criteria must be individually set for each RAN. If unset, reporting criteria
 * for that RAN are implementation-defined.
 *
 * "data" is a const RIL_LinkCapacityReportingCriteria_V1_2 *.
 * "response" is NULL
 *
 * Valid errors returned:
 *   SUCCESS
 *   INVALID_ARGUMENTS
 *   RADIO_NOT_AVAILABLE
 *   INTERNAL_ERR
 */
#define RIL_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA 203

/***********************************************************************/

/**
 * RIL_UNSOL_PHYSICAL_CHANNEL_CONFIG
 *
 * "data" is a const RIL_PhysicalChannelConfig.
 */
#define RIL_UNSOL_PHYSICAL_CHANNEL_CONFIG 1101

#endif // __RADIO_V1_2_H__

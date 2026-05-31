/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RADIO_V1_4_H__
#define __RADIO_V1_4_H__

#include <telephony/ril.h>

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
  /**
   * The EID is the eUICC identifier. The EID shall be stored within the ECASD and can be
   * retrieved by the Device at any time using the standard GlobalPlatform GET DATA command.
   *
   * This data is mandatory and applicable only when cardState is CardState:PRESENT and SIM card
   * supports eUICC.
   */
  char *eid;
} RIL_CardStatus_V1_4;

typedef enum {
    RADIO_TECH_NR = 20,
} RIL_RadioTechnology_V1_4;

typedef enum {
    RAF_NR = (1 << RADIO_TECH_NR),
} RIL_RadioAccessFamily_V1_4;

typedef enum {
    RIL_APN_MCX = (1 << 10),    // APN type for Mission Critical Service
                                // Reference: 3GPP TS 22.280 V15.3.0
} RIL_ApnTypes_V1_4;

// base types are defined in ril.h
typedef enum {
  RIL_CELL_INFO_TYPE_NR  = 6
} RIL_CellInfoType_V1_4;

/**
 * Type to define the LTE specific network capabilities for voice over PS including
 * emergency and normal voice calls.
 */
typedef struct {
    /**
     * This indicates if camped network support VoLTE services. This information is received
     * from LTE network during LTE NAS registration procedure through LTE ATTACH ACCEPT/TAU
     * ACCEPT. Refer 3GPP 24.301 EPS network feature support -> IMS VoPS
     */
    bool isVopsSupported;
    /**
     * This indicates if camped network support VoLTE emergency bearers. This information
     * is received from LTE network through two sources:
     * a. During LTE NAS registration procedure through LTE ATTACH ACCEPT/TAU ACCEPT. Refer
     *    3GPP 24.301 EPS network feature support -> EMC BS
     * b. In case device is not registered on network. Refer 3GPP 25.331 LTE RRC
     *    SIB1 : ims-EmergencySupport-r9
     * If device is registered on LTE, then this field indicates (a).
     * In case of limited service on LTE this field indicates (b).
     */
    bool isEmcBearerSupported;
} RIL_LteVopsInfo;

/** The parameters of NR 5G Non-Standalone. */
typedef struct {
    /**
     * Indicates that if E-UTRA-NR Dual Connectivity (EN-DC) is supported by the primary serving
     * cell.
     *
     * True the primary serving cell is LTE cell and the plmn-InfoList-r15 is present in SIB2 and
     * at least one bit in this list is true, otherwise this value should be false.
     *
     * Reference: 3GPP TS 36.331 v15.2.2 6.3.1 System information blocks.
     */
    bool isEndcAvailable;

    /**
     * True if use of dual connectivity with NR is restricted.
     * Reference: 3GPP TS 24.301 v15.03 section 9.3.3.12A.
     */
    bool isDcNrRestricted;

    /**
     * True if the bit N is in the PLMN-InfoList-r15 is true and the selected PLMN is present in
     * plmn-IdentityList at position N.
     * Reference: 3GPP TS 36.331 v15.2.2 section 6.3.1 PLMN-InfoList-r15.
     *            3GPP TS 36.331 v15.2.2 section 6.2.2 SystemInformationBlockType1 message.
     */
    bool isNrAvailable;
} RIL_NrIndicators;

/**
 * Specifies the type of packet data protocol which is defined in TS 27.007 section 10.1.1.
 */
typedef enum {
    /**
     * Unknown protocol
     */
    PDP_PROTOCOL_TYPE_UNKNOWN = -1,
    /**
     * Internet protocol
     */
    PDP_PROTOCOL_TYPE_IP = 0,
    /**
     * Internet protocol, version 6
     */
    PDP_PROTOCOL_TYPE_IPV6 = 1,
    /**
     * Virtual PDP type introduced to handle dual IP stack UE capability.
     */
    PDP_PROTOCOL_TYPE_IPV4V6 = 2,
    /**
     * Point to point protocol
     */
    PDP_PROTOCOL_TYPE_PPP = 3,
    /**
     * Transfer of Non-IP data to external packet data network
     */
    PDP_PROTOCOL_TYPE_NON_IP = 4,
    /**
     * Transfer of Unstructured data to the Data Network via N6
     */
    PDP_PROTOCOL_TYPE_UNSTRUCTURED = 5,
} PdpProtocolType;


/**
 * Overwritten from @1.0::DataProfileInfo in order to deprecate 'mvnoType', and 'mvnoMatchData'.
 * In the future, this must be extended instead of overwritten.
 * Also added 'preferred' and 'persistent' in this version.
 */
typedef struct {
    /** id of the data profile */
    int profileId;

    /** The APN name */
    char *apn;

    /** PDP_type values */
    int protocol;

    /** PDP_type values used on roaming network */
    int roamingProtocol;

    /** APN authentication type */
    int authType;

    /** The username for APN, or empty string */
    char *user;

    /** The password for APN, or empty string */
    char *password;

    /** Data profile technology type */
    int type;

    /** The period in seconds to limit the maximum connections */
    int maxConnsTime;

    /** The maximum connections during maxConnsTime */
    int maxConns;

    /**
     * The required wait time in seconds after a successful UE initiated disconnect of a given PDN
     * connection before the device can send a new PDN connection request for that given PDN.
     */
    int waitTime;

    /** True to enable the profile, false to disable */
    bool enabled;

    /** Supported APN types bitmap. See ApnTypes for the value of each bit. */
    int supportedApnTypesBitmap;

    /** The bearer bitmap. See RadioAccessFamily for the value of each bit. */
    int bearerBitmap;

    /** Maximum transmission unit (MTU) size in bytes */
    int mtu;

    /**
     * True if this data profile was used to bring up the last default (i.e internet) data
     * connection successfully.
     */
    bool preferred;

    /**
     * If true, modem must persist this data profile and profileId must not be
     * set to DataProfileId.INVALID. If the same data profile exists, this data profile must
     * overwrite it.
     */
    bool persistent;
} RIL_DataProfileInfo_V1_4;

typedef struct {
    int accessNetwork;
    RIL_DataProfileInfo_V1_4 dataProfileInfo;
    bool roamingAllow;
    int reason;
    char *addresses;
    char *dnses;
} RIL_SetupDataCallInfo_V1_4;

/**
 * Overwritten from @1.0::SetupDataCallResult in order to update the DataCallFailCause to 1.4
 * version.
 */
typedef struct {
    /** Data call fail cause. DataCallFailCause.NONE if no error. */
    int cause;

    /**
     * If status != DataCallFailCause.NONE, this field indicates the suggested retry back-off timer
     * value RIL wants to override the one pre-configured in FW. The unit is milliseconds.
     * The value < 0 means no value is suggested.
     * The value 0 means retry must be done ASAP.
     * The value of INT_MAX(0x7fffffff) means no retry.
     */
    int suggestedRetryTime;

    /** Context ID, uniquely identifies this call. */
    int cid;

    /** Data connection active status. */
    int active;

    /**
     * PDP_type values. If cause is DataCallFailCause.ONLY_SINGLE_BEARER_ALLOWED, this is the type
     * supported such as "IP" or "IPV6".
     */
    int type;

    /** The network interface name. */
    char *ifname;

    /**
     * List of addresses with optional "/" prefix length, e.g., "192.0.1.3" or
     * "192.0.1.11/16 2001:db8::1/64".  Typically one IPv4 or one IPv6 or one of each. If the
     * prefix length is absent the addresses are assumed to be point to point with IPv4 having a
     * prefix length of 32 and IPv6 128.
     */
    int len_addresses;
    char **addresses;

    /**
     * List of DNS server addresses, e.g., "192.0.1.3" or "192.0.1.11 2001:db8::1". Empty if no dns
     * server addresses returned.
     */
    int len_dnses;
    char **dnses;

    /**
     * List of default gateway addresses, e.g., "192.0.1.3" or "192.0.1.11 2001:db8::1".
     * When empty, the addresses represent point to point connections.
     */
    int len_gateways;
    char **gateways;

    /**
     * List of P-CSCF(Proxy Call State Control Function) addresses via PCO(Protocol Configuration
     * Option), e.g., "2001:db8::1 2001:db8::2 2001:db8::3". Empty if not IMS client.
     */
    int len_pcscf;
    char **pcscf;

    /**
     * MTU received from network. Value <= 0 means network has either not sent a value or sent an
     * invalid value.
     */
    int mtu;
} RIL_Data_Call_Response_V1_4;


/** Contains the configuration of the LTE cell tower. */
typedef struct {
    /**
     * Indicates that if E-UTRA-NR Dual Connectivity (EN-DC) is supported by the LTE cell.
     *
     * True if the plmn-InfoList-r15 is present in SIB2 and at least one bit in this list is true,
     * otherwise this value should be false.
     *
     * Reference: 3GPP TS 36.331 v15.2.2 6.3.1 System information blocks.
     */
    bool isEndcAvailable;
} RIL_CellConfigLte;

/** Inherits from @1.2::CellInfoLte, in order to add the LTE configuration. */
typedef struct {
    RIL_CellInfoLte_V1_2 cellInfo;
    RIL_CellConfigLte cellConfig;
} RIL_CellInfoLte_V1_4;

typedef struct {
    /** 3-digit Mobile Country Code, in range[0, 999]; This value must be valid for registered or
     *  camped cells; INT_MAX means invalid/unreported.
     */
    int mcc;

    /**
     * 2 or 3-digit Mobile Network Code, in range [0, 999], This value must be valid for
     * registered or camped cells; INT_MAX means invalid/unreported.
     */
    int mnc;

    /**
     * NR Cell Identity in range [0, 68719476735] (36 bits) described in 3GPP TS 38.331, which
     * unambiguously identifies a cell within a PLMN. This value must be valid for registered or
     * camped cells; LONG_MAX (2^63-1) means invalid/unreported.
     */
    uint64_t nci;

    /**
     * Physical cell id in range [0, 1007] described in 3GPP TS 38.331. This value must be valid.
     */
    uint32_t pci;

    /** 16-bit tracking area code, INT_MAX means invalid/unreported. */
    int32_t tac;

    /**
     * NR Absolute Radio Frequency Channel Number, in range [0, 3279165].
     * Reference: 3GPP TS 38.101-1 and 3GPP TS 38.101-2 section 5.4.2.1.
     * This value must be valid.
     */
    int32_t nrarfcn;

    CellIdentityOperatorNames operatorNames;
} RIL_CellIdentityNr_V1_4;

typedef struct {
    /**
     * SS reference signal received power, multipled by -1.
     *
     * Reference: 3GPP TS 38.215.
     *
     * Range [44, 140], INT_MAX means invalid/unreported.
     */
    int ssRsrp;

    /**
     * SS reference signal received quality, multipled by -1.
     *
     * Reference: 3GPP TS 38.215.
     *
     * Range [3, 20], INT_MAX means invalid/unreported.
     */
    int ssRsrq;

    /**
     * SS signal-to-noise and interference ratio.
     *
     * Reference: 3GPP TS 38.215 section 5.1.*, 3GPP TS 38.133 section 10.1.16.1.
     *
     * Range [-23, 40], INT_MAX means invalid/unreported.
     */
    int ssSinr;

    /**
     * CSI reference signal received power, multipled by -1.
     *
     * Reference: 3GPP TS 38.215.
     *
     * Range [44, 140], INT_MAX means invalid/unreported.
     */
    int csiRsrp;

    /**
     * CSI reference signal received quality, multipled by -1.
     *
     * Reference: 3GPP TS 38.215.
     *
     * Range [3, 20], INT_MAX means invalid/unreported.
     */
    int csiRsrq;

    /**
     * CSI signal-to-noise and interference ratio.
     *
     * Reference: 3GPP TS 138.215 section 5.1.*, 3GPP TS 38.133 section 10.1.16.1.
     *
     * Range [-23, 40], INT_MAX means invalid/unreported.
     */
    int csiSinr;
} RIL_NR_SignalStrength_V1_4;

typedef struct CellInfoNr {
    RIL_CellIdentityNr_V1_4 cellidentityNr;
    RIL_NR_SignalStrength_V1_4 signalStrengthNr;
} RIL_CellInfoNr_V1_4;

typedef struct {
    RIL_CellInfoType  cellInfoType;   /* cell type for selecting from union CellInfo */
    int               registered;     /* !0 if this cell is registered 0 if not registered */
    RIL_TimeStampType timeStampType;  /* type of time stamp represented by timeStamp */
    uint64_t          timeStamp;      /* Time in nanos as returned by ril_nano_time */
    union {
        RIL_CellInfoGsm_V1_2 gsm;
        RIL_CellInfoCdma_V1_2 cdma;
        RIL_CellInfoWcdma_V1_2 wcdma;
        RIL_CellInfoTdscdma_V1_2 tdscdma;
        RIL_CellInfoLte_V1_4 lte;
        RIL_CellInfoNr_V1_4 nr;
    } CellInfo;
    RIL_CellConnectionStatus connectionStatus;
} RIL_CellInfo_V1_4;

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
    RIL_LteVopsInfo lteVopsInfo;
    RIL_NrIndicators nrIndicators;
}RIL_DataRegistrationStateResponse_V1_4;

/** Overwritten from @1.2::SignalStrength in order to add signal strength for NR.  */
typedef struct {
    RIL_GSM_SignalStrength_v12  GSM_SignalStrength;
    RIL_CDMA_SignalStrength     CDMA_SignalStrength;
    RIL_EVDO_SignalStrength     EVDO_SignalStrength;
    RIL_LTE_SignalStrength_v8   LTE_SignalStrength;
    RIL_TD_SCDMA_SignalStrength_V1_2 TD_SCDMA_SignalStrength;
    RIL_WCDMA_SignalStrength_V1_2 WCDMA_SignalStrength;
    RIL_NR_SignalStrength_V1_4  NR_SignalStrength;
} RIL_SignalStrength_V1_4;

typedef enum {
    /**
     * Indicates that configuration applies to each slot independently.
     */
    NO_MULTISIM_POLICY = 0,
    /**
     * Indicates that any SIM card can be used as far as one valid card is present in the device.
     * For the modem, a SIM card is valid when its content (i.e. MCC, MNC, GID, SPN) matches the
     * carrier restriction configuration.
     */
    ONE_VALID_SIM_MUST_BE_PRESENT = 1,
} RIL_SimLockMultiSimPolicy;

typedef struct {
  int32_t len_allowed_carriers;         /* length of array allowed_carriers */
  int32_t len_excluded_carriers;        /* length of array excluded_carriers */
  RIL_Carrier * allowed_carriers;       /* whitelist for allowed carriers */
  RIL_Carrier * excluded_carriers;      /* blacklist for explicitly excluded carriers
                                         * which match allowed_carriers. Eg. allowed_carriers match
                                         * mcc/mnc, excluded_carriers has same mcc/mnc and gid1
                                         * is ABCD. It means except the carrier whose gid1 is ABCD,
                                         * all carriers with the same mcc/mnc are allowed.
                                         */
  /**
   * True means that only carriers included in the allowed list and not in the excluded list
   * are permitted. Eg. allowedCarriers match mcc/mnc, excludedCarriers has same mcc/mnc and
   * gid1 is ABCD. It means except the carrier whose gid1 is ABCD, all carriers with the
   * same mcc/mnc are allowed.
   * False means that all carriers are allowed except those included in the excluded list
   * and not in the allowed list.
   */
  bool allowedCarriersPrioritized;
} RIL_CarrierRestrictionsWithPriority;

typedef struct {
    RIL_CarrierRestrictionsWithPriority carriers;
    int multiSimPolicy;
} RIL_CarrierRestrictions_V1_4;

typedef struct {
    RIL_ScanStatus status;              // The status of the scan
    uint32_t network_infos_length;      // Total length of RIL_CellInfo
    RIL_CellInfo_V1_4* network_infos;   // List of network information
    RIL_Errno error;
} RIL_NetworkScanResult_V1_4;

/** Mapping the frequency to a rough range. */
enum {
    FREQUENCY_RANGE_UNKNOWN = 0
    ,
    /** Indicates the frequency range is below 1GHz. */
    FREQUENCY_RANGE_LOW = 1,

    /** Indicates the frequency range is between 1GHz and 3GHz. */
    FREQUENCY_RANGE_MID = 2,

    /** Indicates the frequency range is between 3GHz and 6GHz. */
    FREQUENCY_RANGE_HIGH = 3,

    /** Indicates the frequency range is above 6GHz (millimeter wave frequency). */
    FREQUENCY_RANGE_MMWAVE = 4,
};

enum {
    RF_INFO_TYPE_UNKNOWN = 0,
    RF_INFO_TYPE_RANGE = 1,
    RF_INFO_TYPE_CHANNEL_NUMBER = 2,
};

#define MAX_PHYSICAL_CHANNEL_CONFIGS  8

typedef struct {
    int status;
    int cellBandwidthDownlink;

    /** The radio technology for this physical channel. */
    int rat;

    /** range or channel number */
    int rfInfoType;

    /** The radio frequency info. */
    union {
        /** A rough frequency range. */
        int range;
        /** The Absolute Radio Frequency Channel Number. */
        int channelNumber;
    } rfInfo;

    /**
     * A list of data calls mapped to this physical channel. The context id must match the cid of
     * @1.4::SetupDataCallResult. An empty list means the physical channel has no data call mapped
     * to it.
     */
    int len_contextIds;
    int *contextIds;

    /**
     * The physical cell identifier for this cell.
     *
     * In UTRAN, this value is primary scrambling code. The range is [0, 511].
     * Reference: 3GPP TS 25.213 section 5.2.2.
     *
     * In EUTRAN, this value is physical layer cell identity. The range is [0, 503].
     * Reference: 3GPP TS 36.211 section 6.11.
     *
     * In 5G RAN, this value is physical layer cell identity. The range is [0, 1008].
     * Reference: 3GPP TS 38.211 section 7.4.2.1.
     */
    uint32_t physicalCellId;
} RIL_PhysicalChannelConfig_V1_4;

/**
 * Defining Emergency Service Category as follows:
 * - General emergency call, all categories;
 * - Police;
 * - Ambulance;
 * - Fire Brigade;
 * - Marine Guard;
 * - Mountain Rescue;
 * - Manually Initiated eCall (MIeC);
 * - Automatically Initiated eCall (AIeC);
 *
 * Category UNSPECIFIED (General emergency call, all categories) indicates that no specific
 * services are associated with this emergency number.
 *
 * Reference: 3gpp 22.101, Section 10 - Emergency Calls
 */
typedef enum EmergencyServiceCategory {
    /**
     * General emergency call, all categories
     */
    RIL_EMERGENCY_CATEGORY_UNSPECIFIED = 0,
    RIL_EMERGENCY_CATEGORY_POLICE = 1 << 0,
    RIL_EMERGENCY_CATEGORY_AMBULANCE = 1 << 1,
    RIL_EMERGENCY_CATEGORY_FIRE_BRIGADE = 1 << 2,
    RIL_EMERGENCY_CATEGORY_MARINE_GUARD = 1 << 3,
    RIL_EMERGENCY_CATEGORY_MOUNTAIN_RESCUE = 1 << 4,
    /**
     * Manually Initiated eCall (MIeC)
     */
    RIL_EMERGENCY_CATEGORY_MIEC = 1 << 5,
    /**
     * Automatically Initiated eCall (AIeC)
     */
    RIL_EMERGENCY_CATEGORY_AIEC = 1 << 6,
} RIL_EmergencyServiceCategory;

/**
 * Indicates how the implementation should handle the emergency call if it is required by Android.
 */
typedef enum EmergencyCallRouting {
    /**
     * Indicates Android does not require how to handle the corresponding emergency call; it is
     * decided by implementation.
     */
    RIL_EMERGENCY_CALL_ROUTING_UNKNOWN = 0,
    /**
     * Indicates the implementation must handle the call through emergency routing.
     */
    RIL_EMERGENCY_CALL_ROUTING_EMERGENCY = 1,
    /**
     * Indicates the implementation must handle the call through normal call routing.
     */
    RIL_EMERGENCY_CALL_ROUTING_NORMAL = 2,
} RIL_EmergencyCallRouting;

typedef struct {
    RIL_Dial dialInfo;
    int32_t categories;
    int32_t len_urns;
    char ** urns;       // the emergency Uniform Resource Names (URN)
    int routing;
    bool hasKnownUserIntentEmergency;
    bool isTesting;
} RIL_EmergencyDial;

/**
 * The source to tell where the corresponding @1.4::EmergencyNumber comes from.
 *
 * Reference: 3gpp 22.101, Section 10 - Emergency Calls
 */
typedef enum EmergencyNumberSource {
    /**
     * Indicates the number is from the network signal.
     */
    RIL_EMERGENCY_NUMBER_SOURCE_NETWORK_SIGNALING = 1 << 0,
    /**
     * Indicates the number is from the sim card.
     */
    RIL_EMERGENCY_NUMBER_SOURCE_SIM = 1 << 1,
    /**
     * Indicates the number is from the modem config.
     */
    RIL_EMERGENCY_NUMBER_SOURCE_MODEM_CONFIG = 1 << 2,
    /**
     * Indicates the number is available as default. Per the reference, 112, 911 must always be
     * available; additionally, 000, 08, 110, 999, 118 and 119 must be available when sim is not
     * present.
     */
    RIL_EMERGENCY_NUMBER_SOURCE_DEFAULT = 1 << 3,
} RIL_EmergencyNumberSource;

/**
 * Emergency number contains information of number, one or more service category(s), zero or more
 * emergency uniform resource names, mobile country code (mcc), mobile network country (mnc) and
 * source(s) that indicate where it comes from.
 *
 */
typedef struct {
    /**
     * The emergency number. The character in the number string should only be the dial pad
     * character('0'-'9', '*', or '#'). For example: 911.
     */
    char *number;
    char *mcc;    /* 3-digit Mobile Country Code, 0..999, INT_MAX if unknown  */
    char *mnc;    /* 2 or 3-digit Mobile Network Code, 0..999;
                   the most significant nibble encodes the number of digits - {2, 3, 0 (unset)};
                   INT_MAX if unknown */
    /**
     * The bitfield of @1.4::EmergencyServiceCategory(s). See @1.4::EmergencyServiceCategory for
     * the value of each bit.
     */
    int32_t categories;
    /**
     * The list of emergency Uniform Resource Names (URN).
     */
    int32_t len_urns;
    char ** urns;       // the emergency Uniform Resource Names (URN)
    /**
     * The bitfield of @1.4::EmergencyNumberSource(s). See @1.4::EmergencyNumberSource for the
     * value of each bit.
     */
    int32_t sources;
} RIL_EmergencyNumber;

/**
 * RIL_REQUEST_GET_SIM_STATUS
 *
 * - support radio@1.4
 *
 * "data" is NULL
 *
 * "response" is const RIL_CardStatus_V1_4 *
 *
 * Valid errors:
 *
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 *  NO_MEMORY
 *  NO_RESOURCES
 *  REQUEST_NOT_SUPPORTED
 */
#define RIL_REQUEST_GET_SIM_STATUS 1

/**
 * RIL_REQUEST_SIGNAL_STRENGTH
 *
 * - support radio@1.4
 *
 * "data" is NULL
 *
 * "response" is a const RIL_SignalStrength_V1_4 *
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 */
#define RIL_REQUEST_SIGNAL_STRENGTH 19

/**
 * RIL_REQUEST_DATA_REGISTRATION_STATE
 *
 * - support radio@1.4
 *
 * "data" is NULL
 * "response" is a const RIL_DataRegistrationStateResponse_V1_4 *
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 *  NOT_PROVISIONED
 */
#define RIL_REQUEST_DATA_REGISTRATION_STATE 21

/**
 * RIL_REQUEST_SETUP_DATA_CALL
 *
 *  - support radio@1.4
 *
 * "data" is RIL_SetupDataCallInfo_V1_4 *
 *
 * "response" is RIL_Data_Call_Response_V1_4 *
 *
 * Note this API is same as 1.2 version except using the 1.4 AccessNetwork as the input param.
 *
 * Valid errors returned:
 *   RIL_E_SUCCESS
 *   RIL_E_RADIO_NOT_AVAILABLE
 *   RIL_E_OP_NOT_ALLOWED_BEFORE_REG_TO_NW
 *   RIL_E_OP_NOT_ALLOWED_DURING_VOICE_CALL
 *   RIL_E_REQUEST_NOT_SUPPORTED
 *   RIL_E_INVALID_ARGUMENTS
 *   RIL_E_INTERNAL_ERR
 *   RIL_E_NO_RESOURCES
 *   RIL_E_SIM_ABSENT
 */
#define RIL_REQUEST_SETUP_DATA_CALL 27

/**
 * RIL_REQUEST_DATA_CALL_LIST
 *
 * - support radio@1.4
 *
 * "data" is NULL
 * "response" is an array of RIL_Data_Call_Response_v11
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE (radio resetting)
 *  INTERNAL_ERR
 *  NO_MEMORY
 *  NO_RESOURCES
 *  REQUEST_NOT_SUPPORTED
 *  SIM_ABSENT
 *
 * See also: RIL_UNSOL_DATA_CALL_LIST_CHANGED
 */

#define RIL_REQUEST_DATA_CALL_LIST 57

/**
 * RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE
 *
 * - support radio@1.4
 *
 * "data" is int *
 * ((int *)data)[0] is a bitmap of RIL_RadioAccessFamily
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE (radio resetting)
 *  OPERATION_NOT_ALLOWED
 *  MODE_NOT_SUPPORTED
 *  INTERNAL_ERR
 *  INVALID_ARGUMENTS
 *  MODEM_ERR
 *  REQUEST_NOT_SUPPORTED
 *  NO_RESOURCES
 */
#define RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE 73

/**
 * RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE
 *
 * - support radio@1.4
 *
 * "data" is NULL
 *
 * "response" is int *
 * ((int *)reponse)[0] is which is a bitmap of RIL_RadioAccessFamily
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 *  INVALID_ARGUMENTS
 *  MODEM_ERR
 *  REQUEST_NOT_SUPPORTED
 *  NO_RESOURCES
 */
#define RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE 74

/**
 * RIL_REQUEST_GET_CELL_INFO_LIST
 *
 *  - support radio@1.4
 *
 * "data" is NULL
 *
 * "response" is an array of RIL_CellInfo_V1_4.
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  INTERNAL_ERR
 *  NO_RESOURCES
 *  REQUEST_NOT_SUPPORTED
 *  SIM_ABSENT
 */
#define RIL_REQUEST_GET_CELL_INFO_LIST 109

/**
 * RIL_REQUEST_SET_CARRIER_RESTRICTIONS
 *
 * - support radio@1.4
 *
 * "data" is const RIL_CarrierRestrictions_V1_4 *
 * A list of allowed carriers and possibly a list of excluded carriers.
 * If data is NULL, means to clear previous carrier restrictions and allow all carriers
 *
 * "response" is NULL
 *
 * Valid errors:
 *  RIL_E_SUCCESS
 *  RIL_E_RADIO_NOT_AVAILABLE
 *  RIL_E_INVALID_ARGUMENTS
 *  RIL_E_REQUEST_NOT_SUPPORTED
 */
#define RIL_REQUEST_SET_CARRIER_RESTRICTIONS 136

/**
 * RIL_REQUEST_GET_CARRIER_RESTRICTIONS
 *
 * - support radio@1.4
 *
 * "data" is NULL
 *
 * "response" is const RIL_CarrierRestrictions_V1_4 *.
 * If response is NULL, it means all carriers are allowed.
 *
 * Valid errors:
 *  RIL_E_SUCCESS
 *  RIL_E_RADIO_NOT_AVAILABLE
 *  RIL_E_REQUEST_NOT_SUPPORTED
 */
#define RIL_REQUEST_GET_CARRIER_RESTRICTIONS 137

/**
 * Initiate emergency voice call, with zero or more emergency service category(s), zero or
 * more emergency Uniform Resource Names (URN), and routing information for handling the call.
 * Android uses this request to make its emergency call instead of using @1.0::IRadio.dial
 * if the 'address' in the 'dialInfo' field is identified as an emergency number by Android.
 *
 * In multi-sim scenario, if the emergency number is from a specific subscription, this radio
 * request is sent through the IRadio service that serves the subscription, no matter of the
 * PUK/PIN state of the subscription and the service state of the radio.
 *
 * Some countries or carriers require some emergency numbers that must be handled with normal
 * call routing if possible or emergency routing. 1) if the 'routing' field is specified as
 * @1.4::EmergencyNumberRouting#NORMAL, the implementation must try the full radio service to
 * use normal call routing to handle the call; if service cannot support normal routing, the
 * implementation must use emergency routing to handle the call. 2) if 'routing' is specified
 * as @1.4::EmergencyNumberRouting#EMERGENCY, the implementation must use emergency routing to
 * handle the call. 3) if 'routing' is specified as @1.4::EmergencyNumberRouting#UNKNOWN,
 * Android does not know how to handle the call.
 *
 * If the dialed emergency number does not have a specified emergency service category, the
 * 'categories' field is set to @1.4::EmergencyServiceCategory#UNSPECIFIED; if the dialed
 * emergency number does not have specified emergency Uniform Resource Names, the 'urns' field
 * is set to an empty list. If the underlying technology used to request emergency services
 * does not support the emergency service category or emergency uniform resource names, the
 * field 'categories' or 'urns' may be ignored.
 *
 * In the scenarios that the 'address' in the 'dialInfo' field has other functions besides the
 * emergency number function, if the 'hasKnownUserIntentEmergency' field is true, the user's
 * intent for this dial request is emergency call, and the modem must treat this as an actual
 * emergency dial; if the 'hasKnownUserIntentEmergency' field is false, Android does not know
 * user's intent for this call.
 *
 * If 'isTesting' is true, this request is for testing purpose, and must not be sent to a real
 * emergency service; otherwise it's for a real emergency call request.
 *
 * TODO : "data" is RIL_EmergencyDial_V1_4
 * Reference: 3gpp 22.101, Section 10 - Emergency Calls;
 *            3gpp 23.167, Section 6 - Functional description;
 *            3gpp 24.503, Section 5.1.6.8.1 - General;
 *            RFC 5031
 *
 * dialInfo RIL_Dial struct
 * categories the Emergency Service Category(s) of the call.
 * urns the emergency Uniform Resource Names (URN)
 * routing the emergency call routing information.
 * hasKnownUserIntentEmergency Flag indicating if user's intent for the emergency call is known.
 * isTesting Flag indicating if this request is for testing purpose.
 *
 * "response" is NULL
 *
 * Valid errors returned:
 *   RIL_E_SUCCESS
 *   RIL_E_RADIO_NOT_AVAILABLE
 *   RIL_E_DIAL_MODIFIED_TO_USSD
 *   RIL_E_DIAL_MODIFIED_TO_SS
 *   RIL_E_DIAL_MODIFIED_TO_DIAL
 *   RIL_E_INVALID_ARGUMENTS
 *   RIL_E_NO_RESOURCES
 *   RIL_E_INTERNAL_ERR
 *   RIL_E_FDN_CHECK_FAILURE
 *   RIL_E_MODEM_ERR
 *   RIL_E_NO_SUBSCRIPTION
 *   RIL_E_NO_NETWORK_FOUND
 *   RIL_E_INVALID_CALL_ID
 *   RIL_E_DEVICE_IN_USE
 *   RIL_E_ABORTED
 *   RIL_E_INVALID_MODEM_STATE
 */
#define RIL_REQUEST_EMERGENCY_DIAL 205

/**
 * RIL_UNSOL_SIGNAL_STRENGTH
 *
 * - support radio@1.4
 *
 * "data" is a const RIL_SignalStrength_V1_4 *
 */
#define RIL_UNSOL_SIGNAL_STRENGTH  1009

/**
 * RIL_UNSOL_DATA_CALL_LIST_CHANGED
 *
 * - support radio@1.4
 *
 * See also: RIL_REQUEST_DATA_CALL_LIST
 */

#define RIL_UNSOL_DATA_CALL_LIST_CHANGED 1010

/**
 * RIL_UNSOL_CELL_INFO_LIST
 *
 *
 *
 * "response" is an array of RIL_CellInfo_V1_4.
 */
#define RIL_UNSOL_CELL_INFO_LIST 1036

/**
 * RIL_UNSOL_NETWORK_SCAN_RESULT
 *
 * - support radio@1.4
 *
 * "response" is a const RIL_NetworkScanResult_V1_4 *
 */
#define RIL_UNSOL_NETWORK_SCAN_RESULT 1049

/**
 * RIL_UNSOL_PHYSICAL_CHANNEL_CONFIG
 *
 * Indicates physical channel configurations.
 *
 * An empty configs list indicates that the radio is in idle mode.
 *
 * "response" is an array of RIL_PhysicalChannelConfig_V1_4
 *    a max size of list is MAX_PHYSICAL_CHANNEL_CONFIGS(TBD).
 */
#define RIL_UNSOL_PHYSICAL_CHANNEL_CONFIG 1101

/**
 * RIL_UNSOL_EMERGENCY_NUMBER_LIST
 *
 * Report the current list of emergency numbers
 *
 * Each emergency number (@1.4::EmergencyNumber) in the emergency number list contains a
 * dialing number, zero or more service category(s), zero or more emergency uniform resource
 * names, mobile country code, mobile network code, and source(s) that indicate where it comes
 * from.
 *
 * Radio must report all the valid emergency numbers with known mobile country code, mobile
 * network code, emergency service categories, and emergency uniform resource names from all
 * available sources including network signaling, sim, modem/oem configuration, and default
 * configuration (112 and 911 must be always available; additionally, 000, 08, 110, 999, 118
 * and 119 must be available when sim is not present). Radio shall not report emergency numbers
 * that are invalid in the current locale. The reported emergency number list must not have
 * duplicate @1.4::EmergencyNumber entries. Please refer the documentation of
 * @1.4::EmergencyNumber to construct each emergency number to report.
 *
 * Radio must report the complete list of emergency numbers whenever the emergency numbers in
 * the list are changed or whenever the client and the radio server are connected.
 *
 * Reference: 3gpp 22.101, Section 10 - Emergency Calls;
 *            3gpp 24.008, Section 9.2.13.4 - Emergency Number List
 *
 * "response" an array of RIL_EmergencyNumber
 */
#define RIL_UNSOL_EMERGENCY_NUMBER_LIST 1102

#endif // __RADIO_V1_4_H__

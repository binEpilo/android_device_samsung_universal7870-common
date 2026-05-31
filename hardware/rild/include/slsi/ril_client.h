/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */


/* RIL CLIENT */
#ifndef _RIL_CLIENT_H
#define _RIL_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#define RIL_SOCKET_UNKNOWN  RIL_SOCKET_NUM


#pragma pack(1)

#define MAX_ALPHA_LONG_NAME     64
#define MAX_ALPHA_SHORT_NAME    32
#define MAX_PLMN_LEN            6
enum {
    OPERATOR_INFO_UNKNOWN,
    OPERATOR_INFO_AVAILABLE,
    OPERATOR_INFO_CURRENT,
    OPERATOR_INFO_FORBIDDEN,
};

typedef struct {
    char alphaLong[MAX_ALPHA_LONG_NAME];    // null-terminated
    char alphaShort[MAX_ALPHA_SHORT_NAME];  // null-terminated
    char numeric[MAX_PLMN_LEN];             // 5 or 6 digits
    int state;
} OEM_OperatorInfo;

#pragma pack()

/**
 *  RILC_REQ_GET_AVAILABLE_NETWORKS
 *
 *  "data" is int RAN(Radio Access Network)
 *         0: all 1: GERAN 2: UTRAN 3: EUTRAN
 *
 *  *response" is an array of OEM_OperatorInfo
 */

/* RILC ERROR STATUS */
#define RILC_STATUS_SUCCESS                     0    /* OK */
#define RILC_STATUS_FAIL                        1    /* Generic failure */
#define RILC_STATUS_NOT_CONNECTED               2    /* Client not connected to RIL */
#define RILC_STATUS_INVALID_PARAM               3    /* Invalid parameter */
#define RILC_STATUS_IO                          4    /* I/O error */
#define RILC_STATUS_NO_RESOURCES                5    /* No resources */
#define RILC_STATUS_REQUEST_NOT_SUPPORTED       6
#define RILC_STATUS_CANCELLED                   7
#define RILC_STATUS_RADIO_NOT_AVAILABLE         10   /*radio off or radio unavailable*/
#define RILC_STATUS_MISSING_RESOURCE            16   /* no logical channel available */
#define RILC_STATUS_NO_SUCH_ELEMENT             17   /* application not found on SIM */
#define RILC_STATUS_NO_MEMORY                   37   /* Not sufficient memory to process the request */
#define RILC_STATUS_INTERNAL_ERR                38   /* Modem hit unexpected error scenario while handling this request */
#define RILC_STATUS_SIM_ERR                     43   /* Received error from SIM card */
#define RILC_STATUS_INVALID_SIM_STATE           45   /* Can not process the request in current SIM state */

/* RILC REQUESTS */
#define RILC_REQ_SYSTEM_MODEM_DUMP          1    /* Force modem dump */
#define RILC_REQ_MISC_SET_ENG_MODE          2    /* Engineer Mode Set Command */
#define RILC_REQ_MISC_SCREEN_LINE           3    /* Screen Line select command */
#define RILC_REQ_MISC_DEBUG_TRACE           4    /* Set Debug Trace*/
#define RILC_REQ_MISC_SET_CARRIER_CONFIG    5    /* Set Carrier Config */
#define RILC_REQ_MISC_SET_ENG_STRING_INPUT  6    /* Set Eng String Input */
#define RILC_REQ_MISC_APN_SETTINGS          7    /* APN Settings */
#define RILC_REQ_MISC_GET_MSL_CODE          8    /* Get MSL code */
#define RILC_REQ_MISC_SET_PIN_CONTROL       9    /* Set Pin control */

#define RILC_REQ_AUDIO_SET_MUTE             10    /* Set mute */
#define RILC_REQ_AUDIO_GET_MUTE             11    /* Get mute status */
#define RILC_REQ_AUDIO_SET_VOLUME           12    /* Set volume level */
#define RILC_REQ_AUDIO_GET_VOLUME           13    /* Get current volume level */
#define RILC_REQ_AUDIO_SET_PATH             14    /* Change audio path */
#define RILC_REQ_AUDIO_GET_PATH             15    /* Get current audio path */
#define RILC_REQ_AUDIO_SET_MIC              16    /* Microphone control */
#define RILC_REQ_AUDIO_GET_MIC              17    /* Get current microphone state */
#define RILC_REQ_AUDIO_SET_AUDIO_CLOCK      18    /* control audio/I2S clock */
#define RILC_REQ_AUDIO_SET_AUDIO_LOOPBACK   19    /* set the audio input/output path for loop back test. */

#define RILC_REQ_MISC_SET_PREFERRED_CALL_CAPA   20
#define RILC_REQ_MISC_GET_PREFERRED_CALL_CAPA   21
#define RILC_REQ_MODEM_RESET                    22
#define RILC_REQ_GET_MANUAL_RAT_MODE            23
#define RILC_REQ_SET_MANUAL_RAT_MODE            24
#define RILC_REQ_GET_FREQUENCY_LOCK             25
#define RILC_REQ_SET_FREQUENCY_LOCK             26
#define RILC_REQ_SET_ENDC_MODE                  27
#define RILC_REQ_GET_ENDC_MODE                  28

#define RILC_REQ_IMS_SET_CONFIGURATION          30  /* Set configuration of IMS service */
#define RILC_REQ_IMS_GET_CONFIGURATION          31  /* Get info. for configuration of IMS */
#define RILC_REQ_IMS_SIM_AUTH                   32  /* SIM authentication */
#define RILC_REQ_IMS_SET_EMERGENCY_CALL_STATUS  33  /* Emergency Call's status from AP to CP */
#define RILC_REQ_IMS_SET_SRVCC_CALL_LIST        34  /* SRVCC feature */
#define RILC_REQ_IMS_GET_GBA_AUTH               35
#define RILC_REQ_IMS_SIM_IO                     36
#define RILC_REQ_NET_GET_IMS_SUPPORT_SERVICE    37
#define RILC_REQ_SET_IMS_TEST_MODE              38
#define RILC_REQ_GET_AVAILABLE_NETWORKS         39 /* getAvilableNetwork with RAN(Radio Access Network) */
#define RILC_REQ_SET_UICC_SUBSCRIPTION          40
#define RILC_REQ_AUDIO_SET_TTY_MODE             41

#define RILC_REQ_WLAN_BASE                      60                           /* base for wlan */
#define RILC_REQ_WLAN_GET_IMSI                  RILC_REQ_WLAN_BASE           /* Get EAP-IMSI */
#define RILC_REQ_WLAN_SIM_AUTHENTICATE         (RILC_REQ_WLAN_BASE+1)        /* EAP 3G/GSM Authenticate */

#define RILC_REQ_IF_BASE                        80
#define RILC_REQ_IF_EXECUTE_AM                  (RILC_REQ_IF_BASE)

#define RILC_REQ_MISC_GET_MANUAL_BAND_MODE       90
#define RILC_REQ_MISC_SET_MANUAL_BAND_MODE       91
#define RILC_REQ_MISC_GET_RF_DESENSE_MODE        92
#define RILC_REQ_MISC_SET_RF_DESENSE_MODE        93
#define RILC_REQ_MISC_STORE_ADB_SERIAL_NUMBER    94
#define RILC_REQ_MISC_READ_ADB_SERIAL_NUMBER     95
#define RILC_REQ_SCAN_RSSI                       96
#define RILC_REQ_FORWARDING_AT_COMMAND           97
#define RILC_REQ_SET_MODEM_LOG_DUMP              98
#define RILC_REQ_SET_ELEVATOR_SENSOR             99

//AIMS support start ---------------------
#define RILC_REQ_AIMS_DIAL                       100
#define RILC_REQ_AIMS_ANSWER                     101
#define RILC_REQ_AIMS_HANGUP                     102
#define RILC_REQ_AIMS_DEREGISTRATION             103
#define RILC_REQ_AIMS_HIDDEN_MENU                104
#define RILC_REQ_AIMS_ADD_PDN_INFO               105
#define RILC_REQ_AIMS_CALL_MANAGE                106
#define RILC_REQ_AIMS_SEND_DTMF                  107
#define RILC_REQ_AIMS_SET_FRAME_TIME             108
#define RILC_REQ_AIMS_GET_FRAME_TIME             109
#define RILC_REQ_AIMS_CALL_MODIFY                110
#define RILC_REQ_AIMS_RESPONSE_CALL_MODIFY       111
#define RILC_REQ_AIMS_TIME_INFO                  112
#define RILC_REQ_AIMS_CONF_CALL_ADD_REMOVE_USER  113
#define RILC_REQ_AIMS_ENHANCED_CONF_CALL         114
#define RILC_REQ_AIMS_GET_CALL_FORWARD_STATUS    115
#define RILC_REQ_AIMS_SET_CALL_FORWARD_STATUS    116
#define RILC_REQ_AIMS_GET_CALL_WAITING           117
#define RILC_REQ_AIMS_SET_CALL_WAITING           118
#define RILC_REQ_AIMS_GET_CALL_BARRING           119
#define RILC_REQ_AIMS_SET_CALL_BARRING           120
#define RILC_REQ_AIMS_SEND_SMS                   121
#define RILC_REQ_AIMS_SEND_EXPECT_MORE           122
#define RILC_REQ_AIMS_SEND_SMS_ACK               123
#define RILC_REQ_AIMS_SEND_ACK_INCOMING_SMS      124
#define RILC_REQ_AIMS_CHG_BARRING_PWD            125
#define RILC_REQ_AIMS_SEND_USSD_INFO             126
#define RILC_REQ_AIMS_GET_PRESENTATION_SETTINGS  127
#define RILC_REQ_AIMS_SET_PRESENTATION_SETTINGS  128
#define RILC_REQ_AIMS_SET_SELF_CAPABILITY        129
#define RILC_REQ_AIMS_HO_TO_WIFI_READY           130
#define RILC_REQ_AIMS_HO_TO_WIFI_CANCEL_IND      131
#define RILC_REQ_AIMS_HO_PAYLOAD_IND             132
#define RILC_REQ_AIMS_HO_TO_3GPP                 133
#define RILC_REQ_AIMS_SEND_ACK_INCOMING_CDMA_SMS 134
#define RILC_REQ_AIMS_MEDIA_STATE_IND            135
#define RILC_REQ_AIMS_DEL_PDN_INFO               136
#define RILC_REQ_AIMS_STACK_START_REQ            137
#define RILC_REQ_AIMS_STACK_STOP_REQ             138
#define RILC_REQ_AIMS_XCAPM_START_REQ            139
#define RILC_REQ_AIMS_XCAPM_STOP_REQ             140
#define RILC_REQ_AIMS_RTT_SEND_TEXT              141
#define RILC_REQ_AIMS_EXIT_EMERGENCY_CB_MODE     142
#define RILC_REQ_AIMS_SET_GEO_LOCATION_INFO      143
#define RILC_REQ_AIMS_CDMA_SEND_SMS              144
#define RILC_REQ_AIMS_SET_PDN_EST_STATUS         145
#define RILC_REQ_AIMS_SET_HIDDEN_MENU_ITEM       146
#define RILC_REQ_AIMS_GET_HIDDEN_MENU_ITEM       147
#define RILC_REQ_AIMS_SET_RTP_RX_STATISTICS      148
//AIMS support end ---------------------

//WFC
#define RILC_REQ_WFC_MEDIA_CHANNEL_CONFIG        151
#define RILC_REQ_WFC_DTMF_START                  152
#define RILC_REQ_WFC_SET_VOWIFI_HO_THRESHOLD     153

/* GPS */
#define RILC_REQ_GPS_BASE                                200
#define RILC_REQ_GPS_SET_FREQUENCY_AIDING               (RILC_REQ_GPS_BASE)
#define RILC_REQ_GPS_GET_LPP_SUPL_REQ_ECID_INFO         (RILC_REQ_GPS_BASE + 1)
#define RILC_REQ_GPS_SET_RRLP_SUPL_REQ_ECID_INFO        (RILC_REQ_GPS_BASE + 2)
#define RILC_REQ_GPS_MO_LOCATION_REQUEST                (RILC_REQ_GPS_BASE + 3)
#define RILC_REQ_GPS_GET_LPP_REQ_SERVING_CELL_INFO      (RILC_REQ_GPS_BASE + 4)
#define RILC_REQ_GPS_SET_SUPL_NI_READY                  (RILC_REQ_GPS_BASE + 5)
#define RILC_REQ_GPS_GET_GSM_EXT_INFO_MSG               (RILC_REQ_GPS_BASE + 21)
#define RILC_REQ_GPS_CONTROL_PLANE_ENABLE               (RILC_REQ_GPS_BASE + 22)
#define RILC_REQ_GPS_GNSS_LPP_PROFILE_SET               (RILC_REQ_GPS_BASE + 23)
// Indication from AP, No resp
#define RILC_REQ_GPS_MEASURE_POS_RSP                    (RILC_REQ_GPS_BASE + 6)
#define RILC_REQ_GPS_RELEASE_GPS                        (RILC_REQ_GPS_BASE + 7)
#define RILC_REQ_GPS_MT_LOCATION_REQUEST                (RILC_REQ_GPS_BASE + 8)
#define RILC_REQ_GPS_LPP_PROVIDE_CAPABILITIES           (RILC_REQ_GPS_BASE + 9)
#define RILC_REQ_GPS_LPP_REQUEST_ASSIST_DATA            (RILC_REQ_GPS_BASE + 10)
#define RILC_REQ_GPS_LPP_PROVIDE_LOCATION_INFO          (RILC_REQ_GPS_BASE + 11)
#define RILC_REQ_GPS_LPP_GPS_ERROR_IND                  (RILC_REQ_GPS_BASE + 12)
#define RILC_REQ_GPS_SUPL_LPP_DATA_INFO                 (RILC_REQ_GPS_BASE + 13)
#define RILC_REQ_GPS_SUPL_NI_MESSAGE                    (RILC_REQ_GPS_BASE + 14)
#define RILC_REQ_GPS_RETRIEVE_LOC_INFO                  (RILC_REQ_GPS_BASE + 24)

/* CDMA & HEDGE GANSS */
#define RILC_REQ_GPS_SET_GANSS_MEAS_POS_RSP             (RILC_REQ_GPS_BASE + 15)
#define RILC_REQ_GPS_SET_GPS_LOCK_MODE                  (RILC_REQ_GPS_BASE + 16)
#define RILC_REQ_GPS_GET_REFERENCE_LOCATION             (RILC_REQ_GPS_BASE + 17)
#define RILC_REQ_GPS_SET_PSEUDO_RANGE_MEASUREMENTS      (RILC_REQ_GPS_BASE + 18)
#define RILC_REQ_GPS_GET_CDMA_PRECISE_TIME_AIDING_INFO  (RILC_REQ_GPS_BASE + 19)
#define RILC_REQ_GPS_CDMA_FREQ_AIDING                   (RILC_REQ_GPS_BASE + 25)
// Indication from AP, No resp
#define RILC_REQ_GPS_GANSS_AP_POS_CAP_RSP               (RILC_REQ_GPS_BASE + 20)

/* Seceure Element */
#define RILC_REQ_SE_BASE                                300
#define RILC_REQ_SE_OPEN_CHANNEL                        (RILC_REQ_SE_BASE)
#define RILC_REQ_SE_TRANSMIT_APDU_LOGICAL               (RILC_REQ_SE_BASE + 1)
#define RILC_REQ_SE_TRANSMIT_APDU_BASIC                 (RILC_REQ_SE_BASE + 2)
#define RILC_REQ_SE_CLOSE_CHANNEL                       (RILC_REQ_SE_BASE + 3)
#define RILC_REQ_SE_GET_ICC_ATR                         (RILC_REQ_SE_BASE + 4)
#define RILC_REQ_SE_GET_CARD_PRESENT                    (RILC_REQ_SE_BASE + 5)

/* eMBMS */
#define RILC_REQ_EMBMS_BASE                             310
#define RILC_REQ_EMBMS_ENABLE_SERVICE                   (RILC_REQ_EMBMS_BASE)
#define RILC_REQ_EMBMS_DISABLE_SERVICE                  (RILC_REQ_EMBMS_BASE + 1)
#define RILC_REQ_EMBMS_SET_SESSION                      (RILC_REQ_EMBMS_BASE + 2)
#define RILC_REQ_EMBMS_GET_SESSION_LIST                 (RILC_REQ_EMBMS_BASE + 3)
#define RILC_REQ_EMBMS_GET_SIGNAL_STRENGTH              (RILC_REQ_EMBMS_BASE + 4)
#define RILC_REQ_EMBMS_GET_NETWORK_TIME                 (RILC_REQ_EMBMS_BASE + 5)
#define RILC_REQ_EMBMS_CHECK_AVAIABLE_EMBMS             (RILC_REQ_EMBMS_BASE + 6)

/* P-SENSOR */
#define RILC_REQ_PSENSOR_BASE                           400
#define RILC_REQ_PSENSOR_SET_STATUS                     (RILC_REQ_PSENSOR_BASE + 1)

/* VSIM */
#define RILC_REQ_VSIM_BASE                              450
#define RILC_REQ_VSIM_NOTIFICATION                      (RILC_REQ_VSIM_BASE + 1)
#define RILC_REQ_VSIM_OPERATION                         (RILC_REQ_VSIM_BASE + 2)

/* SAR */
#define RILC_REQ_SAR_BASE                               500
#define RILC_REQ_SAR_SET_SAR_STATE                      (RILC_REQ_SAR_BASE + 1)
#define RILC_REQ_SAR_GET_SAR_STATE                      (RILC_REQ_SAR_BASE + 2)

/* RCS */
#define RILC_REQ_AIMS_RCS_MULTI_FRAME                   550
#define RILC_REQ_AIMS_RCS_CHAT                          551
#define RILC_REQ_AIMS_RCS_GROUP_CHAT                    552
#define RILC_REQ_AIMS_RCS_OFFLINE_MODE                  553
#define RILC_REQ_AIMS_RCS_FILE_TRANSFER                 554
#define RILC_REQ_AIMS_RCS_COMMON_MESSAGE                555
#define RILC_REQ_AIMS_RCS_CONTENT_SHARE                 556
#define RILC_REQ_AIMS_RCS_PRESENCE                      557
#define RILC_REQ_AIMS_XCAP_MANAGE                       558
#define RILC_REQ_AIMS_RCS_CONFIG_MANAGE                 559
#define RILC_REQ_AIMS_RCS_TLS_MANAGE                    560

#define RILC_REQ_SET_SELFLOG                            600
#define RILC_REQ_GET_SELFLOG_STATUS                     601
#define RILC_REQ_MODEM_INFO                             602
#define RILC_REQ_SET_RTP_PKTLOSS_THRESHOLD              603
#define RILC_REQ_SWITCH_MODEM_FUNCTION                  604
#define RILC_REQ_SET_PDCP_DISCARD_TIMER                 605
#define RILC_REQ_GET_CQI_INFO                           606
#define RILC_REQ_SET_SAR_SETTING                        607
#define RILC_REQ_SET_GMO_SWITCH                         608
#define RILC_REQ_SET_TCS_FCI                            609
#define RILC_REQ_GET_TCS_FCI                            610
#define RILC_REQ_SET_SELFLOG_PROFILE                    611
#define RILC_REQ_SET_FORBID_LTE_CELL                    612
#define RILC_REQ_GET_FREQUENCY_INFO                     613

#define RILC_REQ_GET_RADIO_NODE                         800
#define RILC_REQ_SET_RADIO_NODE                         801
#define RILC_REQ_GET_PROVISION_UPDATE_REQUEST           802
#define RILC_REQ_SET_PROVISION_UPDATE_DONE_REQUEST      803
#define RILC_REQ_RADIO_CONFIG_RESET                     804
#define RILC_REQ_VERIFY_MSL                             805
#define RILC_REQ_GET_PLMN_NAME_FROM_SE13TABLE           806
#define RILC_REQ_TS25TABLE_DUMP                         807
#define RILC_REQ_SET_CA_BANDWIDTH_FILTER                808
#define RILC_REQ_ICC_DEPERSONALIZATION                  809
#define RILC_REQ_CANCEL_GET_AVAILABLE_NETWORK           810

/* UNSOLICITED */
#define RILC_UNSOL_SOCKET_ERROR                    1000    /* RIL socket closed */
#define RILC_UNSOL_NOT_SUPPORTED                   1001    /* not supported */
#define RILC_UNSOL_AUDIO_RING                      2001    /* Ring indication */
#define RILC_UNSOL_DISPLAY_ENG_MODE                2002    /* Display Engineer Mode */
#define RILC_UNSOL_AUDIO_RINGBACK                  2003    /* Ringback indication */
#define RILC_UNSOL_PIN_CONTROL                     2004    /* Pin status indication */
#define RILC_UNSOL_AM                              2005    /* AM indication */
#define RILC_UNSOL_SCAN_RSSI_RESULT                2006    /* a result of RSSI Scanning */
#define RILC_UNSOL_FORWARDING_AT_COMMAND           2007    /* AT command through RIL interface */
#define RILC_UNSOL_WB_AMR_REPORT                   2008    /* WB-AMR on/off status */
#define RILC_UNSOL_AUDIO_RINGBACK_BY_NETWORK       2009    /* Ringback indication(network) */

#define RILC_UNSOL_IMS_CONFIGURATION               3000    /* Send IMS configuration information */
#define RILC_UNSOL_IMS_DEDICATED_PDN_INFO          3001    /* Send dedicated pdn information */
#define RILC_UNSOL_IMS_EMERGENCY_ACT_INFO          3002    /* Emergency call rat information */
#define RILC_UNSOL_IMS_SRVCC_HO                    3003    /* SRVCC handover */
#define RILC_UNSOL_IMS_EMERGENCY_CALL_LIST         3004    /* Emergency call list */
#define RILC_UNSOL_IMS_SUPPORT_SERVICE             3005    /* Support service at network */
#define RILC_UNSOL_IMS_OPEN_CARRIER_INFO           3006    /* Open Carrier Information */

//AIMS support start ---------------------
#define RILC_UNSOL_AIMS_CALL_RING                  3010
#define RILC_UNSOL_AIMS_CALL_STATUS                3011
#define RILC_UNSOL_AIMS_REGISTRATION               3012
#define RILC_UNSOL_AIMS_CALL_MODIFY                3013
#define RILC_UNSOL_AIMS_FRAME_TIME                 3014
#define RILC_UNSOL_AIMS_SUPP_SVC_NOTIFICATION      3015
#define RILC_UNSOL_AIMS_NEW_SMS                    3016
#define RILC_UNSOL_AIMS_NEW_SMS_STATUS_REPORT      3017
#define RILC_UNSOL_AIMS_ON_USSD                    3018
#define RILC_UNSOL_AIMS_CONFERENCE_CALL_EVENT      3019
#define RILC_UNSOL_AIMS_HO_PAYLOAD                 3020
#define RILC_UNSOL_AIMS_VOWIFI_HO_CALL_INFO        3021
#define RILC_UNSOL_AIMS_NEW_CDMA_SMS               3022
#define RILC_UNSOL_AIMS_CALL_MANAGE                3023
#define RILC_UNSOL_AIMS_CONF_CALL_ADD_REMOVE_USER  3024
#define RILC_UNSOL_AIMS_ENHANCED_CONF_CALL         3025
#define RILC_UNSOL_AIMS_CALL_MODIFY_RSP            3026
#define RILC_UNSOL_AIMS_DTMF_EVENT                 3031
#define RILC_UNSOL_AIMS_RTT_NEW_TEXT               3032
#define RILC_UNSOL_AIMS_RTT_FAIL_SENDING_TEXT      3033
#define RILC_UNSOL_AIMS_RCS_MULTI_FRAME            3034
#define RILC_UNSOL_AIMS_RCS_CHAT                   3035
#define RILC_UNSOL_AIMS_RCS_GROUP_CHAT             3036
#define RILC_UNSOL_AIMS_RCS_OFFLINE_MODE           3037
#define RILC_UNSOL_AIMS_RCS_FILE_TRANSFER          3038
#define RILC_UNSOL_AIMS_RCS_COMMON_MESSAGE         3039
#define RILC_UNSOL_AIMS_RCS_CONTENT_SHARE          3040
#define RILC_UNSOL_AIMS_RCS_PRESENCE               3041
#define RILC_UNSOL_AIMS_RCS_XCAP_MANAGE            3042
#define RILC_UNSOL_AIMS_RCS_CONFIG_MANAGE          3043
#define RILC_UNSOL_AIMS_RCS_TLS_MANAGE             3044
#define RILC_UNSOL_AIMS_EXIT_EMERGENCY_CB_MODE     3046
#define RILC_UNSOL_AIMS_AC_BARRING_INFO            3047
#define RILC_UNSOL_AIMS_DIALOG_INFO                3048
#define RILC_UNSOL_AIMS_MEDIA_STATUS               3049
#define RILC_UNSOL_AIMS_SIP_MSG_INFO               3050
#define RILC_UNSOL_AIMS_VOICE_RTP_QUALITY          3051
#define RILC_UNSOL_AIMS_RTP_RX_STATISTICS          3052
//AIMS support end ----------------------

/* WFC */
#define RILC_UNSOL_WFC_RTP_RTCP_TIMEOUT        3027
#define RILC_UNSOL_WFC_FIRST_RTP               3028
#define RILC_UNSOL_WFC_RTCP_RX_SR              3029
#define RILC_UNSOL_WFC_RCV_DTMF_NOTI           3030
#define RILC_UNSOL_WFC_SIGNAL_STRENGTH         3045

/* GPS */
#define RILC_UNSOL_GPS_BASE                                 4000
#define RILC_UNSOL_GPS_MEASURE_POS_REQ                      (RILC_UNSOL_GPS_BASE + 1)
#define RILC_UNSOL_GPS_ASSIST_DATA                          (RILC_UNSOL_GPS_BASE + 2)
#define RILC_UNSOL_GPS_RELEASE_GPS                          (RILC_UNSOL_GPS_BASE + 3)
#define RILC_UNSOL_GPS_MT_LOCATION_REQUEST                  (RILC_UNSOL_GPS_BASE + 4)
#define RILC_UNSOL_GPS_RESET_GPS_ASSIST_DATA                (RILC_UNSOL_GPS_BASE + 5)
#define RILC_UNSOL_GPS_LPP_REQUEST_CAPABILITIES             (RILC_UNSOL_GPS_BASE + 6)
#define RILC_UNSOL_GPS_LPP_PROVIDE_ASSIST_DATA              (RILC_UNSOL_GPS_BASE + 7)
#define RILC_UNSOL_GPS_LPP_REQUEST_LOCATION_INFO            (RILC_UNSOL_GPS_BASE + 8)
#define RILC_UNSOL_GPS_LPP_GPS_ERROR_IND                    (RILC_UNSOL_GPS_BASE + 9)
#define RILC_UNSOL_GPS_SUPL_LPP_DATA_INFO                   (RILC_UNSOL_GPS_BASE + 10)
#define RILC_UNSOL_GPS_SUPL_NI_MESSAGE                      (RILC_UNSOL_GPS_BASE + 11)
#define RILC_UNSOL_GPS_SUPL_NI_READY                        (RILC_UNSOL_GPS_BASE + 18)
#define RILC_UNSOL_GPS_START_MDT_LOC                        (RILC_UNSOL_GPS_BASE + 19)
#define RILC_UNSOL_GPS_LPP_UPDATE_UE_LOC_INFO               (RILC_UNSOL_GPS_BASE + 20)
#define RILC_UNSOL_GPS_LOCK_MODE                            (RILC_UNSOL_GPS_BASE + 21)

/* CDMA & HEDGE GANSS */
#define RILC_UNSOL_GPS_3GPP_SEND_GANSS_ASSIT_DATA           (RILC_UNSOL_GPS_BASE + 12)
#define RILC_UNSOL_GPS_GANSS_MEAS_POS_MSG                   (RILC_UNSOL_GPS_BASE + 13)
#define RILC_UNSOL_GPS_CDMA_GPS_POWER_ON                    (RILC_UNSOL_GPS_BASE + 14)
#define RILC_UNSOL_GPS_CDMA_SEND_ACQUSITION_ASSIT_DATA      (RILC_UNSOL_GPS_BASE + 15)
#define RILC_UNSOL_GPS_CDMA_SESSION_CANCELLATION            (RILC_UNSOL_GPS_BASE + 16)
#define RILC_UNSOL_GPS_GANSS_AP_POS_CAP_REQ                 (RILC_UNSOL_GPS_BASE + 17)

#define RILC_UNSOL_JNIIF_START_ACTIVITY         5000
#define RILC_UNSOL_JNIIF_START_SERVICE          5001
#define RILC_UNSOL_JNIIF_STOP_SERVICE           5002
#define RILC_UNSOL_JNIIF_SEND_BROADCAST         5003

/* Self log */
#define RILC_UNSOL_SELFLOG_STATUS                           5100
/* Modem Status */
#define RILC_UNSOL_MODEM_INFO                               5101
/* RTP packet loss threshold */
#define RILC_UNSOL_RTP_PKTLOSS_THRESHOLD                    5102
/* Frequency Info */
#define RILC_UNSOL_FREQUENCY_INFO                           5103
/* AMBR */
#define RILC_UNSOL_AMBR                                     5104
/* B2B1 Config */
#define RILC_UNSOL_B2_B1_CONFIG_INFO                        5105

/* OEM2 */
#define RILC_UNSOL_PSENSOR_BASE                             6000
#define RILC_UNSOL_PSENSOR_CONTROL_STATE                    6001
#define RILC_UNSOL_CA_BANDWIDTH_FILTER                      6002

/* VSIM */
#define RILC_UNSOL_VSIM_BASE                                6500
#define RILC_UNSOL_VSIM_OPERATION                           (RILC_UNSOL_VSIM_BASE + 1)

/* SAR */
#define RILC_UNSOL_SAR_BASE                                 7000
#define RILC_UNSOL_SAR_RF_CONNECTION                        (RILC_UNSOL_SAR_BASE + 1)

/* eMBMS */
#define RILC_UNSOL_EMBMS_BASE                               8000
#define RILC_UNSOL_EMBMS_COVERAGE                           (RILC_UNSOL_EMBMS_BASE)
#define RILC_UNSOL_EMBMS_SESSION_LIST                       (RILC_UNSOL_EMBMS_BASE + 1)
#define RILC_UNSOL_EMBMS_SIGNAL_STRENGTH                    (RILC_UNSOL_EMBMS_BASE + 2)
#define RILC_UNSOL_EMBMS_NETWORK_TIME                       (RILC_UNSOL_EMBMS_BASE + 3)
#define RILC_UNSOL_EMBMS_SAI_LIST                           (RILC_UNSOL_EMBMS_BASE + 4)
#define RILC_UNSOL_EMBMS_GLOBAL_CELL_ID                     (RILC_UNSOL_EMBMS_BASE + 5)
#define RILC_UNSOL_EMBMS_RADIO_STATE_CHANGED                (RILC_UNSOL_EMBMS_BASE + 6)
#define RILC_UNSOL_EMBMS_MODEM_STATUS                       (RILC_UNSOL_EMBMS_BASE + 7)
#define RILC_UNSOL_EMBMS_SESSION_CONTROL                    (RILC_UNSOL_EMBMS_BASE + 8)

#ifdef __cplusplus
};
#endif

#endif // _RIL_CLIENT_H

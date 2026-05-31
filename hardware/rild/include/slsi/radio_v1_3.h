/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RADIO_V1_3_H__
#define __RADIO_V1_3_H__

#include <telephony/ril.h>

/**
 * Specify which bands modem's background scan must act on.
 * If specifyChannels is true, it only scans bands specified in specifiers.
 * If specifyChannels is false, it scans all bands.
 *
 * For example, CBRS is only on LTE band 48. By specifying this band,
 * modem saves more power.
 *
 * @param specifyChannels whether to scan bands defined in specifiers.
 * @param specifiers which bands to scan. Only used if specifyChannels is true.
 *
 */
//#define RIL_REQUEST_ENABLE_MODEM ???      // not in use in RIL.java

/**
 * Toggle logical modem on/off. This is similar to @1.0::IRadio.setRadioPower(), however that
 * does not enforce that radio power is toggled only for the corresponding radio and certain
 * vendor implementations do it for all radios. This new API should affect only the modem for
 * which it is called. A modem stack must be on/active only when both setRadioPower() and
 * enableModem() are set to on for it.
 *
 * SIM must be read if available even if modem is off/inactive.
 *
 * data is int *
 * ((int *)data)[0] is > 0 to turn on the logical modem
 * ((int *)data)[1] is == 0 to turn off the logical modem
 *
 * "response" is NULL
 *
 * Valid errors returned:
 *   RIL_E_SUCCESS
 *   RIL_E_RADIO_NOT_AVAILABLE
 *   RIL_E_MODEM_ERR
*/
#define RIL_REQUEST_ENABLE_MODEM 146

/**
 * Request status of logical modem. It returns isEnabled=true if the logical modem is on.
 * This method is the getter method for enableModem.
 *
 * "data" is NULL
 *
 * "response" is int *
 * ((int *)data)[0] is > 0 the logical modem is on
 * ((int *)data)[0] is == 0 the logical modem is off
 *
 * Valid errors returned:
 *   RIL_E_SUCCESS
 *   RIL_E_RADIO_NOT_AVAILABLE
 *   RIL_E_MODEM_ERR
 */
#define RIL_REQUEST_GET_MODEM_STATUS 147

#endif // __RADIO_V1_3_H__

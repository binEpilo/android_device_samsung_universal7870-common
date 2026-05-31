/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RADIOCONFIG_V1_0_H__
#define __RADIOCONFIG_V1_0_H__

#include <telephony/ril.h>

#define MAX_SLOT_NUM 4

typedef enum {
    PYSICAL_SLOT_INACTIVE  = 0x00, // Physical slot is inactive
    PYSICAL_SLOT_ACTIVE    = 0x01, //Physical slot is active
} RIL_SlotState;

typedef struct {
    RIL_CardState cardState;        //Card state in the physical slot
    RIL_SlotState slotState;        //Slot state Active/Inactive
    /**
     * An Answer To Reset (ATR) is a message output by a Smart Card conforming to ISO/IEC 7816
     * standards, following electrical reset of the card's chip. The ATR conveys information about
     * the communication parameters proposed by the card, and the card's nature and state.
     *
     * This data is applicable only when cardState is CardState:PRESENT.
     */
    uint32_t atr_size;
    char *atr;
    uint32_t logicalSlotId;
    /**
     * Integrated Circuit Card IDentifier (ICCID) is Unique Identifier of the SIM CARD. File is
     * located in the SIM card at EFiccid (0x2FE2) as per ETSI 102.221. The ICCID is defined by
     * the ITU-T recommendation E.118 ISO/IEC 7816.
     *
     * This data is applicable only when cardState is CardState:PRESENT.
     */
    uint32_t iccid_size;
    char *iccid;
} RIL_SimSlotStatus;

typedef struct {
    int32_t num_slots;
    RIL_SimSlotStatus mSimSlotStatus[MAX_SLOT_NUM];
} RIL_SimSlotStatusResult;

/**
* RIL_REQUEST_GET_SLOTS_STATUS
*
* Request provides the slot status of all active and inactive SIM slots and whether card is
* present in the slots or not.
*
* @param serial Serial number of request.
*
* "data" is int32_t
*
* response is a const RIL_SimSlotStaus
*
* Valid errors:
* RadioError:NONE (SUCCESS)
* RadioError:RADIO_NOT_AVAILABLE, NO_MEMORY, INTERNAL_ERR, MODEM_ERR
*
*/
#define RIL_REQUEST_GET_SLOT_STATUS 200

/**
*
* RIL_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING
*
* @param serial Serial number of request
* @param slotMap Logical to physical slot mapping, size == no. of radio instances. Index is
*        mapping to logical slot and value to physical slot, need to provide all the slots
*        mapping when sending request in case of multi slot device.
*        EX: uint32_t slotMap[logical slot] = physical slot
*        index 0 is the first logical_slot number of logical slots is equal to number of Radio
*        instances and number of physical slots is equal to size of slotStatus in
*        getSimSlotsStatusRespons
*
*
* response info contains response type, serial no., error
*
* Valid errors:
* RadioError:NONE (SUCCESS)
* RadioError:RADIO_NOT_AVAILABLE, NO_MEMORY, INTERNAL_ERR, MODEM_ERR, INVALID_ARGUMENTS
*/
#define RIL_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING 201

/**
* RIL_UNSOL_ICC_SLOT_STATUS
*
* "data" is NULL
* "response" is a const RIL_SimSlotStaus *
*
*/
#define RIL_UNSOL_ICC_SLOT_STATUS 1100

#endif // __RADIOCONFIG_V1_0_H__
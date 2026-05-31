/* copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

#ifndef __RADIOCONFIG_V1_2_H__
#define __RADIOCONFIG_V1_2_H__

// There's no new Request just Response is updated
// So add new RIL Request Command Index for RadioConfig 1.2
// This shall use @1.2::SimSlotStatus as Response Payload

typedef struct {
    RIL_CardState cardState;        //Card state for the physical slot
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

    /**
     * The EID is the eUICC identifier. The EID shall be stored within the ECASD and can be
     * retrieved by the Device at any time using the standard GlobalPlatform GET DATA command.
     *
     * This data is mandatory and applicable only when cardState is CardState:PRESENT and SIM card
     * supports eUICC.
     */
    uint32_t eid_size;
    char *eid;
} RIL_SimSlotStatus_1_2;

typedef struct {
    int32_t num_slots;
    RIL_SimSlotStatus_1_2 mSimSlotStatus[MAX_SLOT_NUM];
} RIL_SimSlotStatusResult_1_2;

#endif // __RADIOCONFIG_V1_2_H__

/*
 * Minimal audio device type definitions for amplifier HAL
 * Extracted from audio-hal_slsi-linaro audio_hw.h
 */

#ifndef AUDIO_DEVICE_TYPES_H
#define AUDIO_DEVICE_TYPES_H

#include <system/audio.h>
#include <hardware/audio_amplifier.h>

/*
 * Real Audio Out/Input Device based on Target Device
 * Maps Android audio device constants to simplified device types
 */
typedef enum {
    DEVICE_EARPIECE               = 0,   // handset or receiver
    DEVICE_SPEAKER,
    DEVICE_HEADSET,                      // headphone + mic
    DEVICE_HEADPHONE,                    // headphone or earphone
    DEVICE_SPEAKER_AND_HEADSET,
    DEVICE_SPEAKER_AND_HEADPHONE,
    DEVICE_BT_HEADSET,

    DEVICE_MAIN_MIC,
    DEVICE_HEADSET_MIC,
    DEVICE_BT_HEADSET_MIC,

    DEVICE_NONE,
} device_type_t;

#endif // AUDIO_DEVICE_TYPES_H

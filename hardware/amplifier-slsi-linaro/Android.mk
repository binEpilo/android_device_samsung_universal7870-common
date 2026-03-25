# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(TARGET_AUDIOHAL_VARIANT),samsung-linaro-exynos7870)
ifeq ($(BOARD_USE_SPKAMP),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_BOARD_TFA_MODEL),9890)
LOCAL_SHARED_LIBRARIES := \
	liblog \
	libutils \
	libcutils \
	libhardware \
	libtfa98xx \
	libtinyalsa \
	libtinycompress
endif

ifeq ($(TARGET_BOARD_TFA_MODEL),9896)
LOCAL_SHARED_LIBRARIES := \
	liblog \
	libutils \
	libcutils \
	libhardware \
	libtinyalsa \
	libtinycompress
endif

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
	external/tinyalsa/include \
	external/tinycompress/include \
	external/kernel-headers/original/uapi/sound \
	hardware/libhardware/include \
	$(call include-path-for, audio-utils) \
	$(call include-path-for, audio-route) \
	$(call include-path-for, audio-effects) \
	$(LOCAL_PATH)/../audio-hal_slsi-linaro

ifeq ($(TARGET_AUDIOHAL_VARIANT),samsung-exynos7870)
    LOCAL_C_INCLUDES += $(LOCAL_PATH)/../audio-hal-samsung-hardware
endif

ifeq ($(TARGET_BOARD_TFA_MODEL),9890)
    LOCAL_SRC_FILES := \
        tfa9890/amplifier.c \
        tfa9890/tfa.c
    LOCAL_C_INCLUDES += $(LOCAL_PATH)/tfa9890/include
    LOCAL_CFLAGS += -DTFA_MODEL_9890
endif

ifeq ($(TARGET_BOARD_TFA_MODEL),9896)
    LOCAL_SRC_FILES := \
        tfa9896/amplifier.c \
        tfa9896/tfa.c
    LOCAL_C_INCLUDES += $(LOCAL_PATH)/tfa9896/include
    LOCAL_CFLAGS += -DTFA_MODEL_9896
    LOCAL_C_INCLUDES += $(LOCAL_PATH)/tfa9896/include
endif

LOCAL_CFLAGS := -Werror -Wall
LOCAL_CFLAGS += -DPREPROCESSING_ENABLED

LOCAL_MODULE := audio_amplifier.$(TARGET_BOOTLOADER_BOARD_NAME)
LOCAL_VENDOR_MODULE := true
LOCAL_MULTILIB := 32
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

endif
endif

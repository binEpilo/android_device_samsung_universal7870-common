# Copyright 2006 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    secril-client.cpp

LOCAL_SHARED_LIBRARIES := \
    libutils \
    libbinder \
    libcutils \
    libhardware_legacy \
    liblog

LOCAL_CFLAGS := 

ifeq ($(TARGET_BOARD_PLATFORM),exynos4)
LOCAL_CFLAGS += -DRIL_CALL_AUDIO_PATH_EXTRAVOLUME
endif
ifneq ($(filter m7450 mdm9x35 ss333 xmm7260,$(BOARD_MODEM_TYPE)),)
LOCAL_CFLAGS += -DSAMSUNG_NEXT_GEN_MODEM
endif

ifeq ($(TARGET_USES_VND_SECRIL), true)

LOCAL_SHARED_LIBRARIES += libfloatingfeature

LOCAL_CFLAGS += -DUSES_VND_SECRIL
LOCAL_MODULE:= libvndsecril-client
LOCAL_PROPRIETARY_MODULE := true
else
LOCAL_MODULE:= libsecril-client
endif

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

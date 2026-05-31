# Copyright 2006 The Android Open Source Project

ifdef ENABLE_VENDOR_RIL_SERVICE

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	rild.c

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libdl \
	liblog \
	libril-samsung

# Temporary hack for broken vendor RILs.
#LOCAL_WHOLE_STATIC_LIBRARIES := \
#	librilutils

LOCAL_CFLAGS := -DRIL_SHLIB
LOCAL_CFLAGS += -Wall -Wextra -Werror

ifeq ($(SIM_COUNT), 2)
    LOCAL_CFLAGS += -DANDROID_MULTI_SIM
    LOCAL_CFLAGS += -DANDROID_SIM_COUNT_2
endif
LOCAL_CFLAGS += -DPRODUCT_COMPATIBLE_PROPERTY

LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE:= rild
# LOCAL_INIT_RC := rild.rc

LOCAL_C_INCLUDES += system/core/include \
	$(LOCAL_PATH)/include

include $(BUILD_EXECUTABLE)

endif

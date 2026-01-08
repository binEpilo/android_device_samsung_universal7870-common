ifeq ($(TARGET_BOARD_HAS_MDFPP_KEYMASTER),true)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := android.hardware.keymaster@3.0-impl.exynos7870
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MULTILIB := 32
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_SRC_FILES := \
    KeymasterDevice.cpp \

LOCAL_SHARED_LIBRARIES := \
    liblog \
    libsoftkeymasterdevice \
    libcrypto \
    libkeymaster_portable \
    libpuresoftkeymasterdevice \
    libkeymaster3device \
    libskeymaster3device \
    libhidlbase \
    libutils \
    libhardware \
    android.hardware.keymaster@3.0

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MULTILIB := 32
LOCAL_MODULE := android.hardware.keymaster@3.0-service.exynos7870
LOCAL_INIT_RC := android.hardware.keymaster@3.0-service.exynos7870.rc
LOCAL_SRC_FILES := \
    service.cpp

LOCAL_SHARED_LIBRARIES := \
    liblog \
    libcutils \
    libdl \
    libbase \
    libutils \
    libhardware \
    libhidlbase \
    android.hardware.keymaster@3.0

include $(BUILD_EXECUTABLE)
endif

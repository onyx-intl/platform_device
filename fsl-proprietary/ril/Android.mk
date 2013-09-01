
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libreference-ril-zte.so
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_SRC_FILES := lib/libreference-ril-zte.so
include $(BUILD_PREBUILT)

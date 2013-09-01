ifeq ($(PREBUILT_FSL_IMX_GPU),true)

LOCAL_PATH := $(call my-dir)

ifeq ($(BOARD_SOC_CLASS),IMX5X)
ifeq ($(HAVE_FSL_IMX_GPU3D),false)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := \
        lib/libc2d_z160.so \
        lib/libgsl-fsl.so
LOCAL_MODULE_TAGS := eng        
include $(BUILD_MULTI_PREBUILT)

else

# GPU hw impl and cfg file
include $(CLEAR_VARS)
LOCAL_MODULE := libEGL_imx51.so
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/egl
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_SRC_FILES :=  egl/libEGL_imx51.so
LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libGLESv1_CM_imx51.so
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/egl
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_SRC_FILES :=  egl/libGLESv1_CM_imx51.so
LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libGLESv2_imx51.so
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/egl
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_SRC_FILES :=  egl/libGLESv2_imx51.so
LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := egl.cfg
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/egl
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_SRC_FILES :=  egl/egl.cfg
LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

# GPU libs
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := \
	lib/libc2d_z160.so \
	lib/libc2d_z430.so \
	lib/libgsl-fsl.so
LOCAL_MODULE_TAGS := eng	
include $(BUILD_MULTI_PREBUILT)

endif
endif
endif

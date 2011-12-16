LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := media_profiles.xml
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES := conf/media_profiles.xml
LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)


include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := \
	lib/libfsl_jpeg_enc_arm11_elinux.so \
	lib/lib_g.711_dec_arm11_elinux.so \
	lib/lib_g.711_enc_arm11_elinux.so \
	lib/lib_g.723.1_dec_arm11_elinux.so \
	lib/lib_g.723.1_enc_arm11_elinux.so \
	lib/lib_g.726_dec_arm11_elinux.so \
	lib/lib_g.726_enc_arm11_elinux.so \
	lib/lib_g.729ab_dec_arm11_elinux.so \
	lib/lib_g.729ab_enc_arm11_elinux.so \
	lib/libfslxec.so \
            	
LOCAL_MODULE_TAGS := eng
include $(BUILD_MULTI_PREBUILT)

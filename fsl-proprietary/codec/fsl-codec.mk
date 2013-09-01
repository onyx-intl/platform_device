LOCAL_PATH := $(call my-dir)

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
\
	lib/lib_aac_dec_v2_arm12_elinux.so \
	lib/lib_flac_dec_v2_arm11_elinux.so \
	lib/lib_H263_dec_v2_arm11_elinux.so \
	lib/lib_mp3_dec_v2_arm12_elinux.so \
	lib/lib_mp3_enc_v2_arm12_elinux.so \
	lib/lib_nb_amr_dec_v2_arm9_elinux.so \
	lib/lib_nb_amr_enc_v2_arm11_elinux.so \
	lib/lib_oggvorbis_dec_v2_arm11_elinux.so \
	lib/lib_peq_v2_arm11_elinux.so \
	lib/lib_wb_amr_dec_arm9_elinux.so \
	lib/lib_wb_amr_enc_arm11_elinux.so \
\
	lib/lib_avi_parser_arm11_elinux.3.0.so \
	lib/lib_aac_parser_arm11_elinux.so \
	lib/lib_flac_parser_arm11_elinux.so \
	lib/lib_flv_parser_arm11_elinux.3.0.so \
	lib/lib_mkv_parser_arm11_elinux.3.0.so \
	lib/lib_mp3_parser_v2_arm11_elinux.so \
	lib/lib_mp4_muxer_arm11_elinux.so \
	lib/lib_mp4_parser_arm11_elinux.3.0.so \
	lib/lib_mpg2_parser_arm11_elinux.3.0.so \
	lib/lib_ogg_parser_arm11_elinux.3.0.so \
	lib/lib_wav_parser_arm11_elinux.so \
    lib/lib_amr_parser_arm11_elinux.3.0.so \

ifeq ($(BOARD_SOC_TYPE),IMX6SL)
LOCAL_PREBUILT_LIBS := lib/libfsl_jpeg_enc_arm11_elinux.so
endif
            	
LOCAL_MODULE_TAGS := eng
include $(BUILD_MULTI_PREBUILT)


#for video recoder profile setting
include $(CLEAR_VARS)
LOCAL_MODULE := media_profiles.xml
LOCAL_MODULE_CLASS := ETC

ifeq ($(BOARD_SOC_TYPE),IMX51)
LOCAL_SRC_FILES := record_profile/media_profiles_d1.xml
endif

ifeq ($(BOARD_SOC_TYPE),IMX53)
LOCAL_SRC_FILES := record_profile/media_profiles_720p.xml
endif

#for mx6x, it should be up to 1080p profile
ifeq ($(BOARD_SOC_TYPE),IMX6DQ)
LOCAL_SRC_FILES := record_profile/media_profiles_1080p.xml
endif

#for mx6sl, it should be up to 480p profile
ifeq ($(BOARD_SOC_TYPE),IMX6SL)
LOCAL_SRC_FILES := record_profile/media_profiles_qvga.xml
endif


ifeq ($(BOARD_HAVE_USB_CAMERA),true)
LOCAL_SRC_FILES := record_profile/media_profiles_480p.xml
endif

LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

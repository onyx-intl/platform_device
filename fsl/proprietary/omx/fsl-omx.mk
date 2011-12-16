ifeq ($(PREBUILT_FSL_IMX_OMX),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := \
	lib/lib_omx_player_arm11_elinux.so \
	lib/lib_omx_client_arm11_elinux.so \
	lib/lib_omx_core_mgr_v2_arm11_elinux.so \
	lib/lib_omx_core_v2_arm11_elinux.so \
	lib/lib_omx_osal_v2_arm11_elinux.so \
	lib/lib_omx_common_v2_arm11_elinux.so \
	lib/lib_omx_utils_v2_arm11_elinux.so \
	lib/lib_omx_res_mgr_v2_arm11_elinux.so \
	lib/lib_omx_clock_v2_arm11_elinux.so \
	lib/lib_omx_local_file_pipe_v2_arm11_elinux.so \
	lib/lib_omx_shared_fd_pipe_arm11_elinux.so \
	lib/lib_omx_https_pipe_arm11_elinux.so \
	\
	lib/lib_omx_fsl_parser_v2_arm11_elinux.so \
	lib/lib_omx_fsl_muxer_v2_arm11_elinux.so \
	lib/lib_omx_wav_parser_v2_arm11_elinux.so \
	lib/lib_omx_mp3_parser_v2_arm11_elinux.so \
	lib/lib_omx_aac_parser_v2_arm11_elinux.so \
	lib/lib_omx_flac_parser_v2_arm11_elinux.so \
	\
	lib/lib_omx_pcm_dec_v2_arm11_elinux.so \
	lib/lib_omx_mp3_dec_v2_arm11_elinux.so \
	lib/lib_omx_mp3_enc_v2_arm11_elinux.so \
	lib/lib_omx_aac_dec_v2_arm11_elinux.so \
	lib/lib_omx_amr_dec_v2_arm11_elinux.so \
	lib/lib_omx_amr_enc_v2_arm11_elinux.so \
	lib/lib_omx_vorbis_dec_v2_arm11_elinux.so \
	lib/lib_omx_flac_dec_v2_arm11_elinux.so \
	lib/lib_omx_audio_processor_v2_arm11_elinux.so \
	lib/lib_omx_sorenson_dec_v2_arm11_elinux.so \
	\
	lib/lib_omx_android_audio_render_arm11_elinux.so \
	lib/lib_omx_android_audio_source_arm11_elinux.so \
	lib/lib_omx_camera_source_arm11_elinux.so \
	lib/lib_omx_audio_fake_render_arm11_elinux.so \
	lib/lib_omx_ipulib_render_arm11_elinux.so \
	\
	lib/lib_avi_parser_arm11_elinux.3.0.so \
	lib/lib_divx_drm_arm11_elinux.so \
	lib/lib_mp4_parser_arm11_elinux.3.0.so \
	lib/lib_mp4_muxer_arm11_elinux.so \
	lib/lib_mkv_parser_arm11_elinux.3.0.so \
	lib/lib_flv_parser_arm11_elinux.3.0.so \
	lib/lib_ogg_parser_arm11_elinux.3.0.so \
	\
	lib/lib_id3_parser_arm11_elinux.so \
	lib/lib_wav_parser_arm11_elinux.so \
	lib/lib_mp3_parser_v2_arm11_elinux.so \
	lib/lib_aac_parser_arm11_elinux.so \
	lib/lib_flac_parser_arm11_elinux.so \
	\
	lib/lib_mp3_dec_v2_arm12_elinux.so \
	lib/lib_mp3_enc_v2_arm12_elinux.so \
	lib/lib_aac_dec_v2_arm12_elinux.so \
	lib/lib_flac_dec_v2_arm11_elinux.so \
	lib/lib_nb_amr_dec_v2_arm9_elinux.so \
	lib/lib_nb_amr_enc_v2_arm11_elinux.so \
	lib/lib_oggvorbis_dec_v2_arm11_elinux.so \
	lib/lib_peq_v2_arm11_elinux.so \
	lib/lib_mpg2_parser_arm11_elinux.3.0.so \
	\
	lib/libstagefrighthw.so \


ifeq ($(BOARD_SOC_CLASS),IMX5X)
LOCAL_PREBUILT_LIBS += lib/lib_omx_vpu_v2_arm11_elinux.so \
	lib/lib_omx_vpu_dec_v2_arm11_elinux.so \
	lib/lib_omx_vpu_enc_v2_arm11_elinux.so \
	lib/lib_vpu_wrapper.so 
else
LOCAL_SHARED_LIBRARIES := lib_omx_player_arm11_elinux
endif

ifeq ($(findstring x2.3,x$(PLATFORM_VERSION)), x2.3)
LOCAL_PREBUILT_LIBS += lib/lib_omx_overlay_render_arm11_elinux.so
endif

LOCAL_MODULE_TAGS := eng

include $(BUILD_MULTI_PREBUILT)


include $(CLEAR_VARS)
LOCAL_MODULE := core_register
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES := registry/core_register

LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := component_register
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES := registry/component_register

LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := contentpipe_register
LOCAL_MODULE_CLASS := ETC
LOCAL_SRC_FILES := registry/contentpipe_register

LOCAL_MODULE_TAGS := eng
include $(BUILD_PREBUILT)

endif

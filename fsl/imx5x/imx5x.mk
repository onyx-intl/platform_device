$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)

#add the audio files
$(call inherit-product, frameworks/base/data/sounds/OriginalAudio.mk)
$(call inherit-product, frameworks/base/data/sounds/AudioPackage2.mk)
$(call inherit-product, frameworks/base/data/sounds/AudioPackage3.mk)
$(call inherit-product, frameworks/base/data/sounds/AudioPackage4.mk)
$(call inherit-product, frameworks/base/data/sounds/AudioPackage5.mk)

# overrides
PRODUCT_BRAND := freescale
PRODUCT_MANUFACTUER := freescale

# Android infrastructures
PRODUCT_PACKAGES += \
	LiveWallpapers				\
	LiveWallpapersPicker			\
	MagicSmokeWallpapers			\
	VisualizationWallpapers			\
	CubeLiveWallpapers			\
	SpareParts				\
	PinyinIME				\
	libRS					\
	librs_jni				\
	pppd					\
	chat					\
	ip-up-vpn				\
	ip-up-ppp0				\
	ip-down-ppp0				\
	wpa_supplicant				\
	wpa_supplicant.conf			\
	dispd					\
	ts_calibrator

# Debug utils
PRODUCT_PACKAGES += \
	bash					\
	sqlite3					\
	su                                      \
	busybox

# Wifi AP mode
PRODUCT_PACKAGES += \
	wlan_tool 		\
	hostapd 		\
	hostapd_cli		\
	hostapd_client          \
	hostapd.conf		\
	hostapd_wps		\
	libhostapd_client	\
	wmiconfig		\
	iwconfig

# keyboard mapping files.
PRODUCT_PACKAGES +=				\
	Dell_Dell_USB_Keyboard.kcm			\
	mxckpd.kcm					\

# imx5x Hardware HAL libs.
PRODUCT_PACKAGES +=				\
	sensors.imx5x					\
	overlay.imx5x					\
	lights.freescale				\
	gralloc.imx5x					\
	copybit.imx5x					\
	alsa.imx5x					\
	magd

# Bluetooth firmware files.
PRODUCT_PACKAGES +=				\
	ar3kbdaddr.pst					\
	PS_ASIC.pst					\
	RamPatch.txt					\

# Freescale VPU firmware files.
PRODUCT_PACKAGES +=				\
	vpu_fw_imx51.bin				\
	vpu_fw_imx53.bin				\

# Atheros wifi firmwre files.
PRODUCT_PACKAGES +=				\
	athwlan.bin.z77					\
	data.patch.hw2_0.bin				\
	eeprom.data					\
	eeprom.bin					\
	calData_ar6102_15dBm.bin			\


# render related libs. align to device/fsl/proprietary/render/fsl-render.mk
PRODUCT_PACKAGES += \
	libIpuRender.so

# gpu related libs. align to device/fsl/proprietary/gpu/fsl-gpu.mk
PRODUCT_PACKAGES += \
	libEGL_imx51.so					\
	libGLESv1_CM_imx51.so				\
	libGLESv2_imx51.so				\
	egl.cfg						\
	libgsl-fsl					\
	libc2d_z160					\
	libc2d_z430					\

# gps related lib
PRODUCT_PACKAGES += \
	gps.default

# Omx related libs, please align to device/fsl/proprietary/omx/fsl-omx.mk
omx_libs :=						\
	core_register					\
	component_register				\
	contentpipe_register				\
	fslomx.cfg					\
	media_profiles.xml				\
	ComponentRegistry.txt				\
	lib_omx_player_arm11_elinux			 \
	lib_omx_client_arm11_elinux			\
	lib_omx_core_mgr_v2_arm11_elinux		\
	lib_omx_core_v2_arm11_elinux			\
	lib_omx_osal_v2_arm11_elinux			\
	lib_omx_common_v2_arm11_elinux			\
	lib_omx_utils_v2_arm11_elinux			\
	lib_omx_res_mgr_v2_arm11_elinux			\
	lib_omx_clock_v2_arm11_elinux			\
	lib_omx_local_file_pipe_v2_arm11_elinux		\
	lib_omx_shared_fd_pipe_arm11_elinux		\
	lib_omx_https_pipe_arm11_elinux			\
	lib_omx_fsl_parser_v2_arm11_elinux		\
	lib_omx_wav_parser_v2_arm11_elinux		\
	lib_omx_mp3_parser_v2_arm11_elinux		\
	lib_omx_aac_parser_v2_arm11_elinux		\
	lib_omx_flac_parser_v2_arm11_elinux		\
	lib_omx_pcm_dec_v2_arm11_elinux			\
	lib_omx_mp3_dec_v2_arm11_elinux			\
	lib_omx_aac_dec_v2_arm11_elinux			\
	lib_omx_amr_dec_v2_arm11_elinux			\
	lib_omx_vorbis_dec_v2_arm11_elinux		\
	lib_omx_flac_dec_v2_arm11_elinux		\
	lib_omx_audio_processor_v2_arm11_elinux		\
	lib_omx_sorenson_dec_v2_arm11_elinux		\
	lib_omx_android_audio_render_arm11_elinux	\
	lib_omx_audio_fake_render_arm11_elinux		\
	lib_omx_ipulib_render_arm11_elinux		\
	lib_avi_parser_arm11_elinux.3.0			\
	lib_divx_drm_arm11_elinux			\
	lib_mp4_parser_arm11_elinux.3.0			\
	lib_mkv_parser_arm11_elinux.3.0			\
	lib_flv_parser_arm11_elinux.3.0			\
	lib_id3_parser_arm11_elinux			\
	lib_wav_parser_arm11_elinux			\
	lib_mp3_parser_v2_arm11_elinux			\
	lib_aac_parser_arm11_elinux			\
	lib_flac_parser_arm11_elinux			\
	lib_mp3_dec_v2_arm12_elinux			\
	lib_aac_dec_v2_arm12_elinux			\
	lib_flac_dec_v2_arm11_elinux			\
	lib_nb_amr_dec_v2_arm9_elinux			\
	lib_oggvorbis_dec_v2_arm11_elinux		\
	lib_peq_v2_arm11_elinux				\
	lib_mpg2_parser_arm11_elinux.3.0		\
	libstagefrighthw				\
	libxec						\
	lib_omx_vpu_v2_arm11_elinux			\
	lib_omx_vpu_dec_v2_arm11_elinux			\
	lib_vpu_wrapper					\
	lib_ogg_parser_arm11_elinux.3.0		\
	libfslxec					\
    lib_omx_overlay_render_arm11_elinux             \
	lib_omx_fsl_muxer_v2_arm11_elinux \
    lib_omx_mp3_enc_v2_arm11_elinux \
    lib_omx_amr_enc_v2_arm11_elinux \
	lib_omx_android_audio_source_arm11_elinux \
	lib_omx_camera_source_arm11_elinux \
	lib_mp4_muxer_arm11_elinux \
	lib_mp3_enc_v2_arm12_elinux \
	lib_nb_amr_enc_v2_arm11_elinux \
	lib_omx_vpu_enc_v2_arm11_elinux \

# Omx excluded libs
omx_excluded_libs :=					\
	lib_asf_parser_arm11_elinux.3.0			\
	lib_wma10_dec_v2_arm12_elinux.so		\
	lib_WMV789_dec_v2_arm11_elinux.so		\
	lib_aacplus_dec_v2_arm11_elinux			\
	lib_ac3_dec_v2_arm11_elinux			\
	\
	lib_omx_wma_dec_v2_arm11_elinux			\
	lib_omx_wmv_dec_v2_arm11_elinux			\
	lib_omx_ac3_dec_v2_arm11_elinux			\


PRODUCT_PACKAGES += $(omx_libs) $(omx_excluded_libs)

PRODUCT_PACKAGES += libubi ubinize ubiformat ubiattach ubidetach ubiupdatevol ubimkvol ubinfo mkfs.ubifs

PRODUCT_LOCALES += hdpi mdpi

PRODUCT_COPY_FILES +=	\
	device/fsl/imx5x/Dell_Dell_USB_Keyboard.kl:system/usr/keylayout/Dell_Dell_USB_Keyboard.kl

PRODUCT_COPY_FILES +=	\
	device/fsl/imx5x/init.rc:root/init.rc

# larger the vm heap size to get better performance
# disable the dalvik jni checking
PRODUCT_PROPERTY_OVERRIDES := \
	dalvik.vm.heapsize=32m	\
	dalvik.vm.checkjni=false

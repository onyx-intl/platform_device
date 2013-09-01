$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)
#$(call inherit-product, $(TOPDIR)frameworks/base/data/sounds/AllAudio.mk)

# overrides
PRODUCT_BRAND := ONYX
PRODUCT_MANUFACTURER := ONYX

# Android infrastructures
PRODUCT_PACKAGES += \
	LiveWallpapers				\
	LiveWallpapersPicker			\
	MagicSmokeWallpapers			\
	Gallery2				\
	Gallery		    			\
	SoundRecorder				\
        Camera                                  \
	FSLOta					\
	VideoEditor				\
	FSLProfileApp				\
	FSLProfileService			\
	VisualizationWallpapers			\
	CubeLiveWallpapers			\
	PinyinIME				\
	libjni_pinyinime        		\
	libRS					\
	librs_jni				\
	pppd					\
	chat					\
	ip-up-vpn				\
	ip-up-ppp0				\
	ip-down-ppp0				\
	wpa_supplicant				\
	wpa_supplicant.conf			\
	wpa_supplicant_p2p.conf			\
	dispd					\
	ts_calibrator				\
	libion                                  \
	display_mode_fb0.conf                   \
	display_mode_fb2.conf                   \
	display_mode_fb4.conf

# Debug utils
PRODUCT_PACKAGES += \
	busybox					\
	bash					\
	taskset					\
	sqlite3					\
	libefence				\
	powerdebug

# Wifi AP mode

# keyboard mapping files.
PRODUCT_PACKAGES += \
	Dell_Dell_USB_Keyboard.kcm		\
	mxckpd.kcm				\

#audio related lib

# imx6 Hardware HAL libs.
PRODUCT_PACKAGES += \
	lights.freescale			\
	gralloc.imx6				\
	copybit.imx6				\
	hwcomposer.imx6             		\
	magd

# Bluetooth firmware files.
PRODUCT_PACKAGES += \
	ar3kdbaddr.pst				\
	PS_ASIC.pst				\
	RamPatch.txt

# Freescale VPU firmware files.
PRODUCT_PACKAGES += \
	libvpu					\
	vpu_fw_imx6q.bin			\
	vpu_fw_imx6d.bin			\

# Atheros wifi firmwre files.
PRODUCT_PACKAGES += \
	fw-3                    		\
	bdata                   		\
	athtcmd_ram             		\
	nullTestFlow            		\
	cfg80211.ko             		\
	compat.ko               		\
	ath6kl_sdio.ko          		\
	check_wifi_mac.sh


# drm related lib
PRODUCT_PACKAGES += \
	drmserver                   		\
	libdrmframework_jni         		\
	libdrmframework             		\
	libdrmpassthruplugin        		\
	libfwdlockengine            		\


PRODUCT_PACKAGES += libubi ubinize ubiformat ubiattach ubidetach ubiupdatevol ubimkvol ubinfo mkfs.ubifs

# e2fsprogs libs
PRODUCT_PACKAGES += \
	mke2fs		\
	libext2_blkid	\
	libext2_com_err	\
	libext2_e2p	\
	libext2_profile	\
	libext2_uuid	\
	libext2fs

PRODUCT_LOCALES += hdpi mdpi

PRODUCT_COPY_FILES +=	\
	device/fsl/common/input/Dell_Dell_USB_Keyboard.kl:system/usr/keylayout/Dell_Dell_USB_Keyboard.kl \
	device/fsl/common/input/Dell_Dell_USB_Keyboard.idc:system/usr/idc/Dell_Dell_USB_Keyboard.idc \
	device/fsl/common/input/eGalax_Touch_Screen.idc:system/usr/idc/eGalax_Touch_Screen.idc \
	device/fsl/common/input/eGalax_Touch_Screen.idc:system/usr/idc/HannStar_P1003_Touchscreen.idc \
	device/fsl/imx6/etc/init.rc:root/init.rc \
	device/fsl/imx6/etc/apns-conf.xml:system/etc/apns-conf.xml \
	device/fsl/imx6/etc/init.usb.rc:root/init.freescale.usb.rc \
	device/fsl/imx6/etc/ueventd.freescale.rc:root/ueventd.freescale.rc \
	device/fsl/imx6/etc/ota.conf:system/etc/ota.conf \
	device/fsl/common/display/display_mode_fb0.conf:system/etc/display_mode_fb0.conf \
	device/fsl/common/display/display_mode_fb2.conf:system/etc/display_mode_fb2.conf \
	device/fsl/common/display/display_mode_fb4.conf:system/etc/display_mode_fb4.conf

PRODUCT_COPY_FILES +=	\
	external/linux-firmware-imx/firmware/vpu/vpu_fw_imx6d.bin:system/lib/firmware/vpu/vpu_fw_imx6d.bin 	\
	external/linux-firmware-imx/firmware/vpu/vpu_fw_imx6q.bin:system/lib/firmware/vpu/vpu_fw_imx6q.bin

# for property
PRODUCT_DEFAULT_PROPERTY_OVERRIDES := \
	persist.sys.usb.config=mtp

# include a google recommand heap config file.
#include frameworks/base/build/tablet-dalvik-heap.mk

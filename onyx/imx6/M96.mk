# This is a FSL Android Reference Design platform based on i.MX6Q ARD board
# It will inherit from FSL core product which in turn inherit from Google generic

$(call inherit-product, device/onyx/imx6/imx6.mk)

# Overrides
PRODUCT_NAME := M96
PRODUCT_DEVICE := M96
PRODUCT_MODEL := ONYX_BOOX

include device/onyx/imx6/evk/ProductCommonEvk.mk

#eink apk
PRODUCT_PACKAGES += \
	Highlight                   	\
	HandWriting			\
	HandWriting2			\
	FastPageTurn			\
	Concurrent			\
	Animation

#TP daemon
PRODUCT_PACKAGES += \
	onyx_tpd

PRODUCT_COPY_FILES +=	\
	device/onyx/$(PRODUCT_NAME)/init.rc:root/init.freescale.rc \
	device/onyx/common/input/gpio-keys.idc:system/usr/idc/gpio-keys.idc \
	device/onyx/common/input/gpio-keys.kl:system/usr/keylayout/gpio-keys.kl \
	device/onyx/common/input/hanvon_tp.idc:system/usr/idc/hanvon_tp.idc \

PRODUCT_COPY_FILES += \
	frameworks/base/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml 


PRODUCT_PROPERTY_OVERRIDES += \
			      wifi.interface=wlan0


# This is a FSL Android Reference Design platform based on i.MX6Q ARD board
# It will inherit from FSL core product which in turn inherit from Google generic

$(call inherit-product, device/fsl/imx6/imx6.mk)

# Overrides
PRODUCT_NAME := evk_6sl_eink
PRODUCT_DEVICE := evk_6sl_eink
PRODUCT_MODEL := EVK-MX6SL

include device/fsl/imx6/evk/ProductCommonEvk.mk

#eink apk
PRODUCT_PACKAGES += \
	Highlight                   	\
	HandWriting			\
	HandWriting2			\
	FastPageTurn			\
	Concurrent			\
	Animation

PRODUCT_COPY_FILES +=	\
	device/fsl/evk_6sl_eink/init.rc:root/init.freescale.rc \
	device/fsl/common/input/imx-keypad.idc:system/usr/idc/imx-keypad.idc \
	device/fsl/common/input/imx-keypad.kl:system/usr/keylayout/imx-keypad.kl \
	device/fsl/common/input/eGalax_Touch_Screen.idc:system/usr/idc/elan-touch.idc

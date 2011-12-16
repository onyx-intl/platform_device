# This is a FSL Android Reference Design platform based on i.MX51 BBG board
# It will inherit from FSL core product which in turn inherit from Google generic

$(call inherit-product, device/fsl/imx5x/imx5x.mk)

# Overrides
PRODUCT_NAME := imx53_evk
PRODUCT_DEVICE := imx53_evk

PRODUCT_COPY_FILES += \
	device/fsl/imx53_evk/mxckpd.kl:system/usr/keylayout/mxckpd.kl \
	device/fsl/imx53_evk/required_hardware.xml:system/etc/permissions/required_hardware.xml \
	device/fsl/imx53_evk/init.rc:root/init.freescale.rc \
        device/fsl/imx53_evk/vold.fstab:system/etc/vold.fstab

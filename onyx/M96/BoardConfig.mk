#
# Product-specific compile-time definitions.
#

include device/onyx/imx6/soc/imx6sl.mk
include device/onyx/imx6/evk/BoardConfigEvk.mk
include device/fsl-proprietary/gpu-viv/fsl-gpu.mk

TARGET_BOOTLOADER_BOARD_NAME := $(TARGET_PRODUCT)
USE_CAMERA_STUB := false
BOARD_HAVE_IMX_CAMERA := false
HAVE_FSL_EPDC_FB := true
BOARD_HAVE_HARDWARE_GPS := false
USE_ATHR_GPS_HARDWARE := false
BOARD_HAS_SENSOR := false
SENSOR_MMA8450 := false

TARGET_KERNEL_DEFCONF := imx6s_onyx_android_defconfig
BOARD_KERNEL_CMDLINE := console=ttymxc0,115200 init=/init androidboot.console=ttymxc0 video=mxcepdcfb:E97_V110,bpp=16 video=mxc_elcdif_fb:off
TARGET_BOOTLOADER_CONFIG := mx6sl:onyx_mx6sl_config

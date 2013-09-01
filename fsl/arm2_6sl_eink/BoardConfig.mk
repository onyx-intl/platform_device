#
# Product-specific compile-time definitions.
#

include device/fsl/imx6/soc/imx6sl.mk
include device/fsl/imx6/arm2/BoardConfigArm2.mk
include device/fsl-proprietary/gpu-viv/fsl-gpu.mk

USE_CAMERA_STUB := true
BOARD_HAVE_IMX_CAMERA := false
HAVE_FSL_EPDC_FB := true


BOARD_KERNEL_CMDLINE := console=ttymxc0,115200 init=/init androidboot.console=ttymxc0 max17135:pass=2,vcom=-2030000 video=mxcepdcfb:E060SCM,bpp=16 video=mxc_elcdif_fb:off
TARGET_BOOTLOADER_CONFIG := mx6sl:mx6sl_arm2_android_config

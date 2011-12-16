#
# Product-specific compile-time definitions.
#

include device/fsl/imx5x/BoardConfigCommon.mk

TARGET_BOOTLOADER_BOARD_NAME := BBG

BOARD_SOC_CLASS := IMX5X
BOARD_SOC_TYPE := IMX51
BOARD_SOC_REV := TO2

WIFI_DRIVER_MODULE_NAME     := "ar6000"
WPA_SUPPLICANT_VERSION      := VER_0_6_ATHEROS
BOARD_WLAN_ATHEROS_SDK      := system/wlan/atheros/AR6kSDK
WPA_SUPPLICANT_VERSION      := VER_0_6_ATHEROS
BOARD_WPA_SUPPLICANT_DRIVER := AR6000
BOARD_WLAN_CHIP_AR6102	    := true
BOARD_WLAN_CHIP_AR6003	    := true
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
# Select Wake on wireless mode for AR6003 suspend/resume policy
BOARD_WLAN_PM_SUSPEND       := 2

BOARD_HAVE_VPU := true
HAVE_FSL_IMX_GPU := true
HAVE_FSL_IMX_IPU := true

#for accelerotor sensor, need to define sensor type here if BOARD_HAS_SENSOR is true
BOARD_HAS_SENSOR := false

# for recovery service
TARGET_SELECT_KEY := 28
TARGET_USERIMAGES_USE_EXT4 := true

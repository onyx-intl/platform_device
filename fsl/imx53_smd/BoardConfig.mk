#
# Product-specific compile-time definitions.
#

include device/fsl/imx5x/BoardConfigCommon.mk

TARGET_BOOTLOADER_BOARD_NAME := SMD

BOARD_SOC_CLASS := IMX5X
BOARD_SOC_TYPE := IMX53

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
BOARD_MODEM_VENDOR := AMAZON

BOARD_HAVE_HARDWARE_GPS := false
USE_ATHR_GPS_HARDWARE := false
USE_QEMU_GPS_HARDWARE := false

#for accelerator sensor, need to define sensor type here
BOARD_HAS_SENSOR := true
SENSOR_MMA8451 := true

# for recovery service
TARGET_SELECT_KEY := 28
TARGET_USERIMAGES_USE_EXT4 := true

# atheros 3k BT
BOARD_USE_AR3K_BLUETOOTH := true

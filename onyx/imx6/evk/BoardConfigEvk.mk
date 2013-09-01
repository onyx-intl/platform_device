#
# Product-specific compile-time definitions.
#

include device/onyx/imx6/BoardConfigCommon.mk

TARGET_BOOTLOADER_BOARD_NAME := EVK

BOARD_SOC_CLASS := IMX6

# Wifi
#BOARD_WLAN_VENDOR 			 := ATHEROS
#BOARD_WIFI_VENDOR 			 := realtek
# for atheros vendor
ifeq ($(BOARD_WLAN_VENDOR),ATHEROS)
BOARD_WLAN_DEVICE := ar6003
BOARD_HAS_ATH_WLAN := true
BOARD_WLAN_ATHEROS_SDK := system/wlan/atheros/compat-wireless
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_HOSTAPD_DRIVER := NL80211
WPA_SUPPLICANT_VERSION := VER_0_9_ATHEROS
HOSTAPD_VERSION := VER_0_9_ATHEROS
WIFI_DRIVER_MODULE_PATH         := "/system/lib/modules/ath6kl_sdio.ko"
WIFI_DRIVER_MODULE_NAME         := "ath6kl_sdio"
WIFI_DRIVER_MODULE_ARG          := "suspend_mode=3"
WIFI_DRIVER_P2P_MODULE_ARG      := "suspend_mode=3 ath6kl_p2p=1 debug_mask=0x2413"
WIFI_SDIO_IF_DRIVER_MODULE_PATH := "/system/lib/modules/cfg80211.ko"
WIFI_SDIO_IF_DRIVER_MODULE_NAME := "cfg80211"
WIFI_SDIO_IF_DRIVER_MODULE_ARG  := ""
WIFI_COMPAT_MODULE_PATH  := "/system/lib/modules/compat.ko"
WIFI_COMPAT_MODULE_NAME  := "compat"
WIFI_COMPAT_MODULE_ARG   := ""
WIFI_TEST_INTERFACE      := "sta"
else ifeq ($(BOARD_WIFI_VENDOR), realtek)
    WPA_SUPPLICANT_VERSION := VER_0_8_X
    BOARD_WLAN_RTL_SDK := system/wlan/realtek/rtl8723a
    #BOARD_WPA_SUPPLICANT_DRIVER := WEXT
    BOARD_WPA_SUPPLICANT_DRIVER := NL80211
    BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_rtl
    BOARD_HOSTAPD_DRIVER        := NL80211
    BOARD_HOSTAPD_PRIVATE_LIB   := lib_driver_cmd_rtl

    #BOARD_WLAN_DEVICE := rtl8192cu
    #BOARD_WLAN_DEVICE := rtl8192du
    #BOARD_WLAN_DEVICE := rtl8192ce
    #BOARD_WLAN_DEVICE := rtl8192de
    #BOARD_WLAN_DEVICE := rtl8723as
    BOARD_WLAN_DEVICE := rtl8723au
    #BOARD_WLAN_DEVICE := rtl8188es

    WIFI_DRIVER_MODULE_NAME   := 8723as
    WIFI_DRIVER_MODULE_PATH   := "/system/lib/modules/8723as.ko"

    WIFI_DRIVER_MODULE_ARG    := ""
    WIFI_FIRMWARE_LOADER      := ""
    WIFI_DRIVER_FW_PATH_STA   := ""
    WIFI_DRIVER_FW_PATH_AP    := ""
    WIFI_DRIVER_FW_PATH_P2P   := ""
    WIFI_DRIVER_FW_PATH_PARAM := ""
endif

BOARD_HAVE_VPU := true
BOARD_MODEM_VENDOR := AMAZON

BOARD_HAVE_HARDWARE_GPS := false
USE_ATHR_GPS_HARDWARE := false
USE_QEMU_GPS_HARDWARE := false

#for accelerator sensor, need to define sensor type here
#BOARD_HAS_SENSOR := true
#SENSOR_MMA8451 := true

# for recovery service
TARGET_SELECT_KEY := 28
TARGET_USERIMAGES_USE_EXT4 := true

# atheros 3k BT
BOARD_USE_AR3K_BLUETOOTH := false

USE_ION_ALLOCATOR := false
USE_GPU_ALLOCATOR := true

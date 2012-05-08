#
# Product-specific compile-time definitions.
#

TARGET_BOARD_PLATFORM := imx5x
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH_VARIANT := armv7-a-neon

TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_NO_RECOVERY := false
TARGET_NO_RADIOIMAGE := true
TARGET_BUILD_KERNEL := true
TARGET_KERNEL_DEFCONF := onyx_m92_android_defconfig
TARGET_KERNEL_INITRAMFS_DEFCONF := onyx_m92_android_initramfs_defconfig

TARGET_PROVIDES_INIT_RC := true

#BOARD_USES_GENERIC_AUDIO := true
BOARD_USES_ALSA_AUDIO := true
BUILD_WITH_ALSA_UTILS := true
BOARD_HAVE_BLUETOOTH := true
USE_CAMERA_STUB := false
BOARD_CAMERA_LIBRARIES := libcamera

BOARD_HAVE_WIFI := true

BOARD_HAVE_MODEM := true
BOARD_MODEM_VENDOR := HUAWEI
BOARD_MODEM_ID := EM750M
BOARD_MODEM_HAVE_DATA_DEVICE := true

HAVE_FSL_IMX_CODEC := true
BUILD_WITHOUT_FSL_DIRECTRENDER := false
BUILD_WITHOUT_FSL_XEC := true

TARGET_TS_CALIBRATION := false
TARGET_TS_DEVICE := "hanvon_ts"

TARGET_USERIMAGES_BLOCKS := 204800

EXCLUDED_CODEC_BUILD := false
EXCLUDED_CODEC_V2_BUILD := true

BUILD_WITH_GST := false

BUILD_WITH_GST := false

# for ums config, only export one partion instead of the whole disk
UMS_ONEPARTITION_PER_DISK := true

PREBUILT_FSL_IMX_CODEC := true
PREBUILT_FSL_IMX_OMX := true
PREBUILT_FSL_IMX_GPU := true

# for kernel/user space split
TARGET_KERNEL_2G := true

BOARD_RECOVERY_PARTITION_SIZE = 10M

INTERNAL_USERIMAGES_USE_UBIFS=true

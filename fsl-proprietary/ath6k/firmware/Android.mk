ifeq ($(BOARD_HAS_ATH_WLAN),true)

LOCAL_PATH:= $(call my-dir)
define include-ar6k-prebuilt
    include $$(CLEAR_VARS)
    LOCAL_MODULE := $(4)
    LOCAL_MODULE_STEM := $(3)
    LOCAL_MODULE_TAGS := debug eng optional
    LOCAL_MODULE_CLASS := ETC
    LOCAL_MODULE_PATH := $(2)
    LOCAL_SRC_FILES := $(1)
    ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
    include $$(BUILD_PREBUILT)
endef

define add-ar6k-prebuilt-file
    $(eval $(include-ar6k-prebuilt))
endef
# HW2.1.1 firmware

ar6k_hw21_dst_dir := $(TARGET_OUT)/etc/firmware/ath6k/AR6003/hw2.1.1
$(call add-ar6k-prebuilt-file,hw2.1.1/fw-3.bin,$(ar6k_hw21_dst_dir),fw-3.bin,fw-3)
$(call add-ar6k-prebuilt-file,hw2.1.1/bdata.bin,$(ar6k_hw21_dst_dir),bdata.bin,bdata)
$(call add-ar6k-prebuilt-file,hw2.1.1/softmac,$(ar6k_hw21_dst_dir),softmac,softmac)
$(call add-ar6k-prebuilt-file,hw2.1.1/athtcmd_ram.bin,$(ar6k_hw21_dst_dir),athtcmd_ram.bin,athtcmd_ram)
$(call add-ar6k-prebuilt-file,hw2.1.1/nullTestFlow.bin,$(ar6k_hw21_dst_dir),nullTestFlow.bin,nullTestFlow)
ar6k_hw21_dst_dir :=

# HW2.0 firmware
ar6k_hw20_dst_dir := $(TARGET_OUT)/etc/firmware/ath6k/AR6003/hw2.0
$(call add-ar6k-prebuilt-file,hw2.0/otp.bin.z77,$(ar6k_hw20_dst_dir),otp.bin.z77,otp_hw20)
$(call add-ar6k-prebuilt-file,hw2.0/athwlan.bin.z77,$(ar6k_hw20_dst_dir),athwlan.bin.z77,athwlan_hw20)
$(call add-ar6k-prebuilt-file,hw2.0/fakeBoardData_AR6003_v2_0.bin,$(ar6k_hw20_dst_dir),bdata.bin,bdata_hw20)
$(call add-ar6k-prebuilt-file,hw2.0/fakeBoardData_AR6003_v2_0.bin,$(ar6k_hw20_dst_dir),bdata.SD31.bin,bdataSD31_hw20)
$(call add-ar6k-prebuilt-file,hw2.0/data.patch.hw2_0.bin,$(ar6k_hw20_dst_dir),data.patch.bin,datapatch_hw20)
$(call add-ar6k-prebuilt-file,hw2.0/athtcmd_ram.bin,$(ar6k_hw20_dst_dir),athtcmd_ram.bin,athtcmdram_hw20)

#Android build system ignores this file while installing, hence forcing
ALL_PREBUILT += $(TARGET_OUT)/etc/firmware/ath6k/AR6003/hw2.0/athtcmd_ram.bin

ar6k_hw20_dst_dir :=

endif

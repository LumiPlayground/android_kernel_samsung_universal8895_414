# SPDX-License-Identifier: GPL-2.0
# UFSHCD makefile
obj-$(CONFIG_SCSI_UFS_DWC_TC_PCI) += tc-dwc-g210-pci.o ufshcd-dwc.o tc-dwc-g210.o
obj-$(CONFIG_SCSI_UFS_DWC_TC_PLATFORM) += tc-dwc-g210-pltfrm.o ufshcd-dwc.o tc-dwc-g210.o
obj-$(CONFIG_SCSI_UFS_QCOM) += ufs-qcom.o
obj-$(CONFIG_SCSI_UFSHCD) += ufshcd.o
obj-$(CONFIG_SCSI_UFSHCD_PCI) += ufshcd-pci.o
obj-$(CONFIG_SCSI_UFSHCD_PLATFORM) += ufshcd-pltfrm.o
obj-$(CONFIG_SCSI_UFS_EXYNOS) += ufs-exynos.o ufs-exynos-dbg.o
obj-$(CONFIG_SCSI_UFS_EXYNOS_LEGACY) += ufs-exynos-legacy.o ufs-exynos-dbg.o
obj-$(CONFIG_SOC_EXYNOS8895) += ufs-cal-8895.o
obj-$(CONFIG_SOC_EXYNOS9810) += ufs-cal-9810.o
obj-$(CONFIG_SOC_EXYNOS9610) += ufs-cal-9610.o
obj-$(CONFIG_SOC_EXYNOS9630) += ufs-cal-9630.o
ifneq (,$(filter $(CONFIG_SCSI_UFS_EXYNOS_SMU) $(CONFIG_SCSI_UFS_EXYNOS_FMP),y))
obj-y += ufs-exynos-fmp.o
endif

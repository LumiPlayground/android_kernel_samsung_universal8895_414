# Exynos 8895 Android 17 / Linux 4.14 development

Experimental hardware bring-up, not a complete Android 17 kernel or flashable release.
The ROM built with the 4.4 kernel remains separate.

Upstream: https://github.com/LumiPlayground/android_kernel_samsung_universal8895_414
Pinned donor: a7432fa4d30426fdd45bf0c0c03d3a930056fa90 (8895-rebase).
Original source history and licensing are retained by this GitHub fork.
Actual source release: Linux 4.14.113; no version string spoof is added here.
The donor reports boot/pstore support, not a fully working Android device.

Initial changes:
- Fix the duplicated S8+ DTB entry so S8, S8+ and Note8 DTBs are selected.
- Add an Android bring-up defconfig with explicit Binder devices, XZ initrd,
  swap/ZRAM, BPF, cgroups and seccomp settings.
- Add a manually triggered Image/DTB build preserving failure logs.

The donor configuration uses simple framebuffer, early console and maxcpus=4.
These debugging settings are retained until hardware logs justify switching
to full display and CPU/power paths. This is not a production configuration.
KernelSU Next has not been integrated into this 4.14 tree.

Required before connecting this tree to the ROM build:
1. Pass Image/all three DTB builds and check the effective .config.
2. Establish reproducible S8 recovery/initramfs boot with pstore logs.
3. Adapt/test UFS, PMIC, clocks, CPU/power, ION/dma-buf, Mali/DECON,
   camera, audio, modem and Wi-Fi with the pinned vendor binaries.
4. Validate Android init/cgroups/Binder/SELinux, the actual BPF loader,
   networking and tethering. Linux 4.14 alone does not guarantee Android 17.
5. Integrate KernelSU after a working baseline, then package ROM boot images.

No physical boot or driver validation is claimed by this branch.

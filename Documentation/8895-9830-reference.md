# Pinned Android 17 reference comparison

Reference: LineageOS/android_kernel_samsung_universal9830, lineage-24.0,
97369af7bbd66581d3e993fea083f3eed02d3c20 (Linux 4.19.325).
URL: https://github.com/LineageOS/android_kernel_samsung_universal9830/tree/97369af7bbd66581d3e993fea083f3eed02d3c20

This does not turn Exynos 8895 into a 9830 device. No 9830 board drivers,
device trees or arbitrary subsystem directories are copied.

The first comparison found that the 8895 donor disabled F2FS, ext4/F2FS
file encryption, BPF traffic classifier/actions, and some cgroup controllers.
These are implemented in the existing 4.14 source and are now selected in
the Android configuration. The actual 8895 fstab has both ext4 and F2FS /data
entries with fileencryption=aes-256-xts; both filesystem encryption paths and
their key/XTS dependencies must therefore be available in the Image.
The donor also implements the f2fs fsync_mode=nobarrier mount option.

CI checks the generated .config and fails on silently dropped options.
Enabling features is not evidence of successful mounts or Android boot.

Remaining gaps include BinderFS, PSI, newer fscrypt policies and newer BPF
program/map/helper implementations. The 9830 tree contains significant
backports beyond its release number. Its full BPF directory cannot simply
replace 4.14's without adapting core networking, memory and cgroup APIs.
No kernel release override is introduced to hide those gaps.

Still required: real 8895 display/GPU/audio/camera/modem/Wi-Fi integration,
UFS mounting, matching vendor userspace, and physical boot/subsystem tests.
The original 4.4 ROM currently reboots from the Samsung logo into TWRP;
the user reported empty crash logs, so its root cause is unproven.

# Experimental Exynos 8895 display port

Source: BasicOS2025/android_kernel_samsung_universal8895,
lineage-24.0 at 3ac10c9f390b0edee601791cb6f655e96eef9591.
The Samsung copyrights and GPL notices are retained in imported files.

The 8895 DPU/panel code is compiled in an isolated branch to identify the
real 4.4-to-4.14 API changes. This is not a working display driver yet.
Known adaptation areas: ION client/handle APIs, sync_fence to dma_fence/sync_file,
IOVMM, BTS/clock and media interfaces. No dummy synchronization or successful
return stubs may be substituted for real hardware operations.

CI builds the selected display objects, not a flashable boot image. Passing
this compile probe alone does not prove linked-kernel or hardware operation.
The previous full Image/DTB baseline remains on experimental/android17-4.14.

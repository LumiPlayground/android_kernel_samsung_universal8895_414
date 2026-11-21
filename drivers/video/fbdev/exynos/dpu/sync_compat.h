/* SPDX-License-Identifier: GPL-2.0 */
/* Exynos 8895 display migration: real 4.14 dma-fence/sync-file operations. */
#ifndef EXYNOS8895_SYNC_COMPAT_H
#define EXYNOS8895_SYNC_COMPAT_H
#include <linux/file.h>
#include <linux/jiffies.h>
#include <linux/sync_file.h>
#include "../../../../dma-buf/sync_debug.h"

#define sync_fence sync_file
#define sw_sync_timeline sync_timeline
#define sw_sync_timeline_create sync_timeline_create
#define sw_sync_timeline_inc sync_timeline_signal
#define sw_sync_pt_create sync_pt_create

static inline void sync_pt_free(struct sync_pt *pt)
{
    dma_fence_put(&pt->base);
}

static inline struct sync_file *sync_fence_create(const char *name, struct sync_pt *pt)
{
    struct sync_file *file = sync_file_create(&pt->base);
    if (file) {
        strlcpy(file->user_name, name, sizeof(file->user_name));
        /* The file now owns the reference; the caller frees pt on failure. */
        dma_fence_put(&pt->base);
    }
    return file;
}

static inline struct sync_file *sync_fence_fdget(int fd)
{
    struct dma_fence *fence = sync_file_get_fence(fd);
    struct sync_file *file;
    if (!fence)
        return NULL;
    file = sync_file_create(fence);
    dma_fence_put(fence);
    if (file)
        sync_file_get_name(file, file->user_name, sizeof(file->user_name));
    return file;
}

static inline void sync_fence_put(struct sync_file *file)
{
    fput(file->file);
}

static inline void sync_fence_install(struct sync_file *file, int fd)
{
    fd_install(fd, file->file);
}

static inline int sync_fence_wait(struct sync_file *file, unsigned int timeout_ms)
{
    long ret = dma_fence_wait_timeout(file->fence, true, msecs_to_jiffies(timeout_ms));
    if (ret < 0)
        return ret;
    if (!ret)
        return -ETIME;
    ret = dma_fence_get_status(file->fence);
    return ret < 0 ? ret : 0;
}

static inline const char *sync_status_str(int status)
{
    return status < 0 ? "error" : status ? "signaled" : "active";
}
#endif

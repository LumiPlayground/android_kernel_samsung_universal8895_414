/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/plist.h>
#include <linux/sched/idle.h>
#include <linux/sched/topology.h>

struct gb_qos_request {
	struct plist_node node;
	char *name;
	bool active;
};

struct rq;

#ifdef CONFIG_SCHED_EMS
/*
 * core
 */
extern int
exynos_select_task_rq(struct task_struct *p, int prev_cpu, int sd_flag, int sync, int wakeup);
extern void init_ems(void);


/*
 * init util
 */
extern void post_init_entity_multi_load(struct sched_entity *se);


/*
 * energy model
 */
enum {
	STATES_FREQ = 0,
	STATES_PMQOS,
	NUM_OF_REQUESTS,
};
extern void init_sched_energy_table(struct cpumask *cpus, int table_size,
				unsigned long *f_table, unsigned int *v_table,
				int max_f, int min_f);
extern void rebuild_sched_energy_table(struct cpumask *cpus, int clipped_freq,
						int max_freq, int type);


/*
 * multi load
 */
extern unsigned long ml_boosted_cpu_util(int cpu);
extern void init_multi_load(struct sched_entity *se);
extern void update_multi_load(u64 now, int cpu, struct cfs_rq *cfs_rq, struct sched_entity *se,
				struct sched_avg *sa, unsigned long load, int running);
extern void attach_entity_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se);
extern void detach_entity_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se);
extern void remove_entity_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se);
extern void apply_removed_multi_load(struct cfs_rq *cfs_rq);
extern void update_tg_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se,
				struct cfs_rq *gcfs_rq);
extern void util_est_enqueue_multi_load(struct cfs_rq *cfs_rq, struct task_struct *p);
extern void util_est_dequeue_multi_load(struct cfs_rq *cfs_rq, struct task_struct *p, bool task_sleep);
extern void util_est_update(struct task_struct *p, int prev_util_est, int next_util_est);
extern void set_part_period_start(struct rq *rq);
extern void update_cpu_active_ratio(struct rq *rq, struct task_struct *p, int type);
extern void part_cpu_active_ratio(unsigned long *util, unsigned long *max, int cpu);


/*
 * ontime migration
 */
extern int ontime_can_migrate_task(struct task_struct *p, int dst_cpu);
extern void ontime_migration(void);


/*
 * global boost
 */
extern void gb_qos_update_request(struct gb_qos_request *req, u32 new_value);


/*
 * load balance
 */
extern struct list_head *lb_cfs_tasks(struct rq *rq, int sse);
extern void lb_add_cfs_task(struct rq *rq, struct sched_entity *se);
extern int lb_check_priority(int src_cpu, int dst_cpu);
extern struct list_head *lb_prefer_cfs_tasks(int src_cpu, int dst_cpu);
extern int lb_need_active_balance(enum cpu_idle_type idle,
				struct sched_domain *sd, int src_cpu, int dst_cpu);
extern bool lb_sibling_overutilized(int dst_cpu, struct sched_domain *sd,
					struct cpumask *lb_cpus);
extern bool lbt_overutilized(int cpu, int level);
extern void update_lbt_overutil(int cpu, unsigned long capacity);
extern void lb_update_misfit_status(struct task_struct *p, struct rq *rq, unsigned long task_h_load);

#else /* CONFIG_SCHED_EMS */

/*
 * core
 */
static inline int
exynos_select_task_rq(struct task_struct *p, int prev_cpu, int sd_flag, int sync, int wakeup)
{
	return -1;
}
static inline void init_ems(void) { }


/*
 * init util
 */
static inline void post_init_entity_multi_load(struct sched_entity *se) { }


/*
 * energy model
 */
static inline void init_sched_energy_table(struct cpumask *cpus, int table_size,
				unsigned long *f_table, unsigned int *v_table,
				int max_f, int min_f) { }
static inline void reconstruct_sched_energy_table_qos(struct cpumask *cpus,
					int clipped_freq, int max_freq) { }

/*
 * multi load
 */
static inline unsigned long ml_boosted_cpu_util(int cpu) { return 0; }
static inline void init_multi_load(struct sched_entity *se) { }
static inline void update_multi_load(u64 now, int cpu, struct cfs_rq *cfs_rq, struct sched_entity *se,
				struct sched_avg *sa, unsigned long load, int running) { }
static inline void attach_entity_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se) { }
static inline void detach_entity_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se) { }
static inline void remove_entity_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se) { }
static inline void apply_removed_multi_load(struct cfs_rq *cfs_rq) { }
static inline void update_tg_multi_load(struct cfs_rq *cfs_rq, struct sched_entity *se,
				struct cfs_rq *gcfs_rq) { }
static inline void util_est_enqueue_multi_load(struct cfs_rq *cfs_rq, struct task_struct *p) { }
static inline void util_est_dequeue_multi_load(struct cfs_rq *cfs_rq, struct task_struct *p, bool task_sleep) { }
static inline void util_est_update(struct task_struct *p, int prev_util_est, int next_util_est) { }
static inline void set_part_period_start(struct rq *rq) { }
static inline void update_cpu_active_ratio(struct rq *rq, struct task_struct *p, int type) { }
static inline void part_cpu_active_ratio(unsigned long *util, unsigned long *max, int cpu) { }


/*
 * ontime migration
 */
static inline int ontime_can_migrate_task(struct task_struct *p, int dst_cpu) { return 1; }
static inline void ontime_migration(void) { }


/*
 * global boost
 */
static inline void gb_qos_update_request(struct gb_qos_request *req, u32 new_value) { }


/*
 * load balance
 */
static inline void lb_add_cfs_task(struct rq *rq, struct sched_entity *se) { }
static inline int lb_check_priority(int src_cpu, int dst_cpu)
{
	return 0;
}
static inline struct list_head *lb_prefer_cfs_tasks(int src_cpu, int dst_cpu)
{
	return NULL;
}
static inline int lb_need_active_balance(enum cpu_idle_type idle,
				struct sched_domain *sd, int src_cpu, int dst_cpu)
{
	return 0;
}
static inline bool lb_sibling_overutilized(int dst_cpu, struct sched_domain *sd,
					struct cpumask *lb_cpus)
{
	return true;
}
static inline bool lbt_overutilized(int cpu, int level)
{
	return false;
}
static inline void update_lbt_overutil(int cpu, unsigned long capacity) { }
static inline void lb_update_misfit_status(struct task_struct *p, struct rq *rq, unsigned long task_h_load) { }

#endif /* CONFIG_SCHED_EMS */

extern unsigned int frt_disable_cpufreq;

#if defined(CONFIG_SCHED_EMS) && defined (CONFIG_SCHED_TUNE)
enum stune_group {
	STUNE_ROOT,
	STUNE_FOREGROUND,
	STUNE_BACKGROUND,
	STUNE_TOPAPP,
	STUNE_RT,
	STUNE_GROUP_COUNT,
};
void emst_cpu_update(int cpu, u64 now);
unsigned long emst_boost(int cpu, unsigned long util);
#else
static inline void emst_cpu_update(int cpu, u64 now) { };
static inline unsigned long emst_boost(int cpu, unsigned long util) { return util; };
#endif

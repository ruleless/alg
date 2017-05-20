#ifndef __ALG_PROFILER_H__
#define __ALG_PROFILER_H__

#include <stdio.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROFILER_NAME_LEN    256
#define PROFILER_STACKFRAME  256
#define MAX_PROFILER_THREADS 64
#define MAX_PROFILER_NUM     1024

typedef unsigned int profiler_clock_t;
typedef struct profiler_node_s profiler_node_t;
typedef struct profiler_frame_s profiler_frame_t;

struct profiler_node_s {
    char name[PROFILER_NAME_LEN];

    profiler_clock_t max_time;
    profiler_clock_t min_time;
    profiler_clock_t average_time;
    
    profiler_clock_t last_time;
    profiler_clock_t elapse_time;
};

struct profiler_frame_s {
    profiler_node_t f[PROFILER_STACKFRAME];
    int top;

    unsigned long tid;

    profiler_frame_t *next;
};

#define ALG_PROFILER_START alg_profiler_start(__func__ " line:" __LINE__)

void alg_profiler_start(const char *name);

void alg_profiler_end();

#ifdef __cplusplus
}
#endif

#endif /* __ALG_PROFILER_H__ */


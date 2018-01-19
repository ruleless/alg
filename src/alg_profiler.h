#ifndef __ALG_PROFILER_H__
#define __ALG_PROFILER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROFILER_NAME_LEN    256
#define PROFILER_STACKFRAME  256
#define MAX_PROFILER_THREADS 64
#define MAX_PROFILER_NUM     1024
#define PROFILER_ELAPSE_TIME (1000*60*60)

#ifndef MIN
# define MIN(a, b)  ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
# define MAX(a, b)  ((a) > (b) ? (a) : (b))
#endif

typedef unsigned int profiler_clock_t;
typedef struct profiler_node_s profiler_node_t;
typedef struct profiler_frame_s profiler_frame_t;

struct profiler_node_s {
    char name[PROFILER_NAME_LEN];

    profiler_clock_t max_time;
    profiler_clock_t min_time;
    profiler_clock_t sum_time;
    profiler_clock_t average_time;

    profiler_clock_t last_time;
    profiler_clock_t elapse_time;

    int call_times;
};

struct profiler_frame_s {
    profiler_node_t f[PROFILER_STACKFRAME];
    int top;

    unsigned long tid;

    profiler_frame_t *next;
};

#ifdef _ALG_PROFILER
#define ALG_PROFILER_START                                              \
    do {                                                                \
        char profname[PROFILER_NAME_LEN];                               \
        snprintf(profname, sizeof(profname), \
                 "%s line:%d", __func__, __LINE__);                     \
        alg_profiler_start(profname);                                   \
    } while(0)

#define ALG_PROFILER_END alg_profiler_end()

#define ALG_PROFILER_OUTPUT                                     \
    do {                                                        \
        static const profiler_clock_t FREQUENCY = 1000*60*2;    \
        static profiler_clock_t lasttime = 0;                   \
        profiler_clock_t t = profiler_clock();                  \
        if (t >= lasttime + FREQUENCY) {                        \
            alg_profiler_output();                              \
            lasttime = t;                                       \
        }                                                       \
    } while(0)
#else
#define ALG_PROFILER_START
#define ALG_PROFILER_END
#define ALG_PROFILER_OUTPUT
#endif

profiler_clock_t profiler_clock();

void alg_profiler_start(const char *name);

void alg_profiler_end();

void alg_profiler_output();

#ifdef __cplusplus
}
#endif

#endif /* __ALG_PROFILER_H__ */


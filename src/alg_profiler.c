#include "alg_profiler.h"

#define PROF_LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

static profiler_frame_t threads[MAX_PROFILER_THREADS];
static profiler_frame_t *last_free_thread = &threads[MAX_PROFILER_THREADS-1];
static pthread_mutex_t threads_mut;

static profiler_node_t profs[MAX_PROFILER_NUM];
static pthread_mutex_t profs_mut;

static profiler_frame_t *
get_stackframe()
{
    static const int THREADS_NUM = sizeof(threads)/sizeof(threads[0]);
    
    unsigned long tid = (unsigned long)pthread_self();
    profiler_frame_t *p = &threads[tid % THREADS_NUM];
    
    for (; p != NULL; p = p->next)
    {
        if (p->tid == tid)
        {
            return p;
        }
    }
    
    profiler_frame_t *f = NULL;

    while (last_free_thread > threads && last_free_thread->tid != 0)
        last_free_thread--;
    if (0 == last_free_thread->tid)
        f = last_free_thread;

    if (NULL == f)
    {
        PROF_LOG("found no space for this thread!");
        return NULL;
    }    

    p = &threads[tid % THREADS_NUM];
    if (p->tid != 0 && p->next != NULL)
    {
        profiler_frame_t *other = &threads[p->tid % THREADS_NUM];

        if (other != p)
        {
            while (other->next != p)
                other = other->next;

            other->next = f;
            memcpy(f, p, sizeof(*f));
            p->next = NULL;
        }
        else
        {
            f->next = p->next;
            p->next = f;
            p = f;
        }
    }
    p->tid = tid;
    
    return p;
}

void
alg_profiler_start(const char *name)
{    
    profiler_frame_t *f = NULL;
    
    int i;    

    
    

    if (NULL == f)
    {
        PROF_LOG("found no space to start profiler!");
    }
}

void alg_profiler_end()
{}

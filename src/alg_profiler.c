#include "alg_profiler.h"

#define PROF_LOG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)

static profiler_frame_t threads[MAX_PROFILER_THREADS];
static profiler_frame_t *last_free_thread = &threads[MAX_PROFILER_THREADS-1];
static pthread_mutex_t threads_mut = PTHREAD_MUTEX_INITIALIZER;

static profiler_node_t profs[MAX_PROFILER_NUM];
static int profs_count;
static pthread_mutex_t profs_mut = PTHREAD_MUTEX_INITIALIZER;

profiler_clock_t
profiler_clock()
{
    struct timeval time;
    profiler_clock_t value;
    
    gettimeofday(&time, NULL);    
    value = ((profiler_clock_t)time.tv_sec) * 1000 + (time.tv_usec/1000);
    return value;
}

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

static profiler_node_t *
get_profiler_node(const char *name)
{
    int i;
    profiler_node_t *n;

    for (i = 0; i < profs_count; i++)
    {
        if (strcmp(name, profs[i].name) == 0)
        {
            return &profs[i];
        }
    }

    if (sizeof(profs) / sizeof(profs[0]) == profs_count)
    {
        return NULL;
    }

    n = &profs[profs_count++];
    strncpy(n->name, name, sizeof(n->name) - 1);
    n->max_time = 0;
    n->min_time = PROFILER_ELAPSE_TIME;
    n->sum_time = 0;
    n->average_time = 0;
    n->last_time = 0;
    n->elapse_time = 0;
    n->call_times = 0;

    return n;
}

void
alg_profiler_start(const char *name)
{    
    profiler_frame_t *f = NULL;
    profiler_node_t *n = NULL;

    pthread_mutex_lock(&threads_mut);

    f = get_stackframe();
    if (NULL == f)
    {
        pthread_mutex_unlock(&threads_mut);
        PROF_LOG("found no space to start profiler!");
        return;
    }

    if (sizeof(f->f) / sizeof(f->f[0]) == f->top)
    {
        pthread_mutex_unlock(&threads_mut);
        PROF_LOG("stack overflow!");
        return;
    }

    n = &f->f[++f->top];
    strncpy(n->name, name, sizeof(n->name) - 1);
    n->last_time = profiler_clock();

    pthread_mutex_unlock(&threads_mut);
}

void
alg_profiler_end()
{
    profiler_clock_t t;
    profiler_node_t *curnode, *n;
    profiler_frame_t *f;

    pthread_mutex_lock(&threads_mut);

    f = get_stackframe();
    if (NULL == f || 0 == f->top)
    {
        pthread_mutex_unlock(&threads_mut);
        PROF_LOG("no stackframe found or no refer profiler node!");
        return;
    }

    t = profiler_clock();
    curnode = &f->f[f->top--];

    pthread_mutex_lock(&profs_mut);
    
    n = get_profiler_node(curnode->name);

    if (NULL == n)
    {
        pthread_mutex_unlock(&profs_mut);
        pthread_mutex_unlock(&threads_mut);
        PROF_LOG("found no profiler analysis node");
        return;
    }

    n->last_time = t;
    n->elapse_time = t - curnode->last_time;
    n->max_time = MAX(n->max_time, n->elapse_time);
    n->min_time = MIN(n->min_time, n->elapse_time);
    n->sum_time += n->elapse_time;
    n->call_times++;

    n->average_time = n->sum_time / n->call_times;

    pthread_mutex_unlock(&profs_mut);
    pthread_mutex_unlock(&threads_mut);
}

void
alg_profiler_output()
{
    static FILE *s_proffp = NULL;

    if (NULL == s_proffp)
    {
        time_t nowtime;
        struct tm *timeinfo;
        char pathname[PROFILER_NAME_LEN];
        
        time(&nowtime);
        timeinfo = localtime(&nowtime);
        snprintf(pathname, sizeof(pathname), "/tmp/prof_%04d%02d%02d_%02d%02d%02d",
                 timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                 timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        s_proffp = fopen(pathname, "at");
        if (NULL == s_proffp)
        {
            PROF_LOG("open file failed! pathname=%s", pathname);
            return;
        }
    }

    fprintf(s_proffp, "-------------------------------------------------\n");

    int i;
    profiler_node_t *n;
    
    pthread_mutex_lock(&profs_mut);
    for (i = 0; i < profs_count; i++)
    {
        n = &profs[i];
        fprintf(s_proffp, "==>> %s\n", n->name);
        fprintf(s_proffp, "  max time    : %dms\n", n->max_time);
        fprintf(s_proffp, "  min time    : %dms\n", n->min_time);
        fprintf(s_proffp, "  sum time    : %dms\n", n->sum_time);
        fprintf(s_proffp, "  average time: %dms\n", n->average_time);
        fprintf(s_proffp, "  call times  : %d\n", n->call_times); 
    }
    pthread_mutex_unlock(&profs_mut);
    
    fprintf(s_proffp, "-------------------------------------------------\n");
}

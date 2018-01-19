#include "alg_thread_env.h"

#define MAX_ENV_COUNT 16
#define ENV_KEY_SIZE  32
#define ENV_VAL_SIZE  64

static pthread_once_t g_key_once;
static pthread_key_t  g_key;

typedef struct {
    char key[ENV_KEY_SIZE];
    char val[ENV_VAL_SIZE];
} thread_env_t;

static void free_thread_env(void *data)
{
    thread_env_t **envs = (thread_env_t **)data;
    thread_env_t *e;
    int i;

    for (i = 0; i < MAX_ENV_COUNT; i++)
    {
        e = *(envs + i);
        if (e)
            free(e);
    }
    free(envs);
}

static void init_thread_key()
{
    pthread_key_create(&g_key, free_thread_env);
}

int set_thread_env(const char *key, const char *val)
{
    thread_env_t **envs = NULL;
    int i = 0;

    if (!key || !val)
        return -1;

    pthread_once(&g_key_once, init_thread_key);
    envs = pthread_getspecific(g_key);
    if (!envs)
    {
        envs = malloc(sizeof(void *) * MAX_ENV_COUNT);
        if (!envs)
        {
            return -1;
        }
        memset(envs, NULL, sizeof(envs));
        pthread_setspecific(g_key, envs);
    }

    i = 0;
    while (i < MAX_ENV_COUNT && envs[i]) i++;
    if (MAX_ENV_COUNT == i)
        return -1;

    envs[i] = (thread_env_t *)malloc(sizeof(thread_env_t));
    if (!envs[i])
    {
        return -1;
    }
    snprintf(envs[i]->key, sizeof(envs[i]->key), "%s", key);
    snprintf(envs[i]->val, sizeof(envs[i]->val), "%s", val);

    return 0;
}

const char *get_thread_env(const char *key)
{
    thread_env_t **envs = NULL;
    int i;

    pthread_once(&g_key_once, init_thread_key);
    envs = pthread_getspecific(g_key);
    if (!envs)
    {
        return NULL;
    }

    i = 0;
    while (i < MAX_ENV_COUNT && envs[i])
    {
        if (!strcmp(envs[i]->key, key))
        {
            return envs[i]->val;
        }
    }

    return NULL;
}

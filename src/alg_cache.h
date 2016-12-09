#ifndef __ALG_CACHE_H__
#define __ALG_CACHE_H__

#include "list.h"

typedef int (*alg_cache_flush_handler_pt)(const void *, size_t);
typedef struct alg_cache_seg_s  alg_cache_seg_t;
typedef struct alg_cache_s      alg_cache_t;

struct alg_cache_seg_s {
    struct list_head node;
    
    size_t size;
    char *data;
};

struct alg_cache_s {
    struct list_head            l;

    alg_cache_flush_handler_pt  handler;
};

int alg_cache_init(alg_cache_t *cache);

int alg_cache_push(alg_cache_t *cache, const void *data, size_t size);
int alg_cache_flushall(alg_cache_t *cache);

#endif /* __ALG_CACHE_H__ */

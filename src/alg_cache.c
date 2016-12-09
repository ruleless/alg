#include "alg_cache.h"

int
alg_cache_init(alg_cache_t *cache)
{
    INIT_LIST_HEAD(&cache->l);

    return 1;
}

int
alg_cache_push(alg_cache_t *cache, const void *data, size_t size)
{
    alg_cache_seg_t     *seg;

    seg = (alg_cache_seg_t *)malloc(sizeof(alg_cache_seg_t));
    if (NULL == seg) {
        return 0;
    }

    seg->data = (char *)malloc(size);
    if (NULL == seg->data) {
        free(seg);
        return 0;
    }

    memcpy(seg->data, data, size);
    seg->size = size;
    list_add_tail(&seg->node, &cache->l);

    return 1;
}

int
alg_cache_flushall(alg_cache_t *cache)
{
    struct list_head    *pos, tmp;
    alg_cache_seg_t     *seg;
    
    list_for_each_safe(pos, tmp, &cache->l)
    {
        seg = list_entry(pos, alg_cache_seg_t, node);

        if (cache->handler(seg->data, seg->size)) {
            free(seg->data);
            list_del(&seg->node);
            free(seg);
        } else {
            return 0;
        }            
    }

    return 1;
}

#include "alg_cache.h"

#define MAX_MEM_CACHE_SIZE	256*1024

alg_cache_t *
alg_cache_create(alg_cache_flush_handler_pt h)
{
	alg_cache_t *cache;

	cache = malloc(sizeof(alg_cache_t));
	if (NULL == cache) {
		return NULL;
	}
	
    INIT_LIST_HEAD(&cache->memcache);

	cache->dcache.file = NULL;

	cache->memcache_size = 0;
	cache->dcache_size = 0;
	
	cache->handler = h;

	cache->memcache_maxsize = MAX_MEM_CACHE_SIZE;

    return cache;
}

void
alg_cache_destroy(alg_cache_t *cache)
{
	struct list_head  *pos, *tmp;
	alg_cache_seg_t   *seg;
	
	list_for_each_safe(pos, tmp, &cache->memcache)
    {
        seg = list_entry(pos, alg_cache_seg_t, node);

		free(seg->data);
		list_del(&seg->node);
		free(seg);
    }

	alg_disk_cache_close(&cache->dcache);
}

int
alg_cache_push(alg_cache_t *cache, const void *data, size_t size)
{
    alg_cache_seg_t     *seg;
	ssize_t				 rv;

	/* cache in file */

	if (cache->memcache_size + size > cache->memcache_maxsize
		|| cache->dcache_size) {
		
		rv = alg_disk_cache_write(&cache->dcache, data, size);

		if (rv == size) {
			cache->dcache_size += size;
			return 1;
		}

		return 0;
	}

	/* cache in memory */

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
    list_add_tail(&seg->node, &cache->memcache);

    return 1;
}

int
alg_cache_flushall(alg_cache_t *cache)
{
    struct list_head    *pos, *tmp;
    alg_cache_seg_t     *seg;
	size_t 				 sz;
	char   			    *ptr;

	/* flush data in memory */

    list_for_each_safe(pos, tmp, &cache->memcache)
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

	/* flush data in file */

	while ((sz = alg_disk_cache_peeksize(&cache->dcache))) {
		ptr = (char *)malloc(sz);
		
		assert(ptr && "alg_cache_flushall()  alloc failed!");
		assert(alg_disk_cache_read(&cache->dcache, ptr, sz) == sz);

		if (cache->handler(ptr, sz)) {			
			cache->dcache_size -= sz;
			free(ptr);
		} else {
			free(ptr);
			alg_disk_cache_rollback(&cache->dcache, sz);
		}
	}	

    return 1;
}

int
alg_cache_empty(alg_cache_t *cache)
{
	return 0 == cache->memcache_size && 0 == cache->dcache_size;
}

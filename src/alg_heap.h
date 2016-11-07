#ifndef __ALG_HEAP_H__
#define __ALG_HEAP_H__

#include "alg_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * alg_make_heap - make an array to be max heap
 */
void alg_make_heap(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *));

/**
 * alg_push_heap - insert the last element(ie. base[nsize-1]) to the heap
 */
void alg_push_heap(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *));

/**
 * alg_pop_heap - pop the root from an heap
 *
 * move the first element(ie. base[0]) to
 * the last(ie. base[nsize-1]) and re-heap
 */
void alg_pop_heap(void *base, size_t nmem, size_t nsize,
				  int (*cmp)(void *, void *));

/**
 * alg_heap_sort - sort the array base on max-heap
 */
void alg_heap_sort(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *));

#ifdef __cplusplus
}
#endif

#endif /* __ALG_HEAP_H__ */


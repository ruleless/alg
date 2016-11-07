#ifndef __ALG_HEAP_H__
#define __ALG_HEAP_H__

#include "alg_common.h"

#ifdef __cplusplus
extern "C" {
#endif

void alg_make_heap(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *));

void alg_push_heap(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *));

void alg_pop_heap(void *base, size_t nmem, size_t nsize,
				  int (*cmp)(void *, void *));

#ifdef __cplusplus
}
#endif

#endif /* __ALG_HEAP_H__ */




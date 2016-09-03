#ifndef __ALG_SORT_H__
#define __ALG_SORT_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void alg_inserction_sort(void *base, size_t nmem, size_t nsize,
						 int (*cmp)(void *, void *));

#ifdef __cplusplus
}
#endif

#endif /* __ALG_SORT_H__ */

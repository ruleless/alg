#ifndef __ALG_SORT_H__
#define __ALG_SORT_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * alg_inserction_sort - inserction sort
 * @base:  the first element's pointer of the array
 * @nmen:  element's size in byte
 * @nsize: the num of elements
 * @cmp:   the compair function define by user
 */
void alg_inserction_sort(void *base, size_t nmem, size_t nsize,
						 int (*cmp)(void *, void *));

/**
 * alg_merge_sort - merge sort
 */
void alg_merge_sort(void *base, size_t nmem, size_t nsize,
					int (*cmp)(void *, void *));

/**
 * alg_quick_sort - quick sort
 */
void alg_quick_sort(void *base, size_t nmem, size_t nsize,
					int (*cmp)(void *, void *));

#ifdef __cplusplus
}
#endif

#endif /* __ALG_SORT_H__ */

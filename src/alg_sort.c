#include "alg_sort.h"

#include <stdlib.h>
#include <string.h>

void alg_inserction_sort(void *base, size_t nmem, size_t nsize,
						 int (*cmp)(void *, void *)) {
	char *ptr = (char *)base, *key = (char *)malloc(nmem);
	size_t i, j, insert_pos;
	
	for (j = 1; j < nsize; ++j) {
		memcpy(key, ptr+j*nmem, nmem);
		insert_pos = j;
		i = j-1;
		while (cmp(ptr+i*nmem, key) > 0) {
			memcpy(ptr+i*nmem+nmem, ptr+i*nmem, nmem);
			insert_pos = i;

			if (i-- == 0)
				break;
		}

		if (insert_pos != j) {
			memcpy(ptr+insert_pos*nmem, key, nmem);
		}
	}
	free(key);
}

static void merge_sort(void *base, size_t nmem, size_t low, size_t high,
					   int (*cmp)(void *, void *), void *ext_storage) {
	if (low >= high)
		return;

	size_t mid = (low+high)>>1;
	merge_sort(base, nmem, low, mid, cmp, ext_storage);
	merge_sort(base, nmem, mid+1, high, cmp, ext_storage);

	char *ptr = (char *)base;
	char *dummy = (char *)ext_storage;
	size_t i = low, j = mid+1, k = 0;
	while (i <= mid && j <= high) {
		if (cmp(ptr+i*nmem, ptr+j*nmem) <= 0) {
			memcpy(dummy+k*nmem, ptr+i*nmem, nmem);
			++i;
		} else {
			memcpy(dummy+k*nmem, ptr+j*nmem, nmem);
			++j;
		}
		++k;
	}
	for (; i <= mid; ++i) {
		memcpy(dummy+(k++)*nmem, ptr+i*nmem, nmem);		
	}
	for (; j <= high; ++j) {
		memcpy(dummy+(k++)*nmem, ptr+j*nmem, nmem);
	}		
	memcpy(ptr+low*nmem, dummy, (high-low+1)*nmem);
}

void alg_merge_sort(void *base, size_t nmem, size_t nsize,
					int (*cmp)(void *, void *)) {
	char *ext_storage = NULL;
	if (nsize > 0) {
		ext_storage = (char *)malloc(nmem*nsize);
		merge_sort(base, nmem, 0, nsize-1, cmp, ext_storage);
		free(ext_storage);
	}
}

static size_t partion(void *base, size_t nmem, size_t l, size_t r,
					  int (*cmp)(void *, void *), void *ext_storage) {
	char *ptr = base;
	memcpy(ext_storage, ptr+r*nmem, nmem);
	
	while (l < r) {
		while (l < r && cmp(ptr+l*nmem, ext_storage) <= 0)
			++l;
		if (l < r)
			memcpy(ptr+r*nmem, ptr+l*nmem, nmem);

		while (l < r && cmp(ptr+r*nmem, ext_storage) > 0)
			--r;
		if (l < r)
			memcpy(ptr+l*nmem, ptr+r*nmem, nmem);
	}

	memcpy(ptr+l*nmem, ext_storage, nmem);
	return l;
}

static void quick_sort(void *base, size_t nmem, size_t l, size_t r,
					   int (*cmp)(void *, void *), void *ext_storage) {
	if (l >= r)
		return;
	
	size_t m = partion(base, nmem, l, r, cmp, ext_storage);
	if (m > 0)
		quick_sort(base, nmem, l, m-1, cmp, ext_storage);
	quick_sort(base, nmem, m+1, r, cmp, ext_storage);
}

void alg_quick_sort(void *base, size_t nmem, size_t nsize,
					int (*cmp)(void *, void *)) {
	char *ext_storage = NULL;
	if (nsize > 0) {
		ext_storage = (char *)malloc(nmem);
		quick_sort(base, nmem, 0, nsize-1, cmp, ext_storage);
		free(ext_storage);
	}	
}

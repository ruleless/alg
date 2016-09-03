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
					   int (*cmp)(void *, void *)) {
	if (low >= high)
		return;

	size_t mid = (low+high)>>1;
	merge_sort(base, nmem, low, mid, cmp);
	merge_sort(base, nmem, mid+1, high, cmp);

	char *ptr = (char *)base;
	char *dummy = (char *)malloc((high-low+1)*nmem);
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
	free(dummy);
}

void alg_merge_sort(void *base, size_t nmem, size_t nsize,
					int (*cmp)(void *, void *)) {
	if (nsize > 0)
		merge_sort(base, nmem, 0, nsize-1, cmp);
}   				

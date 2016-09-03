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

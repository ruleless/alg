#include "bitset.h"

struct bitset {
	uint *bit_array;
	uint array_size;
};

static int bitset_extend(bitset *b, uint sz) {
	if (sz <= b->array_size)
		return 1;

	uint cur = b->array_size;
	uint new_sz = sz;
	if (sz < (b->array_size << 1) && b->array_size < 65536) {
		new_sz = b->array_size << 1;
	}
	new_sz = max(new_sz, 256);

	if (NULL == b->bit_array)		
		b->bit_array = malloc(new_sz*sizeof(uint));
	else
		b->bit_array = realloc(b->bit_array, new_sz*sizeof(uint));
	if (NULL == b->bit_array)
		return 0;

	b->array_size = new_sz;
	memset(b->bit_array+cur, sizeof(uint), new_sz-cur);
	return 1;
}

bitset* bitset_new() {
	bitset *b = (bitset *)malloc(sizeof(bitset));
	if (NULL == b) {
		return NULL;
	}

	b->bit_array = NULL;
	b->array_size = 0;
	return b;
}

void bitset_destroy(bitset *b) {
	if (b->bit_array)
		free(b->bit_array);
	free(b);
}

int bitset_set(bitset *b, uint n) {
	uint i = n>>5, bit = n&31;

	if (i+1 > b->array_size) {
		if (!bitset_extend(b, i+1)) {
			return 0;
		}
	}

	b->bit_array[i] |= (1<<bit);
	return 1;
}

void bitset_clear(bitset *b, uint n) {
	uint i = n>>5, bit = n&31;

	if (i < b->array_size) {
		b->bit_array[i] &= ~(1<<bit);
	}
}

int bitset_exists(bitset *b, uint n) {
	uint i = n>>5, bit = n&31;
	
	if (i < b->array_size) {
		return (b->bit_array[i] & (1<<bit)) != 0;
	}
	return 0;
}

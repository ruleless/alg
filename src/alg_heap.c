#include "alg_heap.h"
#include "alg_base.h"

#define HEAP_PARENT(n) ((n-1)>>1)
#define HEAP_LEFT(n)   ((n<<1)+1)
#define HEAP_RIGHT(n)  ((n<<1)+1)

static void
heap_downward(void *base, size_t nmem, size_t heap_size, size_t n,
			  int (*cmp)(void *, void *)) {
	char *ptr = (char *)base;
	size_t largest = n;
	size_t left = HEAP_LEFT(n), right = HEAP_RIGHT(n);
	
	if (left < heap_size && cmp(ptr+left*nmem, ptr+largest*nmem) > 0) {
		largest = left;
	}
	if (right < heap_size && cmp(ptr+right*nmem, ptr+largest*nmem) > 0) {
		largest = right;
	}	
	if (largest != n) {
		alg_swap(ptr+largest*nmem, ptr+n*nmem, nmem);
		heap_downward(base, nmem, heap_size, largest, cmp);
	}
}

static void
heap_upward(void *base, size_t nmem, size_t heap_size, size_t n,
			  int (*cmp)(void *, void *)) {
	
}

void alg_make_heap(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *)) {
	
}

void alg_push_heap(void *base, size_t nmem, size_t nsize,
				   int (*cmp)(void *, void *)) {
	
}

void alg_pop_heap(void *base, size_t nmem, size_t nsize,
				  int (*cmp)(void *, void *)) {
	
}

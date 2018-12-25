#include "alg_heap.h"
#include "alg_base.h"

#define HEAP_PARENT(n) ((n - 1) >> 1)
#define HEAP_LEFT(n)   ((n << 1) + 1)
#define HEAP_RIGHT(n)  ((n << 1) + 2)

static void
heap_downward(void *base, size_t nmem, size_t heap_size, size_t n,
              int (*cmp)(void *, void *))
{
    char *ptr = (char *)base;
    size_t largest = n;
    size_t left = HEAP_LEFT(n), right = HEAP_RIGHT(n);

    if (left < heap_size && cmp(ptr + left*nmem, ptr + largest*nmem) > 0) {
        largest = left;
    }
    if (right < heap_size && cmp(ptr + right*nmem, ptr + largest*nmem) > 0) {
        largest = right;
    }
    if (largest != n) {
        alg_swap(ptr + largest*nmem, ptr + n*nmem, nmem);
        heap_downward(base, nmem, heap_size, largest, cmp);
    }
}

static void
heap_upward(void *base, size_t nmem, size_t heap_size, size_t n,
            int (*cmp)(void *, void *))
{
    char *ptr = (char *)base;
    size_t parent;

    while (n != 0) {
        parent = HEAP_PARENT(n);
        if (cmp(ptr + parent*nmem, ptr+n*nmem) > 0) {
            break;
        }

        alg_swap(ptr + n*nmem, ptr + parent*nmem, nmem);
        n = parent;
    }
}

void
alg_make_heap(void *base, size_t nmem, size_t nsize,
              int (*cmp)(void *, void *))
{
    if (nsize > 1) {
        size_t n = (nsize>>1) - 1;

        do {
            heap_downward(base, nmem, nsize, n, cmp);
        } while (n--);
    }
}

void
alg_push_heap(void *base, size_t nmem, size_t nsize,
              int (*cmp)(void *, void *))
{
    if (nsize > 1) {
        heap_upward(base, nmem, nsize, nsize-1, cmp);
    }
}

void
alg_pop_heap(void *base, size_t nmem, size_t nsize,
             int (*cmp)(void *, void *))
{
    if (nsize > 1) {
        char *ptr = base;

        alg_swap(ptr, ptr + nmem*(nsize-1), nmem);
        heap_downward(base, nmem, nsize-1, 0, cmp);
    }
}

void
alg_heap_sort(void *base, size_t nmem, size_t nsize,
              int (*cmp)(void *, void *))
{
    size_t heap_size = nsize;
    char *ptr = (char *)base;

    alg_make_heap(base, nmem, nsize, cmp);
    while (heap_size > 1) {
        alg_swap(ptr, ptr + (heap_size-1)*nmem, nmem);
        heap_downward(base, nmem, --heap_size, 0, cmp);
    }
}

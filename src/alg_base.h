#ifndef __ALG_BASE_H__
#define __ALG_BASE_H__

#include "alg_common.h"

#define ROUND_SHIFT   3
#define ROUND_SIZE    (((size_t)1) << ROUND_SHIFT)
#define ROUND_UP(n)   (((n) + ROUND_SIZE - 1) & ~(ROUND_SIZE - 1))

#define MAX_MEMSIZE 64

#ifdef __cplusplus
extern "C" {
#endif

static inline void
alg_swap(void *a, void *b, size_t nmem)
{
    void *tmp = alloca(nmem); assert(tmp);
    memcpy(tmp, a, nmem);
    memcpy(a, b, nmem);
    memcpy(b, tmp, nmem);
}

#ifdef __cplusplus
}
#endif

#endif /* __ALG_BASE_H__ */

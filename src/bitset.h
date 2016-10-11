#ifndef __ALG_BITSET_H__
#define __ALG_BITSET_H__

#include "alg_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct bitset;
typedef struct bitset bitset;

bitset* bitset_new();
void bitset_destroy(bitset *b);

int bitset_set(bitset *b, uint n);
void bitset_clear(bitset *b, uint n);

int bitset_exists(bitset *b, uint n);

#ifdef __cplusplus
}
#endif

#endif // __ALG_BITSET_H__

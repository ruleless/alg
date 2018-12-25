#ifndef __ALG_BITSET_H__
#define __ALG_BITSET_H__

#ifndef MAX
# define MAX(a, b) ((b) > (a) ? (b) : (a))
#endif
#ifndef MIN
# define MIN(a, b) ((b) < (a) ? (b) : (a))
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct bitset;
typedef struct bitset bitset;

bitset *bitset_new();
void bitset_destroy(bitset *b);

int bitset_set(bitset *b, uint n);
void bitset_clear(bitset *b, uint n);

int bitset_exists(bitset *b, uint n);

#ifdef __cplusplus
}
#endif

#endif // __ALG_BITSET_H__

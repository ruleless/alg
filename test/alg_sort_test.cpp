#include "src/alg_sort.h"
#include "src/bitset.h"
#include "src/alg_heap.h"
#include "src/alg_profiler.h"
#include <gtest/gtest.h>

struct SortNode {
    int key;
    int id;
};

class alg_sort_test : public testing::Test
{
  protected:
    void SetUp()
    {
        ALG_PROFILER_START;

        mBitset = bitset_new();

#if 0
        srand(time(NULL));
        mArraySz = 0;
        while (mArraySz <= 0) {
            mArraySz = rand()%65535;
        }
#else
        mArraySz = 10000;
#endif

        mArray = (SortNode *)malloc(mArraySz * sizeof(SortNode));
        for (int i = 0; i < mArraySz; ++i) {
            bitset_set(mBitset, i);
            mArray[i].key = rand();
            mArray[i].id = i;
        }

        ALG_PROFILER_END;
    }

    SortNode *mArray;
    int mArraySz;
    bitset *mBitset;
};

static int cmp_int(void *a, void *b)
{
    SortNode *sa = (SortNode *)a, *sb = (SortNode *)b;
    return sa->key - sb->key;
}

TEST_F(alg_sort_test, inserction_sort)
{
    ALG_PROFILER_START;
    alg_inserction_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i) {
        EXPECT_TRUE(mArray[i].key <= mArray[i+1].key);
        EXPECT_TRUE(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

TEST_F(alg_sort_test, merge_sort)
{
    ALG_PROFILER_START;
    alg_merge_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i) {
        EXPECT_TRUE(mArray[i].key <= mArray[i+1].key);
        EXPECT_TRUE(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

TEST_F(alg_sort_test, quick_sort)
{
    ALG_PROFILER_START;
    alg_quick_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i) {
        EXPECT_TRUE(mArray[i].key <= mArray[i+1].key);
        EXPECT_TRUE(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

TEST_F(alg_sort_test, heap_sort)
{
    ALG_PROFILER_START;
    alg_heap_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i) {
        EXPECT_TRUE(mArray[i].key <= mArray[i+1].key);
        EXPECT_TRUE(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

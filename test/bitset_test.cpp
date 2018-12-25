#include "src/bitset.h"
#include "src/alg_profiler.h"
#include <gtest/gtest.h>

TEST(bitset_test, test)
{
    bitset *b = bitset_new();
    EXPECT_TRUE(b != NULL);

    unsigned int maxn = 1000000;

    ALG_PROFILER_START;
    for (unsigned int i = 0; i < maxn; ++i) {
        ALG_PROFILER_START;

        bitset_set(b, i);
        EXPECT_TRUE(bitset_exists(b, i));

        ALG_PROFILER_END;
    }
    ALG_PROFILER_END;

    ALG_PROFILER_START;
    for (unsigned int i = 0; i < maxn; ++i) {
        bitset_clear(b, i);
        EXPECT_TRUE(!bitset_exists(b, i));
    }
    ALG_PROFILER_END;

    ALG_PROFILER_OUTPUT;
}

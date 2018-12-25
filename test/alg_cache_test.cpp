#include "src/alg_cache.h"
#include <gtest/gtest.h>

static const char *s_test_str[] = {
    "test1",
    "test23",
    "fkadsfkjsdakfjasdjfkasjrieuwqrnkvnakfhijlkf5a4s5f74asf42asd1fasdf",
    "jfakdsiofruewiorewnckjdkfjasfjdnafkmnmnkjujwiue9q  k safjkdsajfkmmjjlklk",
    "中文测试中文测试中文测试中文测试中文测试中文测试中文测试中文测试",
};

static int s_test_index = 0;

int test_cache_handler(alg_cache_t *c, const void *data, size_t size)
{
    EXPECT_EQ(memcmp(data, s_test_str[s_test_index++], size), 0);
    return 1;
}

void *cache_alloc(void *, size_t sz)
{
    return malloc(sz);
}

void cache_dealloc(void *, void *p)
{
    free(p);
}

TEST(alg_cache_test, test_cache)
{
    alg_cache_t *c = alg_cache_create(test_cache_handler, cache_alloc, cache_dealloc, NULL);

    c->memcache_maxsize = 10;
    s_test_index = 0;

    for (int i = 0; i < (int)sizeof(s_test_str)/(int)sizeof(const char *); ++i) {
        alg_cache_push(c, s_test_str[i], strlen(s_test_str[i]));
    }

    alg_cache_flushall(c);

    alg_cache_destroy(c);
}

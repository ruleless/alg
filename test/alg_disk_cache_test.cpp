#include "src/alg_disk_cache.h"
#include <gtest/gtest.h>

TEST(alg_disk_cache, disk_cache)
{
    const char *strs[] = {
        "test1",
        "test23",
        "fkadsfkjsdakfjasdjfkasjrieuwqrnkvnakfhijlkf5a4s5f74asf42asd1fasdf",
        "jfakdsiofruewiorewnckjdkfjasfjdnafkmnmnkjujwiue9q  k safjkdsajfkmmjjlklk",
    };

    alg_disk_cache_t dcache;
    dcache.file = NULL;
    for (int i = 0; i < (int)sizeof(strs)/(int)sizeof(const char *); ++i) {
        alg_disk_cache_write(&dcache, strs[i], strlen(strs[i]));
    }

    char *ptr = NULL;
    int i = 0;
    ssize_t sz = 0;
    while ((sz = alg_disk_cache_peeksize(&dcache)) > 0) {
        ptr = (char *)malloc(sz);
        alg_disk_cache_read(&dcache, ptr, sz);
        EXPECT_EQ(memcmp(ptr, strs[i++], sz), 0);
    }
}


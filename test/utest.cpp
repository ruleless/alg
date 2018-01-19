#include "utest.h"

#include "../src/alg_sort.h"
#include "../src/alg_heap.h"
#include "../src/list.h"
#include "../src/bitset.h"
#include "../src/alg_cache.h"
#include "../src/alg_string.h"
#include "../src/alg_profiler.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UTest);

//--------------------------------------------------------------------------
UTest::UTest()
{}

UTest::~UTest()
{}

void UTest::setUp()
{
    ALG_PROFILER_START;

    mBitset = bitset_new();

#if 0
    srand(time(NULL));
    mArraySz = 0;
    while (mArraySz <= 0)
        mArraySz = rand()%65535;
#else
    mArraySz = 10000;
#endif

    mArray = (SortNode *)malloc(mArraySz*sizeof(SortNode));
    for (int i = 0; i < mArraySz; ++i)
    {
        bitset_set(mBitset, i);
        mArray[i].key = rand();
        mArray[i].id = i;
    }

    ALG_PROFILER_END;
}

void UTest::tearDown()
{
    ALG_PROFILER_START;

    bitset_destroy(mBitset);

    free(mArray);
    mArray = NULL;
    mArraySz = 0;

    ALG_PROFILER_END;
}

static int cmp_int(void *a, void *b)
{
    SortNode *sa = (SortNode *)a, *sb = (SortNode *)b;
    return sa->key - sb->key;
}
void UTest::inserction_sort()
{
    ALG_PROFILER_START;
    alg_inserction_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i)
    {
        CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
        CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

void UTest::merge_sort()
{
    ALG_PROFILER_START;
    alg_merge_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i)
    {
        CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
        CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

void UTest::quick_sort()
{
    ALG_PROFILER_START;
    alg_quick_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i)
    {
        CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
        CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

void UTest::heap_sort()
{
    ALG_PROFILER_START;
    alg_heap_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
    ALG_PROFILER_END;

    for (int i = 0; i < mArraySz-1; ++i)
    {
        CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
        CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
        bitset_clear(mBitset, mArray[i].id);
    }
}

struct LNode
{
    int a;
    struct list_head list;
};
static int array_to_test_list[] = {
    1, 2, 3, 31, 49, 34, 5, 9, 0, 1, 2,
    11, 21, 31, 313, 494, 343, 54, 95, 120, 19, 20,
    11, 22, 43, 931, 949, 134, 95, 89, 890, 71, 92,
    1, 2, 3, 31, 49, 34, 5, 9, 0, 1, 2,
    11, 21, 31, 313, 494, 343, 54, 95, 120, 19, 20,
    11, 22, 43, 931, 949, 134, 95, 89, 890, 71, 92,
    1, 2, 3, 31, 49, 34, 5, 9, 0, 1, 2,
    11, 21, 31, 313, 494, 343, 54, 95, 120, 19, 20,
    11, 22, 43, 931, 949, 134, 95, 89, 890, 71, 92,
    1, 2, 3, 31, 49, 34, 5, 9, 0, 1, 2,
    11, 21, 31, 313, 494, 343, 54, 95, 120, 19, 20,
    11, 22, 43, 931, 949, 134, 95, 89, 890, 71, 92,
    1, 2, 3, 31, 49, 34, 5, 9, 0, 1, 2,
    11, 21, 31, 313, 494, 343, 54, 95, 120, 19, 20,
    11, 22, 43, 931, 949, 134, 95, 89, 890, 71, 92,
};
void UTest::test_list()
{
    // test insert
    struct list_head l1 = LIST_HEAD_INIT(l1);
    int i = 0;
    for (i = 0; i < (int)sizeof(array_to_test_list)/(int)sizeof(int); i++)
    {
        LNode *n = new LNode;
        n->a = array_to_test_list[i];
        INIT_LIST_HEAD(&n->list);
        list_add(&n->list, &l1);
    }

    struct list_head l2 = LIST_HEAD_INIT(l2);
    for (i = 0; i < (int)sizeof(array_to_test_list)/(int)sizeof(int); i++)
    {
        LNode *n = new LNode;
        n->a = array_to_test_list[i];
        INIT_LIST_HEAD(&n->list);
        list_add_tail(&n->list, &l2);
    }

    struct list_head *pos, *next;
    i = sizeof(array_to_test_list)/sizeof(int)-1;
    list_for_each_safe(pos, next, &l1)
    {
        struct LNode *n = list_entry(pos, LNode, list);
        CPPUNIT_ASSERT(i >= 0 && n->a == array_to_test_list[i--]);
    }
    CPPUNIT_ASSERT(i == -1);

    i = 0;
    list_for_each_safe(pos, next, &l2)
    {
        struct LNode *n = list_entry(pos, LNode, list);
        CPPUNIT_ASSERT(n->a == array_to_test_list[i++]);
    }
    CPPUNIT_ASSERT(i == sizeof(array_to_test_list)/sizeof(int));

    // test delete
    i = 0;
    list_for_each_prev_safe(pos, next, &l1)
    {
        struct LNode *n = list_entry(pos, LNode, list);
        CPPUNIT_ASSERT(n->a == array_to_test_list[i++]);
        list_del(&n->list);
        free(n);
    }
    CPPUNIT_ASSERT(list_empty(&l1));

    i = sizeof(array_to_test_list)/sizeof(int)-1;
    list_for_each_prev_safe(pos, next, &l2)
    {
        struct LNode *n = list_entry(pos, LNode, list);
        CPPUNIT_ASSERT(n->a == array_to_test_list[i--]);
        list_del(&n->list);
        free(n);
    }
    CPPUNIT_ASSERT(list_empty(&l2));
}

void UTest::test_bitset()
{
    bitset *b = bitset_new();
    uint maxn = 1000000;

    ALG_PROFILER_START;
    for (uint i = 0; i < maxn; ++i)
    {
        ALG_PROFILER_START;
        bitset_set(b, i);
        CPPUNIT_ASSERT(bitset_exists(b, i));
        ALG_PROFILER_END;
    }
    ALG_PROFILER_END;

    ALG_PROFILER_START;
    for (uint i = 0; i < maxn; ++i)
    {
        bitset_clear(b, i);
        CPPUNIT_ASSERT(!bitset_exists(b, i));
    }
    ALG_PROFILER_END;
}

void UTest::test_dcache()
{
    const char *strs[] = {
        "test1",
        "test23",
        "fkadsfkjsdakfjasdjfkasjrieuwqrnkvnakfhijlkf5a4s5f74asf42asd1fasdf",
        "jfakdsiofruewiorewnckjdkfjasfjdnafkmnmnkjujwiue9q  k safjkdsajfkmmjjlklk",
    };

    alg_disk_cache_t dcache;
    dcache.file = NULL;
    for (int i = 0; i < (int)sizeof(strs)/(int)sizeof(const char *); ++i)
    {
        alg_disk_cache_write(&dcache, strs[i], strlen(strs[i]));
    }

    char *ptr = NULL;
    int i = 0;
    ssize_t sz = 0;
    while ((sz = alg_disk_cache_peeksize(&dcache)) > 0)
    {
        ptr = (char *)malloc(sz);
        alg_disk_cache_read(&dcache, ptr, sz);
        CPPUNIT_ASSERT(memcmp(ptr, strs[i++], sz) == 0);
    }
}

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
    CPPUNIT_ASSERT(memcmp(data, s_test_str[s_test_index++], size) == 0);
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

void UTest::test_cache()
{
    alg_cache_t *c = alg_cache_create(test_cache_handler, cache_alloc, cache_dealloc, NULL);

    c->memcache_maxsize = 10;
    s_test_index = 0;

    for (int i = 0; i < (int)sizeof(s_test_str)/(int)sizeof(const char *); ++i)
    {
        alg_cache_push(c, s_test_str[i], strlen(s_test_str[i]));
    }

    alg_cache_flushall(c);

    alg_cache_destroy(c);
}

struct ReplaceNode
{
    const char *source;
    const char *substr;
    const char *newstr;
    const char *target;
};
void UTest::test_replace_str()
{
    ReplaceNode TESTING_CASE[] = {
        {"you are a fuck!", "you are", "he is", "he is a fuck!"},
        {"you are a fuck!", "you", "", " are a fuck!"},
        {
            "a random string should be replaced!",
            "r", "bbb",
            "a bbbandom stbbbing should be bbbeplaced!",
        },
        {NULL, NULL, NULL, NULL},
    };

    ReplaceNode *n;
    char buf[256];

    for (int i = 0; TESTING_CASE[i].source; i++)
    {
        n = &TESTING_CASE[i];

        strncpy(buf, n->source, sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';

        alg_replace(buf, sizeof(buf), n->substr, n->newstr);

        int cmpret = strcmp(buf, n->target);
        if (cmpret != 0)
        {
            printf("src:%s\nbeing:%s", n->source, buf);
        }

        CPPUNIT_ASSERT(cmpret == 0);
    }

    strncpy(buf, "any word", sizeof(buf)-1);
    CPPUNIT_ASSERT(alg_replace(buf, sizeof(buf), "tttt", "") == buf);
}

struct WildcardMatchTestNode
{
    const char *str;
    const char *patt;
    BOOL ret;
};
void UTest::test_wildcard_match()
{
    WildcardMatchTestNode TESTING_CASE[] = {
        {"you are a fuck", "*", TRUE},
        {"you are a fuck", "you*", TRUE},
        {"you are a fuck", "you are a fuck", TRUE},
        {"you are a fuck", "you are ? fuck", TRUE},
        {"you are a fuck", "you are ? fuck?", FALSE},
        {"you are a fuck", "you are*fuck", TRUE},
        {NULL, NULL, FALSE},
    };

    for (int i = 0; TESTING_CASE[i].str; i++)
    {
        WildcardMatchTestNode *n = &TESTING_CASE[i];
        BOOL ret = alg_wildcard_match(n->str, n->patt);

        if (ret != n->ret)
        {
            printf("unpassed case!\nstr:%s\npattern:%s\n",
                   n->str, n->patt);
        }

        CPPUNIT_ASSERT(ret == n->ret);
    }
}
//--------------------------------------------------------------------------


int main(int argc, char *argv[])
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    runner.run();
    ALG_PROFILER_OUTPUT;
    exit(0);
}


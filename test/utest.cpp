#include "utest.h"

#include "../src/alg_sort.h"
#include "../src/alg_heap.h"
#include "../src/list.h"
#include "../src/bitset.h"

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
	mBitset = bitset_new();
	
	srand(time(NULL));
	mArraySz = 0;	
	while (mArraySz <= 0)
		mArraySz = rand()%65535;

	mArray = (SortNode *)malloc(mArraySz*sizeof(SortNode));
	for (int i = 0; i < mArraySz; ++i)
	{				
		bitset_set(mBitset, i);
		mArray[i].key = rand();
		mArray[i].id = i;
	}
}
	
void UTest::tearDown()
{
	bitset_destroy(mBitset);
	
	free(mArray);
	mArray = NULL;
	mArraySz = 0;
}

static int cmp_int(void *a, void *b)
{
	SortNode *sa = (SortNode *)a, *sb = (SortNode *)b;	
	return sa->key - sb->key;
}
void UTest::inserction_sort()
{	
	alg_inserction_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
	for (int i = 0; i < mArraySz-1; ++i)
	{
		CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
		CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
		bitset_clear(mBitset, mArray[i].id);
	}
}

void UTest::merge_sort()
{	
	alg_merge_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
	for (int i = 0; i < mArraySz-1; ++i)
	{
		CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
		CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
		bitset_clear(mBitset, mArray[i].id);
	}
}

void UTest::quick_sort()
{	
	alg_quick_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
	for (int i = 0; i < mArraySz-1; ++i)
	{
		CPPUNIT_ASSERT(mArray[i].key<=mArray[i+1].key);
		CPPUNIT_ASSERT(bitset_exists(mBitset, mArray[i].id));
		bitset_clear(mBitset, mArray[i].id);
	}
}

void UTest::heap_sort()
{
	alg_heap_sort(mArray, sizeof(SortNode), mArraySz, cmp_int);
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
	for (i = 0; i < sizeof(array_to_test_list)/sizeof(int); i++)
	{
		LNode *n = new LNode;
		n->a = array_to_test_list[i];
		INIT_LIST_HEAD(&n->list);
		list_add(&n->list, &l1);
	}

	struct list_head l2 = LIST_HEAD_INIT(l2);
	for (i = 0; i < sizeof(array_to_test_list)/sizeof(int); i++)
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
	for (int i = 0; i < maxn; ++i)
	{
		bitset_set(b, i);
		CPPUNIT_ASSERT(bitset_exists(b, i));
	}
	
	for (int i = 0; i < maxn; ++i)
	{
		bitset_clear(b, i);
		CPPUNIT_ASSERT(!bitset_exists(b, i));
	}
}
//--------------------------------------------------------------------------


int main(int argc, char *argv[])
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	runner.run();
	exit(0);
}


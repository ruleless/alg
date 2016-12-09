#ifndef __UTEST_H__
#define __UTEST_H__

#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "../src/bitset.h"

struct SortNode
{
	int key;
	int id;	
};

class UTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UTest);
	CPPUNIT_TEST(inserction_sort);
	CPPUNIT_TEST(merge_sort);
	CPPUNIT_TEST(quick_sort);
	CPPUNIT_TEST(heap_sort);
	CPPUNIT_TEST(test_list);
	CPPUNIT_TEST(test_bitset);	
	CPPUNIT_TEST(test_dcache);
	CPPUNIT_TEST(test_cache);	
	CPPUNIT_TEST_SUITE_END();
	
  public:
    UTest();
    virtual ~UTest();
	
	virtual void setUp();
	
	virtual void tearDown();

	void inserction_sort();
	void merge_sort();
	void quick_sort();
	void heap_sort();

	void test_list();

	void test_bitset();

	void test_dcache();
	void test_cache();

  private:		
	SortNode *mArray;
	int mArraySz;
	bitset *mBitset;
};

#endif // __UTEST_H__

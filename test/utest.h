#ifndef __UTEST_H__
#define __UTEST_H__

#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

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
	CPPUNIT_TEST(test_list);
	CPPUNIT_TEST(test_bitset);
	CPPUNIT_TEST_SUITE_END();
	
  public:
    UTest();
    virtual ~UTest();
	
	virtual void setUp();
	
	virtual void tearDown();

	void inserction_sort();
	void merge_sort();
	void quick_sort();

	void test_list();

	void test_bitset();

  private:		
	SortNode *mArray;
	int mArraySz;
};

#endif // __UTEST_H__

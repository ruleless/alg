#ifndef __UTEST_H__
#define __UTEST_H__

#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

class UTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UTest);
	CPPUNIT_TEST(inserction_sort);
	CPPUNIT_TEST_SUITE_END();
  public:
    UTest();
    virtual ~UTest();
	
	virtual void setUp();
	
	virtual void tearDown();

	void inserction_sort();
};

#endif // __UTEST_H__

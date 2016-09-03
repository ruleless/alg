#include "utest.h"

#include "../src/alg_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UTest);

UTest::UTest()
{}

UTest::~UTest()
{}
	
void UTest::setUp()
{}
	
void UTest::tearDown()
{}

static int cmp_int(void *a, void *b)
{
	return *((int *)a)-*((int *)b);
}
void UTest::inserction_sort()
{
	int a[] = {10, 3, 6, 1, 5, 9, 9, 10, -9, 10, 432, 1, 19};
	puts("before insertcion sort:");
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
	puts("");
	
	puts("after insertcion sort:");
	alg_inserction_sort(a, sizeof(int), sizeof(a)/sizeof(int), cmp_int);
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
	{
		printf("%d ", a[i]);
	}
	puts("");
}

int main(int argc, char *argv[])
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	runner.run();
	exit(0);
}


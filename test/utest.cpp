#include "utest.h"

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

void UTest::inserction_sort()
{}

int main(int argc, char *argv[])
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	runner.run();
	exit(0);
}


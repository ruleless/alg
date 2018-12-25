#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    fprintf(stdout, "unit test for %s ...\n", argv[0]);
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

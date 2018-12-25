#include "src/alg_thread_env.h"
#include <gtest/gtest.h>

TEST(alg_thread_env, set_thread_env)
{
    char tid[16];

    snprintf(tid, sizeof(tid), "%ld", (long)pthread_self());
    set_thread_env("tid", tid);

    EXPECT_STREQ(get_thread_env("tid"), tid);
}

#include "src/alg_string.h"
#include <gtest/gtest.h>

typedef struct {
    const char *source;
    const char *substr;
    const char *newstr;
    const char *target;
} replace_test_node_t;

TEST(alg_string, replace)
{
    replace_test_node_t TESTING_CASE[] = {
        {"you are a fuck!", "you are", "he is", "he is a fuck!"},
        {"you are a fuck!", "you", "", " are a fuck!"},
        {
            "a random string should be replaced!",
            "r", "bbb",
            "a bbbandom stbbbing should be bbbeplaced!",
        },

        {NULL, NULL, NULL, NULL},
    };

    replace_test_node_t *n;
    char buf[256];

    for (int i = 0; TESTING_CASE[i].source; i++) {
        n = &TESTING_CASE[i];

        strncpy(buf, n->source, sizeof(buf) - 1);
        buf[sizeof(buf)-1] = '\0';

        alg_replace(buf, sizeof(buf), n->substr, n->newstr);

        int cmpret = strcmp(buf, n->target);
        if (cmpret != 0) {
            printf("src:%s\nbeing:%s", n->source, buf);
        }

        EXPECT_EQ(cmpret, 0);
    }

    strncpy(buf, "any word", sizeof(buf) - 1);
    EXPECT_STREQ(alg_replace(buf, sizeof(buf), "tttt", ""), buf);
}

typedef struct
{
    const char *str;
    const char *patt;
    BOOL ret;
} wildcard_match_test_node_t;

TEST(alg_string, wildcard_match)
{
    wildcard_match_test_node_t TESTING_CASE[] = {
        {"you are a fuck", "*", TRUE},
        {"you are a fuck", "you*", TRUE},
        {"you are a fuck", "you are a fuck", TRUE},
        {"you are a fuck", "you are ? fuck", TRUE},
        {"you are a fuck", "you are ? fuck?", FALSE},
        {"you are a fuck", "you are*fuck", TRUE},

        {NULL, NULL, FALSE},
    };

    for (int i = 0; TESTING_CASE[i].str; i++) {
        wildcard_match_test_node_t *n = &TESTING_CASE[i];
        BOOL ret = alg_wildcard_match(n->str, n->patt);

        if (ret != n->ret) {
            fprintf(stderr, "unpassed case!\nstr:%s\npattern:%s\n",
                    n->str, n->patt);
        }

        EXPECT_EQ(ret, n->ret);
    }
}

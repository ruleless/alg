#include "src/list.h"
#include <gtest/gtest.h>

struct LNode {
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

TEST(list_test, test)
{
    // test insert
    struct list_head l1 = LIST_HEAD_INIT(l1);
    int i = 0;
    for (i = 0; i < (int)sizeof(array_to_test_list)/(int)sizeof(int); i++) {
        LNode *n = new LNode;
        n->a = array_to_test_list[i];
        INIT_LIST_HEAD(&n->list);
        list_add(&n->list, &l1);
    }

    struct list_head l2 = LIST_HEAD_INIT(l2);
    for (i = 0; i < (int)sizeof(array_to_test_list)/(int)sizeof(int); i++) {
        LNode *n = new LNode;
        n->a = array_to_test_list[i];
        INIT_LIST_HEAD(&n->list);
        list_add_tail(&n->list, &l2);
    }

    struct list_head *pos, *next;
    i = sizeof(array_to_test_list)/sizeof(int)-1;
    list_for_each_safe(pos, next, &l1) {
        struct LNode *n = list_entry(pos, LNode, list);
        EXPECT_TRUE(i >= 0 && n->a == array_to_test_list[i--]);
    }
    EXPECT_EQ(i, -1);

    i = 0;
    list_for_each_safe(pos, next, &l2) {
        struct LNode *n = list_entry(pos, LNode, list);
        EXPECT_TRUE(n->a == array_to_test_list[i++]);
    }
    EXPECT_EQ(i, sizeof(array_to_test_list)/sizeof(int));

    // test delete
    i = 0;
    list_for_each_prev_safe(pos, next, &l1) {
        struct LNode *n = list_entry(pos, LNode, list);
        EXPECT_EQ(n->a, array_to_test_list[i++]);
        list_del(&n->list);
        free(n);
    }
    EXPECT_TRUE(list_empty(&l1) != 0);

    i = sizeof(array_to_test_list)/sizeof(int)-1;
    list_for_each_prev_safe(pos, next, &l2) {
        struct LNode *n = list_entry(pos, LNode, list);
        EXPECT_EQ(n->a, array_to_test_list[i--]);
        list_del(&n->list);
        free(n);
    }
    EXPECT_TRUE(list_empty(&l2));
}

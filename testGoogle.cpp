#include <gtest/gtest.h>
#include "dllist.h"

TEST(dllistTest, empty_string_list)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.empty(), true);
}

TEST(dllistTest, empty_own_class_list)
{
    struct point {unsigned int x; unsigned int y;};
    dllist<point> lst;
    ASSERT_EQ(lst.empty(), true);
}


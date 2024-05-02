#include <gtest/gtest.h>
#include "dllist.h"

TEST(dllist, create_default_empty_string_list)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.empty(), true);
}

TEST(dllist, create_default_empty_own_class)
{
    struct point {unsigned int x; unsigned int y;};
    dllist<point> lst;
    ASSERT_EQ(lst.empty(), true);
}
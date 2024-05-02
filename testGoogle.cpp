#include <gtest/gtest.h>
#include "dllist.h"


TEST(dllistTest, push_front_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    ASSERT_EQ(*lst.begin(), "urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(*lst.begin(), "konsternacja");
}

TEST(dllistTest, forward_iteration_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.push_front("gaz");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "gaz");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(it != lst.end(), false);
}

TEST(dllistTest, begin_end_empty_list)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.begin() != lst.end(), false);
}

TEST(dllistTest, empty_list)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.empty(), true);
}

TEST(dllistTest, empty_not)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    ASSERT_EQ(lst.empty(), false);
}

TEST(dllistTest, pop_front_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.push_front("gaz");
    ASSERT_EQ(lst.pop_front(), "gaz");
    ASSERT_EQ(lst.pop_front(), "konsternacja");
    ASSERT_EQ(lst.pop_front(), "urobek");
    ASSERT_EQ(lst.empty(), true);
}

TEST(dllistTest, clear_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.clear();
    ASSERT_EQ(lst.empty(), true);
}
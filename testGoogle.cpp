#include <gtest/gtest.h>
#include "dllist.h"


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

TEST(dllistTest, front_non_const)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(lst.front(), "konsternacja");
    lst.front() = "konkurencja";
    ASSERT_EQ(lst.front(), "konkurencja");
}

TEST(dllistTest, front_and_clear)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(lst.front(), "konsternacja");
    lst.clear();
    EXPECT_THROW(lst.front(), std::runtime_error);
}

TEST(dllistTest, push_front_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    ASSERT_EQ(*lst.begin(), "urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(*lst.begin(), "konsternacja");
}

TEST(dllistTest, push_front_own_class)
{
    struct point {int x; int y;};
    dllist<point> lst;
    point pnt;
    pnt.x = 1;
    pnt.y = 2;
    lst.push_front(pnt);
    ASSERT_EQ((*lst.begin()).x, 1);
    ASSERT_EQ((*lst.begin()).y, 2);
}

TEST(dllistTest, push_back_typical)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    ASSERT_EQ(lst.empty(), false);
    ASSERT_EQ(*lst.begin(), "urobek");
}

TEST(dllistTest, push_front_back)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    ASSERT_EQ(*lst.begin(), "urobek");
    lst.push_back("konsternacja");
    lst.push_front("kowariancja");
    lst.push_back("katastrofalny");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "katastrofalny");
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
    lst.push_back("konkurencja");
    lst.clear();
    ASSERT_EQ(lst.empty(), true);
    ASSERT_EQ(lst.begin() != lst.end(), false);
}

TEST(dllistTest, clear_and_push)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.clear();
    ASSERT_EQ(lst.empty(), true);
    ASSERT_EQ(lst.begin() != nullptr, false);
    lst.push_front("urobek2");
    lst.push_front("konsternacja2");
    lst.push_back("konkurencja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "konsternacja2");
    ASSERT_EQ(*it++, "urobek2");
    ASSERT_EQ(*it++, "konkurencja");
    ASSERT_EQ(it != lst.end(), false);
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

TEST(dllistTest, size_typical)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.size(), 0);
    lst.push_front("urobek");
    ASSERT_EQ(lst.size(), 1);
    lst.push_front("konsternacja");
    ASSERT_EQ(lst.size(), 2);
    lst.pop_front();
    ASSERT_EQ(lst.size(), 1);
    lst.pop_front();
    ASSERT_EQ(lst.size(), 0);
}
#include <gtest/gtest.h>
#include "dllist.h"

TEST(dllistTest, copy_constructor_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string> copy_lst(lst);
    auto it = copy_lst.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, copy_constructor_edit)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    dllist<std::string> copy_lst(lst);
    ASSERT_EQ(*copy_lst.begin(), "urobek");
    *copy_lst.begin() = "kowariancja";
    ASSERT_EQ(*lst.begin(), "urobek");
    ASSERT_EQ(*copy_lst.begin(), "kowariancja");
}

TEST(dllistTest, move_constructor_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string> lst2(std::move(lst));
    ASSERT_EQ(lst.empty(), true);
    auto it = lst2.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "urobek");
}

TEST(dllistTest, copy_operator_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string> copy_lst;
    copy_lst = lst;
    auto it = copy_lst.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, copy_operator_not_empty)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string> copy_lst;
    copy_lst.push_front("kowariancja");
    copy_lst = lst;
    auto it = copy_lst.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, copy_operator_itself)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    lst = lst;
    #pragma GCC diagnostic pop
    auto it = lst.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, move_operator_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string> lst2;
    lst2 = std::move(lst);
    ASSERT_EQ(lst.empty(), true);
    ASSERT_EQ(*lst2.begin(), "konsternacja");
}

TEST(dllistTest, move_operator_not_empty)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string> lst2;
    lst2.push_front("kowariancja");
    lst2 = std::move(lst);
    ASSERT_EQ(lst.empty(), true);
    ASSERT_EQ(*lst2.begin(), "konsternacja");
}

TEST(dllistTest, move_operator_itself)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wself-move"
    lst = std::move(lst);
    #pragma GCC diagnostic pop
    auto it = lst.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, iterator_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, iterator_modify)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string>::iterator it = lst.begin();
    ASSERT_EQ(*it, "konsternacja");
    *it = "awangardowy";
    ASSERT_EQ(*it, "awangardowy");
    ASSERT_EQ(*lst.begin(), "awangardowy");
    it++;
    ASSERT_EQ(*it, "urobek");
}

TEST(dllistTest, iterator_postincrementation)
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

TEST(dllistTest, iterator_preincrementation)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string>::iterator it = lst.begin();
    ASSERT_EQ(*++it, "urobek");
    ASSERT_EQ(++it != lst.end(), false);
}

TEST(dllistTest, forward_iteration_auto)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.push_front("kowariancja");
    auto it = lst.begin();
    for (auto element : lst)
        ASSERT_EQ(element, *it++);
}

TEST(dllistTest, const_iterator_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    dllist<std::string>::const_iterator it = lst.cbegin();
    ASSERT_EQ(*it, "konsternacja");
}

TEST(dllistTest, const_iterator_postincrementation)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.push_front("gaz");
    auto it = lst.cbegin();
    ASSERT_EQ(*it++, "gaz");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(it != lst.cend(), false);
}

TEST(dllistTest, const_iterator_preincrementation)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    const  dllist<std::string> lst2 = lst;
    dllist<std::string>::const_iterator it = lst2.begin();
    ASSERT_EQ(*++it, "urobek");
    ASSERT_EQ(++it != lst.cend(), false);
}

TEST(dllistTest, const_forward_iteration_auto)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.push_front("kowariancja");
    const dllist<std::string>lst2 = lst;
    auto it = lst.begin();
    for (auto element : lst2)
        ASSERT_EQ(element, *it++);
}

TEST(dllistTest, begin_end_empty_list)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.begin() == lst.end(), true);
}

TEST(dllistTest, cbegin_cend_and_begin_end)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    const  dllist<std::string> lst2 = lst;
    ASSERT_EQ(lst2.begin() == lst2.cbegin(), true);
    ASSERT_EQ(lst2.end() == lst2.cend(), true);
}

TEST(dllistTest, cbegin_cend_empty_list)
{
    dllist<std::string> lst;
    ASSERT_EQ(lst.cbegin() == lst.cend(), true);
}

TEST(dllistTest, front_const)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    const dllist<std::string> lst2 = lst;
    ASSERT_EQ(lst2.front(), "konsternacja");
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

TEST(dllistTest, back_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(lst.back(), "urobek");
}

TEST(dllistTest, back_and_clear)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(lst.back(), "urobek");
    lst.clear();
    EXPECT_THROW(lst.back(), std::runtime_error);
}

TEST(dllistTest, push_front_typical)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    ASSERT_EQ(*lst.begin(), "urobek");
    lst.push_front("konsternacja");
    ASSERT_EQ(*lst.begin(), "konsternacja");
    ASSERT_EQ(*++lst.begin(), "urobek");
}

TEST(dllistTest, push_front_move)
{
     dllist<std::string> lst;
    lst.push_front(std::move("urobek"));
    ASSERT_EQ(*lst.begin(), "urobek");
    std::string str = "konsternacja";
    lst.push_front(std::move(str));
    ASSERT_EQ(*lst.begin(), "konsternacja");
    ASSERT_EQ(*++lst.begin(), "urobek");
    str = "kowariancja";
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
    ASSERT_EQ(*lst.begin(), "urobek");
    lst.push_back("konsternacja");
    ASSERT_EQ(*lst.begin(), "urobek");
    ASSERT_EQ(*++lst.begin(), "konsternacja");
}

TEST(dllistTest, push_back_move)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    ASSERT_EQ(*lst.begin(), "urobek");
    std::string str = "konsternacja";
    lst.push_back(str);
    ASSERT_EQ(*lst.begin(), "urobek");
    ASSERT_EQ(*++lst.begin(), "konsternacja");
    str = "kowariancja";
    ASSERT_EQ(*++lst.begin(), "konsternacja");
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

TEST(dllistTest, pop_front_empty_list)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    ASSERT_EQ(lst.pop_front(), "urobek");
    EXPECT_THROW(lst.pop_front(), std::runtime_error);
}

TEST(dllistTest, pop_back_typical)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    ASSERT_EQ(lst.pop_back(), "gaz");
    ASSERT_EQ(lst.pop_back(), "konsternacja");
    ASSERT_EQ(lst.pop_back(), "urobek");
    ASSERT_EQ(lst.empty(), true);
}

TEST(dllistTest, pop_back_empty_list)
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    ASSERT_EQ(lst.pop_back(), "urobek");
    EXPECT_THROW(lst.pop_back(), std::runtime_error);
}

TEST(dllistTest, insert_single_typical)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(++lst.cbegin(), "kowariancja", 1);
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(*inserted_it++, "konsternacja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
}

TEST(dllistTest, insert_single_begin)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(lst.cbegin(), "kowariancja", 1);
    ASSERT_EQ(*inserted_it, "kowariancja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
}

TEST(dllistTest, insert_single_end)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(lst.cend(), "kowariancja", 1);
    ASSERT_EQ(*inserted_it, "kowariancja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
    ASSERT_EQ(*it++, "kowariancja");
}

TEST(dllistTest, insert_single_move_typical)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    std::string str = "kowariancja";
    dllist<std::string>::iterator inserted_it = lst.insert(++lst.cbegin(), std::move(str));
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(*inserted_it, "konsternacja");
    ASSERT_EQ(*++lst.begin(), "kowariancja");
    str = "konkatenacja";
    ASSERT_EQ(*++lst.begin(), "kowariancja");
}

TEST(dllistTest, insert_single_move_begin)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    std::string str = "kowariancja";
    dllist<std::string>::iterator inserted_it = lst.insert(lst.cbegin(), std::move(str));
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(*inserted_it, "urobek");
    ASSERT_EQ(lst.front(), "kowariancja");
    str = "konkatenacja";
    ASSERT_EQ(lst.front(), "kowariancja");
}

TEST(dllistTest, insert_single_move_end)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    std::string str = "kowariancja";
    dllist<std::string>::iterator inserted_it = lst.insert(lst.cend(), std::move(str));
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(inserted_it == lst.end(), true);
    ASSERT_EQ(lst.back(), "kowariancja");
    str = "konkatenacja";
    ASSERT_EQ(lst.back(), "kowariancja");
}

TEST(dllistTest, insert_nothing)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(++lst.cbegin(), "kowariancja", 0);
    ASSERT_EQ(*inserted_it, "konsternacja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
}

TEST(dllistTest, insert_multiple_typical)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(++lst.cbegin(), "kowariancja", 3);
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(*inserted_it++, "kowariancja");
    ASSERT_EQ(*inserted_it++, "konsternacja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
}

TEST(dllistTest, insert_multiple_begin)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(lst.cbegin(), "kowariancja", 3);
    ASSERT_EQ(*inserted_it, "kowariancja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
}

TEST(dllistTest, insert_multiple_end)
{
    dllist<std::string> lst;
    lst.push_back("urobek");
    lst.push_back("konsternacja");
    lst.push_back("gaz");
    dllist<std::string>::iterator inserted_it = lst.insert(lst.cend(), "kowariancja", 3);
    ASSERT_EQ(*inserted_it, "kowariancja");
    auto it = lst.begin();
    ASSERT_EQ(*it++, "urobek");
    ASSERT_EQ(*it++, "konsternacja");
    ASSERT_EQ(*it++, "gaz");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "kowariancja");
    ASSERT_EQ(*it++, "kowariancja");
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
#include "dllist.h"
#include <iostream>

int main()
{
    dllist<std::string> lst;
    lst.push_front("urobek");
    lst.push_front("konsternacja");
    lst.push_front("gaz");
    std::cout << *lst.begin();
}
#include "dllist.h"

template<typename T> dllist<T>::iterator dllist<T>::iterator::operator++(int)
{
    iterator old_it = *this;
    this->pntr = this->pntr->next;
    return old_it;
};
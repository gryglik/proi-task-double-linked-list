#pragma once
#include <cstddef>
#include <iostream>

template<typename T>
class dllist
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;

private:
    struct dllnode
    {
        value_type value;
        dllnode *next;
        dllnode *prev;

        dllnode(const_reference val, dllnode* nxt = nullptr, dllnode* prv = nullptr)
            : value(val), next(nxt), prev(prv) {}

        const_reference get_value() const {return this->value;}
        reference get_value() {return this->value;}
    };

    dllnode *head = nullptr;
public:
    // Constructors
    dllist() = default;

    // Destructor
    ~dllist() {this->clear();}

    // Iterators
    class iterator
    {
    private:
        dllnode* pntr;
    public:
        iterator(dllnode* node)
            : pntr(node) {}

        iterator operator++(int);
        value_type& operator*() {return pntr->get_value();}
        bool operator!=(iterator it) {return this->pntr != it.pntr;}
    };
    iterator begin() {return iterator(this->head);}
    iterator end() {return iterator(nullptr);}

    // Element access
    reference front() {return this->head->get_value();}
    const_reference front() const {return this->head->get_value();}
    reference back();
    const_reference back() const;

    // Modifiers
    void push_front(const_reference val);
    void push_back(const_reference val);
    value_type pop_front();
    value_type pop_back();
    void clear();

    // Capacity
    bool empty() const {return this->head == nullptr;}
    size_type size() const;

    friend std::ostream operator<<(std::ostream& os, const dllist<value_type>& dllist);
};

template<typename T>
dllist<T>::iterator dllist<T>::iterator::operator++(int)
{
    iterator old_it = *this;
    this->pntr = this->pntr->next;
    return old_it;
};

template<typename T>
void dllist<T>::push_front(const_reference val)
{
    this->head = new dllnode(val, this->head);
    if (this->head->next != nullptr)
        this->head->next->prev = this->head;
};

template<typename T>
dllist<T>::value_type dllist<T>::pop_front()
{
    value_type front;
    if (not this->empty())
    {
        dllnode* to_delete = this->head;
        front = this->head->get_value();
        this->head = this->head->next;
        if (this->head != nullptr)
            this->head->prev = nullptr;
        delete to_delete;
    }
    return front;
};

template<typename T>
void dllist<T>::clear()
{
    while (not this->empty())
        this->pop_front();
};

template<typename T>
dllist<T>::size_type dllist<T>::size() const
{
    size_type size = 0;
    for (dllnode* ptr = this->head; ptr != nullptr; ptr = ptr->next)
        ++size;
    return size;
}
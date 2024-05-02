#pragma once
#include <cstddef>
#include <iostream>

template<typename T> class dllist
{
private:
    struct dllnode
    {
        T value;
        dllnode *prev;
        dllnode *next;

        dllnode(const T& val, dllnode* nxt = nullptr, dllnode* prv = nullptr)
            : value(val), next(nxt), prev(prv) {}

        const T& get_value() const {return this->value;}
        T& get_value() {return this->value;}
    };

    dllnode *head = nullptr;
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;

    // Constructors
    dllist() = default;

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
        bool operator!=(iterator it) {return this->pntr->get_value() != it->pntr->getvalue();}
    };
    iterator begin() {return iterator(this->head);}
    iterator end() {return iterator(nullptr);}

    // Modifiers
    void push_front(const_reference val);
    void push_back(const_reference val);
    reference pop_front();
    reference pop_back();
    void clear();

    // Capacity
    bool empty() const {return this->head == nullptr;}
    size_type size() const;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    friend std::ostream operator<<(std::ostream& os, const dllist<value_type>& dllist);

};
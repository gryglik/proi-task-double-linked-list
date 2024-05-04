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
    dllnode *tail = head;
public:
    // Constructors
    dllist() = default;
    dllist(const dllist& src);
    dllist(dllist&& src);

    // Destructor
    ~dllist() {this->clear();}

    // Assigment
    void operator=(const dllist& src);
    void operator=(dllist&& src);

    // Iterators
    class iterator
    {
    private:
        dllnode* pntr;
    public:
        iterator(dllnode* node)
            : pntr(node) {}

        iterator operator++(int);
        iterator& operator++();
        reference operator*() const {return pntr->get_value();}
        bool operator!=(const iterator it) const {return this->pntr != it.pntr;}
    };
    iterator begin() {return iterator(this->head);}
    iterator end() {return iterator(nullptr);}

    class const_iterator
    {
    private:
        const dllnode* pntr;
    public:
        const_iterator(const dllnode* node)
            : pntr(node) {}

        const_iterator operator++(int);
        const_iterator& operator++();
        const_reference operator*() const {return pntr->get_value();}
        bool operator!=(const_iterator cit) const {return this->pntr != cit.pntr;}
    };
    const_iterator begin() const {return const_iterator(this->head);}
    const_iterator end() const {return const_iterator(nullptr);}
    const_iterator cbegin() const {return const_iterator(this->head);}
    const_iterator cend() const {return const_iterator(nullptr);}

    // Element access
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // Modifiers
    void push_front(const_reference val);
    void push_front(value_type&& val);

    void push_back(const_reference val);
    void push_back(value_type&& val);

    value_type pop_front();
    value_type pop_back();

    iterator insert(const_iterator it, const_reference val, size_type size = 1);
    iterator insert(const_iterator it, value_type&& val);
    iterator insert(const_iterator it, const_iterator first, const_iterator last);

    iterator erase(const_iterator it);
    iterator erase(const_iterator first, const_iterator last);

    void clear();

    // Capacity
    bool empty() const {return this->head == nullptr && this->tail == nullptr;}
    size_type size() const;

    // Friend methods
    friend std::ostream operator<<(std::ostream& os, const dllist<value_type>& dllist);
};

template<typename T>
dllist<T>::dllist(const dllist& src)
{
    for (const_reference element : src)
        this->push_back(element);
};

template<typename T>
dllist<T>::dllist(dllist&& src)
{
    this->head = src.head;
    this->tail = src.tail;
    src.head = nullptr;
    src.tail = nullptr;
};

template<typename T>
void dllist<T>::operator=(const dllist& src)
{
    if (&src != this)
    {
        this->clear();
        for (const_reference element : src)
            this->push_back(element);
    }
};

template<typename T>
void dllist<T>::operator=(dllist&& src)
{
    if (&src != this)
    {
        this->clear();
        this->head = src.head;
        this->tail = src.tail;
        src.head = nullptr;
        src.tail = nullptr;
    }
};

template<typename T>
dllist<T>::iterator dllist<T>::iterator::operator++(int)
{
    iterator old_it = *this;
    this->pntr = this->pntr->next;
    return old_it;
};

template<typename T>
dllist<T>::iterator& dllist<T>::iterator::operator++()
{
    this->pntr = this->pntr->next;
    return *this;
};

template<typename T>
dllist<T>::const_iterator dllist<T>::const_iterator::operator++(int)
{
   const_iterator old_it = *this;
   this->pntr = this->pntr->next;
   return old_it;
};

template<typename T>
dllist<T>::const_iterator& dllist<T>::const_iterator::operator++()
{
   this->pntr = this->pntr->next;
   return *this;
};

template<typename T>
dllist<T>::reference dllist<T>::front()
{
    if (not this->empty())
        return *this->begin();
    throw (std::runtime_error("Cannot call front() on empty list."));
}

template<typename T>
dllist<T>::const_reference dllist<T>::front() const
{
    if (not this->empty())
        return *this->begin();
    throw (std::runtime_error("Cannot call front() on empty list."));
}

template<typename T>
dllist<T>::reference dllist<T>::back()
{
    if (not this->empty())
        return this->tail->get_value();
    throw (std::runtime_error("Cannot call back() on empty list."));
}

template<typename T>
void dllist<T>::push_front(const_reference val)
{
    this->head = new dllnode(val, this->head);
    if (this->head->next != nullptr)
        this->head->next->prev = this->head;
    else
        this->tail = this->head;
};

template<typename T>
void dllist<T>::push_back(const_reference val)
{
    this->tail = new dllnode(val, nullptr, this->tail);
    if (this->tail->prev != nullptr)
        this->tail->prev->next = this->tail;
    else
        this->head = this->tail;
};

template<typename T>
dllist<T>::value_type dllist<T>::pop_front()
{
    if (not this->empty())
    {
        dllnode* to_delete = this->head;
        value_type front = this->front();
        this->head = this->head->next;
        if (this->head != nullptr)
            this->head->prev = nullptr;
        else
            this->tail = nullptr;
        delete to_delete;
        return front;
    }
    throw (std::runtime_error("Cannot call pop_front() on empty list."));
};

template<typename T>
dllist<T>::value_type dllist<T>::pop_back()
{
    if (not this->empty())
    {
        dllnode* to_delete = this->tail;
        value_type back = this->back();
        this->tail = this->tail->prev;
        if (this->tail != nullptr)
            this->tail->next = nullptr;
        else
            this->head = nullptr;
        delete to_delete;
        return back;
    }
    throw (std::runtime_error("Cannot call pop_back() on empty list."));
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
};
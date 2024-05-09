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
        dllnode(value_type&& val, dllnode* nxt = nullptr, dllnode* prv = nullptr)
            : value(std::move(val)), next(nxt), prev(prv) {}

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
        const dllist* list_pntr;
        dllnode* node_pntr;

        iterator(const dllist* list, dllnode* node)
            : list_pntr(list), node_pntr(node) {}

        friend class dllist;
    public:
        iterator operator++(int);
        iterator& operator++();

        iterator operator--(int);
        iterator& operator--();

        reference operator*() const {return node_pntr->get_value();}

        bool operator!=(const iterator it) const {return this->node_pntr != it.node_pntr;}
        bool operator==(const iterator it) const {return this->node_pntr == it.node_pntr;}
    };
    iterator begin() {return iterator(this, this->head);}
    iterator end() {return iterator(this, nullptr);}

    class const_iterator
    {
    private:
        const dllist* list_pntr;
        dllnode* node_pntr;

        const_iterator(const dllist* list, dllnode* node)
            : list_pntr(list), node_pntr(node) {}

        friend class dllist;
    public:
        const_iterator operator++(int);
        const_iterator& operator++();

        const_iterator operator--(int);
        const_iterator& operator--();

        const_reference operator*() const {return node_pntr->get_value();}
        bool operator!=(const_iterator cit) const {return this->node_pntr != cit.node_pntr;}
        bool operator==(const_iterator cit) const {return this->node_pntr == cit.node_pntr;}
    };
    const_iterator begin() const {return const_iterator(this, this->head);}
    const_iterator end() const {return const_iterator(this, nullptr);}
    const_iterator cbegin() const {return const_iterator(this, this->head);}
    const_iterator cend() const {return const_iterator(this, nullptr);}

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

    iterator insert(const_iterator it, const_reference val, size_type size);
    iterator insert(const_iterator it, value_type&& val);

    iterator erase(const_iterator it);

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
    this->node_pntr = this->node_pntr->next;
    return old_it;
};

template<typename T>
dllist<T>::iterator& dllist<T>::iterator::operator++()
{
    this->node_pntr = this->node_pntr->next;
    return *this;
};

template<typename T>
dllist<T>::iterator dllist<T>::iterator::operator--(int)
{
    iterator old_it = *this;
    if (this->node_pntr == nullptr)
        this->node_pntr = this->list_pntr->tail;
    else
        this->node_pntr = this->node_pntr->prev;
    return old_it;
};

template<typename T>
dllist<T>::iterator& dllist<T>::iterator::operator--()
{
    if (this->node_pntr == nullptr)
        this->node_pntr = this->list_pntr->tail;
    else
        this->node_pntr = this->node_pntr->prev;
    return *this;
};

template<typename T>
dllist<T>::const_iterator dllist<T>::const_iterator::operator++(int)
{
   const_iterator old_it = *this;
   this->node_pntr = this->node_pntr->next;
   return old_it;
};

template<typename T>
dllist<T>::const_iterator& dllist<T>::const_iterator::operator++()
{
   this->node_pntr = this->node_pntr->next;
   return *this;
};

template<typename T>
dllist<T>::const_iterator dllist<T>::const_iterator::operator--(int)
{
    const_iterator old_it = *this;
    if (this->node_pntr == nullptr)
        this->node_pntr = this->list_pntr->tail;
    else
        this->node_pntr = this->node_pntr->prev;
    return old_it;
};

template<typename T>
dllist<T>::const_iterator& dllist<T>::const_iterator::operator--()
{
    if (this->node_pntr == nullptr)
        this->node_pntr = this->list_pntr->tail;
    else
        this->node_pntr = this->node_pntr->prev;
    return *this;
};

template<typename T>
dllist<T>::reference dllist<T>::front()
{
    if (not this->empty())
        return *this->begin();
    throw (std::runtime_error("Cannot call front() on empty list."));
};

template<typename T>
dllist<T>::const_reference dllist<T>::front() const
{
    if (not this->empty())
        return *this->begin();
    throw (std::runtime_error("Cannot call front() on empty list."));
};

template<typename T>
dllist<T>::reference dllist<T>::back()
{
    if (not this->empty())
        return this->tail->get_value();
    throw (std::runtime_error("Cannot call back() on empty list."));
};

template<typename T>
dllist<T>::const_reference dllist<T>::back() const
{
    if (not this->empty())
        return this->tail->get_value();
    throw (std::runtime_error("Cannot call back() on empty list."));
};

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
void dllist<T>::push_front(value_type&& val)
{
    this->head = new dllnode(std::move(val), this->head);
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
void dllist<T>::push_back(value_type&& val)
{
    this->tail = new dllnode(std::move(val), nullptr, this->tail);
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
dllist<T>::iterator dllist<T>::insert(const_iterator it, const_reference val, size_type size)
{
    dllnode* first = nullptr;

    if (size == 0)
        return iterator(this, it.node_pntr);

    if (it == this->cbegin())
    {
        while (size--)
            this->push_front(val);
        return this->begin();
    }

    if (it == this->cend())
    {
        this->push_back(val);
        size--;
        first = this->tail;
        while (size--)
            this->push_back(val);
        return iterator(this, first);
    }

    first = new dllnode(val, it.node_pntr, it.node_pntr->prev);
    it.node_pntr->prev->next = first;
    it.node_pntr->prev = first;
    size--;
    while (size--)
    {
        it.node_pntr->prev->next = new dllnode(val, it.node_pntr, it.node_pntr->prev);
        it.node_pntr->prev = it.node_pntr->prev->next;
    }
    return iterator(this, first);
};

template<typename T>
dllist<T>::iterator dllist<T>::insert(const_iterator it, value_type&& val)
{
    if (it == this->cbegin())
    {
        this->push_front(std::move(val));
        return this->begin();
    }

    if (it == this->cend())
    {
        this->push_back(std::move(val));
        return iterator(this, this->tail);
    }

    it.node_pntr->prev->next = new dllnode(std::move(val), it.node_pntr, it.node_pntr->prev);
    it.node_pntr->prev = it.node_pntr->prev->next;
    return iterator(this, it.node_pntr->prev);
};

template<typename T>
dllist<T>::iterator dllist<T>::erase(const_iterator it)
{
    if (it == this->cbegin())
    {
        this->pop_front();
        return iterator(this->begin());
    }

    if (it == this->cend())
        return iterator(this->end());

    dllnode* to_delete = it.node_pntr;
    it.node_pntr->prev->next = it.node_pntr->next;
    it.node_pntr->next->prev = it.node_pntr->prev;
    dllnode* following = it.node_pntr->next;
    delete to_delete;
    return iterator(this, following);
}

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
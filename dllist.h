#pragma once

template<typename T>
class dllist
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
    };

    dllnode *head = nullptr;
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;

    dllist() = default;

    void clear();

    bool empty() const {return this->head == nullptr;}

    size_type size() const;

    void push_front(const_reference val);
    void push_back(const_reference val);

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    reference pop_front();
    reference pop_back();
};
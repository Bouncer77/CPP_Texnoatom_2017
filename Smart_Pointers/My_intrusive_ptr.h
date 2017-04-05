#pragma once

#include <iostream>
#include <memory>

using namespace std;

class RefCounterBase
{
public:
    RefCounterBase() :
        _counter(0)
    {}

    virtual ~RefCounterBase()
    {}

    void addRef()
    {
        ++_counter;
    }

    void releaseRef()
    {
        --_counter;
        if (_counter == 0)
            delete this;
    }
private:
    std::size_t _counter;
};

template <typename T>
class IntrusivePtr
{
public:
    IntrusivePtr() :
        _data(nullptr)
    {}

    IntrusivePtr(T* data) :
        _data(data)
    {
        if (_data)
            _data->addRef();
    }

    IntrusivePtr(const IntrusivePtr& ptr)
        : _data(ptr._data)
    {
        if (_data)
            _data->addRef();
    }

    IntrusivePtr& operator = (const IntrusivePtr& ptr)
    {
        swap(IntrusivePtr(ptr));
        return *this;
    }

    operator bool() const
    {
        return _data != nullptr;
    }

    void swap(IntrusivePtr& ptr)
    {
        std::swap(_data, ptr._data);
    }

    void swap(IntrusivePtr&& ptr)
    {
        std::swap(_data, ptr._data);
    }

    T* operator ->()
    {
        return _data;
    }

    T& operator *()
    {
        return *_data;
    }

    T* get()
    {
        return _data;
    }

    ~IntrusivePtr()
    {
        if (_data)
            _data->releaseRef();
    }
private:
    T* _data;
};

struct IntrusiveNode;
using Node_ptr = IntrusivePtr<IntrusiveNode>;

struct IntrusiveNode : public RefCounterBase
{
    int data;
    Node_ptr next;

    IntrusiveNode() :
        data(0)
    {
        cout << "Node " << data << " created\n";
    }

    ~IntrusiveNode()
    {
        cout << "Node " << data << " deleted\n";
    }
};

void delete_even(Node_ptr head)
{
    for (IntrusiveNode* cur = head.get(); cur; cur = cur->next.get())
        if (cur->next)
            cur->next = cur->next->next;
}

Node_ptr create_list(std::size_t size)
{
    Node_ptr head;
    for (std::size_t i = 0; i < size; ++i)
    {
        Node_ptr n = new IntrusiveNode();
        n->data = size - i;
        n->next = head;
        head = n;
    }
    return head;
}

void print_list(Node_ptr head)
{
    for (IntrusiveNode* cur = head.get(); cur; cur = cur->next.get())
        cout << cur->data << ' ';
    cout << endl;
}
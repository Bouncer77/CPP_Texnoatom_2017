#pragma once

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class MySharedPtr
{
public:
    MySharedPtr() :
        _data(nullptr),
        _counter(new std::size_t(1))
    {}

    MySharedPtr(const MySharedPtr& ptr) :
        _data(ptr._data),
        _counter(ptr._counter)
    {
        addRef();
    }

    explicit MySharedPtr(T* data) :
        _data(data),
        _counter(new std::size_t(1))
    {}

    MySharedPtr& operator = (const MySharedPtr& ptr)
    {
        swap(MySharedPtr(ptr));
        return *this;
    }

    void swap(MySharedPtr&& ptr)
    {
        std::swap(_data, ptr._data);
        std::swap(_counter, ptr._counter);
    }

    operator bool() const
    {
        return _data != nullptr;
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

    ~MySharedPtr()
    {
        if (releaseRef() == 0)
        {
            delete _counter;
            delete _data;
        }
    }

private:
    T* _data;
    std::size_t* _counter;

    std::size_t& addRef()
    {
        return ++(*_counter);
    }

    std::size_t& releaseRef()
    {
        return --(*_counter);
    }
};
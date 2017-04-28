#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <memory>

using namespace std;

template<typename T>
class MyVector
{
public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    class reverse_iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    public:
        reverse_iterator(T* ptr) :
            _ptr(ptr)
        {}

        reverse_iterator& operator ++()
        {
            --_ptr;
            return *this;
        }

        T& operator *()
        {
            return *_ptr;
        }

        bool operator !=(const reverse_iterator& rhs) const
        {
            return _ptr != rhs._ptr;
        }
    private:
        T* _ptr;
    };

    MyVector() :
        _data(nullptr),
        _size(0),
        _capacity(0)
    {}

    explicit MyVector(std::size_t size) :
        _data(new T[size]),
        _size(size),
        _capacity(size)
    {}

    MyVector(const MyVector& v) :
        _data(new T[v._size]),
        _size(v._size),
        _capacity(v._capacity)
    {
        for (std::size_t i = 0; i < _size; ++i)
            _data[i] = v._data[i];
    }

    iterator begin()
    {
        return &_data[0];
    }

    iterator end()
    {
        return &_data[_size];
    }

    reverse_iterator rbegin()
    {
        return &_data[_size - 1];
    }

    reverse_iterator rend()
    {
        return &_data[-1];
    }

    T& operator [](std::size_t i)
    {
        return const_cast<T&>(static_cast<const MyVector*>(this)->operator [](i));
    }

    const T& operator [](std::size_t i) const
    {
        return _data[i];
    }

    T& at(std::size_t i)
    {
        return const_cast<T&>(static_cast<const MyVector*>(this)->at(i));
    }

    const T& at(std::size_t i) const
    {
        if (_size > i && i >= 0)
            return this->operator [] (i);
        else
            throw std::out_of_range("Subscript out of range");
    }

    void swap(MyVector& v)
    {
        std::swap(this->_data, v._data);
        std::swap(this->_size, v._size);
        std::swap(this->_capacity, v._capacity);
    }

    MyVector& operator =(const MyVector& v)
    {
        MyVector copy(v);
        swap(copy);
        return *this;
    }

    void push_back(const T& value)
    {
        _double_capacity();
        _data[_size] = value;
        ++_size;
    }

    T pop_back()
    {
        T result = _data[_size - 1];
        --_size;
    }

    friend ostream& operator << (std::ostream& os, const MyVector& v)
    {
        for (std::size_t i = 0; i < v._size; ++i)
            os << v[i] << ' ';
        os << "size: " << v.size() << " capacity: " << v.capacity();
        return os;
    }

    std::size_t size() const
    {
        return _size;
    }

    std::size_t capacity() const
    {
        return _capacity;
    }

    void reserve(std::size_t capacity)
    {
        if (capacity <= _capacity)
            return;

        this->_capacity = capacity;
        T* newData = new T[capacity];
        for (std::size_t i = 0; i < _size; ++i)
            newData[i] = _data[i];

        _data.reset(newData);
    }

    void resize(std::size_t size, const T& value = T())
    {
        T* newData = new T[size];
        for (std::size_t i = 0; i < size; ++i)
            newData[i] = i < _size ? _data[i] : value;

        _data.reset(newData);
        _size = size;
        _capacity = size;
    }

private:
    std::unique_ptr<T[]> _data;
    std::size_t _size, _capacity;

    void _double_capacity()
    {
        if (_size == _capacity)
            reserve(_capacity > 0 ? 2 * _capacity : 1);
    }
};

template<typename IterT>
void print(IterT begin, IterT end)
{
    for (auto it = begin; it != end; ++it)
        cout << *it << endl;
}
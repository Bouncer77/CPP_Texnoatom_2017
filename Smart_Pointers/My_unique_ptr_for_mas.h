#pragma once

#include <iostream>
#include <memory>

#ifndef _MY_UNIQUE_PTR_
#define _MY_UNIQUE_PTR_

template<typename T, std::size_t n>
class MyUniquePtr
{
public:
    using value_type = T;
    using const_value_type = const T;
    using rvalue_reference = T&&;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using value_size = std::size_t;

    //! ������ �����������
    MyUniquePtr() :
        m_data(nullptr)
    {}

    //! ����������� � ����������
    MyUniquePtr(const_pointer data) :
        m_data(data)
    {}

    //! ����������� �����������
    MyUniquePtr(const MyUniquePtr& that) = delete;

    //! ����������� �����������
    MyUniquePtr(MyUniquePtr&& that) :
        m_data(nullptr)
    {
        swap(that)
    }

    //! ����������
    ~MyUniquePtr()
    {
        delete[] m_data;
    }

    //! ������������� �������� =   (��� lvalue)
    reference operator = (const_reference that) = delete;

    //! ������������� �������� =   (��� rvalue)
    reference operator = (rvalue_reference that)
    {
        swap(that);
    }

    //! ������������� �������� *
    reference operator * () const
    {
        return *m_data;
    }

    //! ������������� �������� ->
    pointer operator -> () const
    {
        return m_data;
    }

    //! ����� swap
    void swap(MyUniquePtr &that)
    {
        std::swap(m_data, that.m_data);
    }

    //! ����� ����������
    void reset(pointer data)
    {
        delete []m_data;
        m_data = data;
    }

private:
    value_type *m_data;
};

#endif /! _MY_UNIQUE_PTR_
#ifndef _MY_ARRAY_H_
#define _MY_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <exception>

//-----------------------------------------
//! Macro to test object integrity
//-----------------------------------------

#if !defined (NO_TESTS_AT_ALL)

#define ASSERT_OK()					\
	if (!ok())						\
	{								\
		dump();						\
		assert(!"Object is OK");	\
	}
#endif //! _ASSERT_OK_


template <typename T, const std::size_t max_size = 256>
class MyArray
{
public:
    using value_type = T;
    using const_value_type = const T;
    using size_type = std::size_t;

    class badAllocExeption { badAllocExeption (const char* msg); };
    class outOfRangeExeption { outOfRangeExeption (const char* msg); };
    class emptyArray { emptyArray (const char* msg); };

    MyArray() :
        m_size(0)
    {}

    MyArray(const size_type n,
        const value_type& value = value_type()) :
        m_size(0)
    {
        if (n > max_size)
        {
            throw MyArray::badAllocExeption(__FUNCSIG__
                __FILE__,
                __LINE__);
        }

        m_size = n;
        std::fill_n(m_data, m_size, value);
    }

    //  онструктор со списком инициализации
    MyArray(std::initializer_list<value_type> const & Ist)
    {
        auto it = Ist.begin();
        for (std::size_t i = 0; i < max_size && it != Ist.end(); ++i, ++it)
        {
            m_data[i] = *it;
        }
    }

    //! @brief Default copy constructor
    MyArray(const MyArray& that) = default;

    //! @brief Defult destructor
    ~MyArray() = default;
    
    value_type& operator [] (const size_type n) const
    {
        return const_cast<value_type&>(static_cast<const MyArray*>->operator [] (n));
    }
        
    const_value_type& operator [] (const size_type n)
    {
        if (n >= m_size)
        {
            throw outOfRangeExeption(__FUNCSIG__
                __FILE__,
                __LINE__);
        }

        return m_data[n];
    }

    const MyArray& operator = (const MyArray& that)
    {
        MyArray<value_type> victim(that);
        swap(victim);
        return *this;
    }

    const_value_type& front() const
    {
        if (!empty())
        {
            return this->operator[] (0);
        }
       else
        {
            throw emptyArray(__FUNCSIG__,
                __FILE__,
                __LINE__);
        }
    }

    const_value_type& back() const
    {
        if (!empty())
        {
            return operator[] (size - 1);
        }
        else
        {
            throw emptyArray(__FUNCSIG__,
                __FILE__,
                __LINE__);
        }
    }

    void push_back(const_value_type& that)
    {
        if (m_size >= max_size)
        {
            throw badAllocExeption(__FUNCSIG__,
                __FILE__,
               __LINE__);
        }

        m_data[m_size++] = that;
    }

    bool empty() const noexcept
    {
        return !m_size;
    }

    size_type size() const noexcept
    {
        return m_size;
    }

    size_type capacity() const noexcept
    {
        return max_size;
    }

    void swap(MyArray& rhs)
    {
        std::swap_ranges(m_data, m_data + m_size, rhs.m_size);
        std::swap(m_size, rhs.m_size);
    }

    bool ok() const
    {
        if (m_size <= max_size)
        {
            return true;
        }
        return false;
    }

    void dump() const
    {
        if (ok() == true)
        {
           std::cout << "Array (ok)" << std::endl;
        }
        else
        {
            std::cout << "Array (ERROR)" << std::endl;
        }
        std::cout << "{" << std::endl;
        myPrintArray();
        std::cout << "}" << std::endl;
    }

    void myPrintArray() const
    {
        std::cout << "    size = " << m_size << "\n    capacity = " << max_size << std::endl;
        std::cout << "\n    data[" << m_size << "]:" << std::endl;
        std::cout << "  {" << std::endl;
        for (std::size_t i = 0; i < m_size; ++i)
            std::cout << "      [" << i << "] = " << m_data[i] << std::endl;
        std::cout << "  }" << std::endl;
    }

private:
    size_type m_size;
    value_type m_data[max_size];
};

#endif //! _MY_ARRAY_H_
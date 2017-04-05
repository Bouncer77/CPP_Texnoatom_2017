//-----------------------------------------------------------------------------
//! @file vector_b.h
//-----------------------------------------------------------------------------
//! @mainpage
//!
//! Implements a vector class
//!
//!
//! @version 2.0
//!
//! @author Kosenkov Ivan, Morochev Georgi 
//! @date   30.03.2017
//-----------------------------------------------------------------------------

#include <assert.h>
#include <iostream>
#include <algorithm>
#include <initializer_list>

//#include <fstream>

#include "va_iterator.h"

#ifndef _BIG_VECTOR_H_
#define _BIG_VECTOR_H_

namespace big 
{
    //-----------------------------------------------------------------------------
    //! @class vector_b
    //! @tparam Tp The type of the value in the vector
    //-----------------------------------------------------------------------------
    template<typename Tp>
    class vector_b
    {
    public:

        friend class va_iterator<Tp>; // My bidirectional iterators

        using value_type        = Tp;                    //!< Element type
        using const_value_type  = const Tp;              //!< Constant element type
        using reference         = Tp&;                   //!< Reference type
        using const_reference   = const Tp&;             //!< Constant reference type
        using iterator          = va_iterator<Tp>;       //!< Iterator type
        using const_iterator    = va_iterator<const Tp>; //!< Constant iterator type
        using size_type         = std::size_t;           //!< Size type

        //-----------------------------------------------------------------------------
        //! @brief Default constructor
        //-----------------------------------------------------------------------------
        vector_b() noexcept :
            m_size(0),
            m_capacity(0),
            m_data(nullptr)
        {}

        //-----------------------------------------------------------------------------
        //! @brief Constructor
        //! @param Vector size
        //-----------------------------------------------------------------------------
        explicit vector_b(size_type size) :
            m_data(new Tp[size]),
            m_size(size),
            m_capacity(size)
        {}

        //-----------------------------------------------------------------------------
        //! @brief The copy constructor
        //! @details Deep copy
        //! @param Vector reference
        //-----------------------------------------------------------------------------
        vector_b(const vector_b& v) :
            m_data(new Tp[v.m_size]),
            m_size(v.m_size),
            m_capacity(v.m_capacity)
        {
            std::copy(v.m_data, v.m_data + v.m_size, m_data);
        }

        //-----------------------------------------------------------------------------
        //! @brief Destructor
        //-----------------------------------------------------------------------------
        ~vector_b()
        {
            delete[] m_data;
            m_data = nullptr;
            m_size = POISON<size_type>::value;
            m_capacity = POISON<size_type>::value;
        }

        //-----------------------------------------------------------------------------
        //! @brief Clear the vector
        //-----------------------------------------------------------------------------
        void clear() noexcept
        {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the begin of the vector
        //-----------------------------------------------------------------------------
        iterator begin()
        {
            BIG_OUT_OF_RANGE(!m_size);
            return iterator(m_data);
        }

        //-----------------------------------------------------------------------------
        //! @brief Iterator
        //! @return Iterator on the end of the vector
        //-----------------------------------------------------------------------------
        iterator end()
        {
            BIG_OUT_OF_RANGE(!m_size);
            return iterator(m_data + m_size);
        }

        //-----------------------------------------------------------------------------
        //! @brief Constant iterator
        //! @return Iterator on the begin of the vector
        //-----------------------------------------------------------------------------
        const_iterator cbegin() const
        {
            BIG_OUT_OF_RANGE(!m_size);
            return const_iterator(m_data);
        }

        //-----------------------------------------------------------------------------
        //! @brief Constant iterator
        //! @return Iterator on the end of the vector
        //-----------------------------------------------------------------------------
        const_iterator cend() const {
            BIG_OUT_OF_RANGE(!m_size);
            return const_iterator(m_data + m_size);
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the vector
        //! @param n Number of the element
        //! @throws The same exceptions as the operator[] returns const reference
        //! @return Reference on the nth item of the vector
        //-----------------------------------------------------------------------------
        reference operator [](const size_type n)
        {
            return const_cast<reference>(static_cast<const vector_b*>(this)->operator [](n));
        }

        //-----------------------------------------------------------------------------
        //! @brief Operator addressing
        //! @details Checks n for occurrence in the interval of bounds of the vector
        //! @param n Number of the element
        //! @throw big::outOfRange When n is bigger or equal than size of the vector
        //! @throw big::invalidObject From big_ASSERT_VALID() when vector is not valid
        //! @return Const reference on the nth item of the vector
        //-----------------------------------------------------------------------------
        const_reference operator[](const size_type n) const {
            BIG_ASSERT_VALID(this);

            BIG_OUT_OF_RANGE(n >= size_);
            return data_[n];
        }


        //-----------------------------------------------------------------------------
        //! @brief Swap two vector
        //! @param rhs other vector to which you want to exchange
        //-----------------------------------------------------------------------------
        void swap(vector_b& rhs) noexcept
        {
            std::swap(m_data, rhs.m_data);
            std::swap(m_size, rhs.m_size);
            std::swap(m_capacity, rhs._capacity);
        }

        //-----------------------------------------------------------------------------
        //! @brief The assignment operator
        //! @details Use copy and move idiom
        //! @param that The source of the assignment
        //! @throws The same exceptions as the vector_t(const vector_t&)
        //! @return Constant reference to the calling object
        //-----------------------------------------------------------------------------
        vector_b& operator =(const vector_b& that)
        {
            BIG_ASSERT_VALID(this);

            if (this == &that)
                return *this;

            vector_b buf_vector(that);
            BIG_ASSERT_VALID(&buf_vector);
            swap(buf_vector);

            BIG_ASSERT_VALID(this);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief The move assignment operator
        //! @param that The move source
        //! @return Reference to the calling object
        //-----------------------------------------------------------------------------
        vector_b& operator=(vector_b&& that) 
        {
            BIG_ASSERT_VALID(this);

            swap(this);
            return *this;
        }

        //-----------------------------------------------------------------------------
        //! @brief Push new item in back of the vector
        //! @details Can increase the capacity
        //! @param x new element which will be added in vector
        //! @throw big::invalidObject From big_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function alloc()
        //-----------------------------------------------------------------------------
        void push_back(const_reference value)
        {
            BIG_ASSERT_VALID(this);

            _double_capacity();

            m_data[m_size++] = value;

            BIG_ASSERT_VALID(this);
        }


        //-----------------------------------------------------------------------------
        //! @brief Push new rvalue reference item in back of the vector
        //! @details Can increase the capacity
        //! @param x new element which will be added in vector
        //! @throw big::invalidObject From big_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function alloc()
        //-----------------------------------------------------------------------------
        void push_back(const_value_type&& value) 
        {
            BIG_ASSERT_VALID(this);

            _double_capacity();

            m_data[m_size++] = value;

            BIG_ASSERT_VALID(this);
        }




        //-----------------------------------------------------------------------------
        //! Метод, возвращает последний элемент вектора
        //-----------------------------------------------------------------------------
        value_type back() const
        {
            BIG_ASSERT_VALID(this);
            return m_data[m_size - 1];
        }

        //-----------------------------------------------------------------------------
        //! Метод, удаляющий последний элемент в векторе
        //! @return копию удаленного элемента
        //-----------------------------------------------------------------------------
        void pop_back()
        {
            BIG_ASSERT_VALID(this);

            m_data[m_size--] = POISON<value_type>::value;

            BIG_ASSERT_VALID(this);

            return result;
        }

        //-----------------------------------------------------------------------------
        //! Метод, возвращает размер вектора
        //-----------------------------------------------------------------------------
        size_type size() const
        {
            BIG_ASSERT_VALID(this);

            return m_size;
        }

        //-----------------------------------------------------------------------------
        //! Метод, возвращает количество элементов под которое выделенна память
        //-----------------------------------------------------------------------------
        size_type capacity() const
        {
            BIG_ASSERT_VALID(this);

            return _capacity;
        }

        //-----------------------------------------------------------------------------
        //! @brief Reserve new memory
        //! @details Do not shrink the capacity
        //! @param n new capacity
        //! @throw big::invalidObject From big_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function alloc()
        //-----------------------------------------------------------------------------
        void reserve(const size_type capacity)
        {
            BIG_ASSERT_VALID(this);

            if (capacity <= m_capacity)
                return;

            m_capacity = capacity;
            Tp* newData = new Tp[capacity];

            std::copy(m_data, m_data + m_size, newData);

            delete[] m_data;
            m_data = newData;

            BIG_ASSERT_VALID(this);
        }

        //-----------------------------------------------------------------------------
        //! @brief Create new block of the memory
        //! @details Can change size and capacity
        //! @details Specialized types: short, int, long long, char (also with unsigned), float, double
        //! @details These types use memcpy() and memset()
        //! @param n The number of elements for which memory is allocated
        //! @param value initializer for n elements
        //! @throw big::invalidObject From big_ASSERT_VALID() when vector is not valid
        //! @throws The same exceptions as the function shrink_alloc()
        //-----------------------------------------------------------------------------
        void resize(const size_type size, const_reference value = Tp())
        {
            Tp* newData = new Tp[size];
            for (std::size_t i = 0; i < size; ++i)
                newData[i] = i < m_size ? m_data[i] : value;

            delete[] m_data;
            m_data = newData;
            m_size = size;
            m_capacity = size;
        }

        //-----------------------------------------------------------------------------
        //! @brief Silent verifier
        //! @return True if vector is valid else return false
        //-----------------------------------------------------------------------------
        bool is_valid() const noexcept
        {
            if (m_size >= 0 && m_size <= m_capacity && m_data != nullptr)
                return true;

            return false;
        }
        
        //-----------------------------------------------------------------------------
        //! @brief Constructor at std::initializer_list
        //! @details Constructor which copy from std::initializer_list
        //! @param init List of elements
        //! @throws The same exceptions as the function resize()
        //-----------------------------------------------------------------------------
        vector_b(const std::initializer_list<value_type>& init) :
            m_size(0),
            m_capacity(0),
            m_data(nullptr)
        {
            resize(init.size());

            std::copy(init.begin(), init.end(), m_data);
        }

        //-----------------------------------------------------------------------------
        //! @brief Print Vector
        //! @details Prints the contents of the vector into the standard output stream
        //-----------------------------------------------------------------------------
        void pVector() const
        {
        std::cout << __FUNCSIG__ << "\n" << __FILE__ << "\n" << __LINE__ << std::endl;

        std::cout << "Stack (" << (ok() ? "ok" : "error") << ")\n    {\n";
        std::cout << "    size = " << _size << ";\n" << "    capacity = " << _capacity << "\n\n";
        std::cout << "    data[" << _size << "]:\n        {\n";
        for (std::size_t i = 0; i < _size; ++i)
        {
        std::cout << "        [" << i << "] = " << _data[i] << std::endl;
        }
        std::cout << "        }\n    }\n";
        }


    private:
        size_type m_size;     //!< Size of the vector 
        size_type m_capacity; //!< Capacity of the vector
        value_type *m_data;   //!< A pointer to an vector
        
        //-----------------------------------------------------------------------------
        //! @brief Constructor at std::initializer_list
        //! @details Method, increases the storage capacity by 2 times, when size equally capacity
        //! @details if capacity equally zero - use reserve(1)
        //! @throws The same exceptions as the function reserve()
        //-----------------------------------------------------------------------------
        //! Метод, увеличивает емкость хранения в 2 раза, при достижение _size == _capacity
        void _double_capacity()
        {
            if (m_size == m_capacity)
                reserve(m_capacity > 0 ? 2 * m_capacity : 1);
        }

        //-----------------------------------------------------------------------------
        //! @brief Dumper
        //! @details Create file "__vector_dump.txt" where is information about vector's status
        //! @details Macro big_NWRITE prohibit function dump() print elements (for example when value_type has not operator<<)
        //! @param function_name Name of function which call this method
        //! @param line_number Number of line which call this method
        //-----------------------------------------------------------------------------
        void dump(const char* file,
            const char* function_name,
            int         line_number,
            const char* output_file = "__vector_dump.txt") const;
    };
}

//! @brief Implementation methods of the class vector_b
#include "implement_vector.hpp"
//#include "vector_bool_b.h"

#endif // _BIG_VECTOR_H_






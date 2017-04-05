#pragma once
#include "My_vector.h"
class FibonacciGenerator
{
public:
    class iterator : public std::iterator<std::forward_iterator_tag, int>
    {
    private:
        int _a, _b;
        int _i;
    public:
        iterator(int a, int b, int i) :
            _a(a),
            _b(b),
            _i(i)
        {}

        iterator operator ++()
        {
            int c = _a + _b;
            _a = _b;
            _b = c;
            ++_i;
            return *this;
        }

        int& operator *()
        {
            return _b;
        }

        bool operator !=(const iterator& rhs) const
        {
            return _i != rhs._i;
        }

        difference_type operator - (const iterator& rhs) const
        {
            return rhs._i - _i;
        }
    };

    FibonacciGenerator(int n) :
        _n(n)
    {}

    iterator begin() const
    {
        return iterator(0, 1, 0);
    }

    iterator end() const
    {
        return iterator(0, 0, _n);
    }
private:
    int _n;
};
#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class MyUniquePtr
{
public:
    MyUniquePtr() :
        _data(nullptr)
    {}

    MyUniquePtr(T* data) :
        _data(data)
    {}

    MyUniquePtr(const MyUniquePtr& p) = delete;

    MyUniquePtr(MyUniquePtr&& p) :
        _data(nullptr)
    {
        swap(p);
    }

    ~MyUniquePtr()
    {
        delete _data;
    }

    T& operator *() const
    {
        return *_data;
    }

    T& operator = (const MyUniquePtr& p) = delete;

    T& operator = (MyUniquePtr&& p)
    {
        swap(p);
    }

    void reset(T* data)
    {
        delete _data;
        _data = data;
    }

    void swap(MyUniquePtr& p)
    {
        std::swap(_data, p._data);
    }

private:
    T* _data;
};

int* create_int(int value)
{
    return new int(value);
}

void use_unique(MyUniquePtr<int> ppp)
{
    cout << *ppp;
}

int sum_integers()
{
    int result = 0;
    for (int i = 0; i < 5; ++i)
    {
        std::unique_ptr<int> ptr(create_int(i));
        result += *ptr;
    }
    return result;
}

int main()
{
    MyUniquePtr<int> ptr(create_int(5));
    return 0;
}

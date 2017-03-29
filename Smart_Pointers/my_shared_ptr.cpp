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

struct Node;
using Node_ptr = MySharedPtr<Node>;

struct Node
{
    int data;
    Node_ptr next;

    Node() :
        data(0)
    {
        cout << "Node " << data << " created\n";
    }

    ~Node()
    {
        cout << "Node " << data << " deleted\n";
    }
};

void delete_even(Node_ptr head)
{
    for(Node* cur = head.get(); cur; cur = cur->next.get())
        if (cur->next)
            cur->next = cur->next->next;
}

Node_ptr create_list(std::size_t size)
{
    Node_ptr head;
    for (std::size_t i = 0; i < size; ++i)
    {
        Node_ptr n = Node_ptr(new Node());
        n->data = size - i;
        n->next = head;
        head = n;
    }
    return head;
}

void print_list(Node_ptr head)
{
    for(Node* cur = head.get(); cur; cur = cur->next.get())
        cout << cur->data << ' ';
    cout << endl;
}

int main()
{
    Node_ptr head = create_list(10);
    Node_ptr second = head->next;

    print_list(head);
    delete_even(head);
    print_list(head);
    return 0;
}

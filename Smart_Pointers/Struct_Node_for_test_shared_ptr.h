#ifndef _NODE_H_
#define _NODE_H_

#include "My_shared_ptr.h"

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
    for (Node* cur = head.get(); cur; cur = cur->next.get())
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
    for (Node* cur = head.get(); cur; cur = cur->next.get())
        cout << cur->data << ' ';
    cout << endl;
}

#endif //! _NODE_H_
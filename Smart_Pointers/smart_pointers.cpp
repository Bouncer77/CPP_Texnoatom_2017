#include <memory>
#include <iostream>

using namespace std;

struct Node
{
    int data;
    std::shared_ptr<Node> next;

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

using Node_ptr = std::shared_ptr<Node>;

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
        auto n = std::make_shared<Node>();
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
    std::weak_ptr<Node> second = head->next;

    print_list(head);
    cout << (second.expired() ? "true" : "false") << endl;

    delete_even(head);
    print_list(head);
    cout << (second.expired() ? "true" : "false") << endl;
}

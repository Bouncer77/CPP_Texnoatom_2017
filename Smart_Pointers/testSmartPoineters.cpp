#include "My_unique_ptr_for_item.h"
#include "My_unique_ptr_for_mas.h"
#include "My_intrusive_ptr.h"
#include "Struct_Node_for_test_shared_ptr.h"
#include "Node.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    // Test MY_UNIQUE_PTR
    MyUniquePtr<int> ptr(create_int(5));

    //Test INTRUSIVE_PTR
    Node_ptr head = create_list(10);
    Node_ptr second = head->next;

    print_list(head);
    delete_even(head);
    print_list(head);

    //Test SHARED_PTR
    Node_ptr head = create_list(10);
    Node_ptr second = head->next;

    print_list(head);
    delete_even(head);
    print_list(head);

    //Test Smart_Pointer in My_Vector
    FibonacciGenerator g(10);
    print(g.begin(), g.end());
    cout << endl;

    MyVector<int> a(10);
    std::copy(g.begin(), g.end(), a.begin());
    print(a.begin(), a.end());
    cout << endl;

    for (int t : FibonacciGenerator(5))
        cout << t << endl;

    system("pause");
    return 0;
}
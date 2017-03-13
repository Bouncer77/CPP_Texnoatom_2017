#include <iostream>
#include "MyArray.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    /*MyArray<int, 5> aa = {1, 2, 3, 4, 5};
    aa.myPrintArray();*/

    MyArray<int, 5> bb;
    std::cout << "Array пуст? " << bb.empty() << std::endl;
    bb.push_back(1);
    bb.push_back(2);
    bb.push_back(3);
    bb.dump();

    std::cout << "Array пуст? " << bb.empty() << std::endl;

    std::cout << bb.capacity() << "    " << bb.front() << "     " << bb.back() << std::endl;

    system("pause");
    return 0;
}
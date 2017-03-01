//-----------------------------------------
//! @file StackTest.cpp
//! Tests a stack class
//!
//! @autor Kosenkov Ivan, 2017
//-----------------------------------------
#include <iostream>
#include "Stack.h"
using namespace std;
using namespace Stacks;
//-----------------------------------------
//! A simple unit_test
//! @param condition is a test expr
//-----------------------------------------

//#define TEST( condition ) \
//	if (! (condition))	  \
//		cout << "Тест провален" #condition);



//------------------------------------------
//! main
//------------------------------------------
int main()
{
	setlocale(LC_ALL, "Russian");

	Stack a;
	cout << a;

	a.push("Привет я 1");
	a.push("Привет я 2");
	a.push("Привет я 3");
	cout << a;

	cout << "Размер стека :" << a.size() << endl;

	if (a.empty() == true)
		cout << "Стек пуст" << endl;
	else
		cout << "В стеке есть элементы" << endl;

	cout << "Прочитать верхушку стека" << endl;
	cout << a.top() << endl;

	cout << "\n\n Вывести стек на экран: " << endl;
	cout << a;

	cout << "Убрать один элемент стека" << endl;
	a.pop();
	cout << a;

	// то же самое что и push (но без Кирилицы =)  )
	cout << "Введите три элемента: (Без Кирилицы , т.к. тут у нас перегруженный оператор >> со стандартным потоком ввода" << endl;
	cin >> a;
	cin >> a;
	cin >> a;

	cout << "\n\n Вывести стек на экран: " << endl;
	cout << a;


	system("pause");
	return 0;
}
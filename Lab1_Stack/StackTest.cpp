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
//		cout << "���� ��������" #condition);



//------------------------------------------
//! main
//------------------------------------------
int main()
{
	setlocale(LC_ALL, "Russian");

	Stack a;
	cout << a;

	a.push("������ � 1");
	a.push("������ � 2");
	a.push("������ � 3");
	cout << a;

	cout << "������ ����� :" << a.size() << endl;

	if (a.empty() == true)
		cout << "���� ����" << endl;
	else
		cout << "� ����� ���� ��������" << endl;

	cout << "��������� �������� �����" << endl;
	cout << a.top() << endl;

	cout << "\n\n ������� ���� �� �����: " << endl;
	cout << a;

	cout << "������ ���� ������� �����" << endl;
	a.pop();
	cout << a;

	// �� �� ����� ��� � push (�� ��� �������� =)  )
	cout << "������� ��� ��������: (��� �������� , �.�. ��� � ��� ������������� �������� >> �� ����������� ������� �����" << endl;
	cin >> a;
	cin >> a;
	cin >> a;

	cout << "\n\n ������� ���� �� �����: " << endl;
	cout << a;


	system("pause");
	return 0;
}
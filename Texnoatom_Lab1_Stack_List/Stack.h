//-----------------------------------------
//! @file Stack.h
//! Implements a stack class
//!
//! @autor Kosenkov Ivan, 2017
//-----------------------------------------

//-----------------------------------------
//! Stack class
//-----------------------------------------

#ifndef STACK_H
#define STACK_H

#include <string>

namespace Stacks
{
	

	struct Stack_element
	{
		std::string *info;
		struct Stack_element *next;
	};

	class Stack // LIFO
	{
	public:
		// ������������
		Stack() : m_top(nullptr), m_size(0) {};
		Stack(const std::string &str);
		Stack(const Stack_element &a);

		// ����������
		~Stack();

		// �������� ������ ������
		//bool push(std::string &&value);
		void push(std::string value);
		void pop();
		std::string top() const;

		int size() const;
		bool empty() const;

		// �������� �� ������
		bool ok() const;
		bool dump() const;

		// ������������� ���������
		friend std::ostream & operator << (std::ostream &os, const Stack &r);
		friend std::istream & operator >> (std::istream &is, Stack &r);
		Stack operator =(const Stack &r);
		friend Stack operator +(const Stack &left, const Stack &right);
		const Stack operator[] (int num) const;

	private:
		int m_size;
		Stack_element* m_top;
	};
}


#endif STACK_H

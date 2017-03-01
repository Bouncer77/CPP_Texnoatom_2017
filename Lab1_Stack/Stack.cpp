//-----------------------------------------
//! @file Stack.cpp
//! Implementation methods and friend functions 
//!  of the class stack
//!
//! @autor Kosenkov Ivan, 2017
//-----------------------------------------

#include "Stack.h"
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;

//-----------------------------------------
//! Macro to test object integrity
//-----------------------------------------
#define ASSERT_OK()					\
	if (!ok())						\
	{								\
		dump();						\
		assert(!"Object is OK");	\
	}
//-----------------------------------------

namespace Stacks
{
	//-----------------------------------------
	//! Silent verifier
	//-----------------------------------------
	bool Stack::ok() const
	{
		//return size_ <= capacity_;
		return true;
	}
	
	//-----------------------------------------
	//! Dumper
	//-----------------------------------------
	bool Stack::dump() const
	{
		return true;
	}

	void Stack::push(std::string value)
	{
		ASSERT_OK(); // Entry verification

		Stack_element *ptr = new Stack_element;
		(*ptr).next = nullptr;

		std::string *str_ptr = new std::string;
		*str_ptr = value;

		(*ptr).info = str_ptr;
		(*ptr).next = m_top;
		m_top = ptr;
		++m_size;

		ASSERT_OK(); // Exit verification
	}

	void Stack::pop()
	{
		ASSERT_OK(); // Entry verification

		Stack_element *x = m_top;
		m_top = x->next;
		--m_size;

		ASSERT_OK(); // Exit verification
	}

	std::string Stack::top() const
	{
		ASSERT_OK(); // Entry verification

		std::string *p_str = m_top->info;

		ASSERT_OK(); // Exit verification
		return *p_str;
	}

	int Stack::size() const
	{
		return m_size;
	}

	bool Stack::empty() const
	{
		bool res = m_top ? true : false;
		return res;
	}

	std::ostream & operator << (std::ostream &os, const Stack &r)
	{
		Stack_element *x = r.m_top;
		std::string *ptr;
		while (x != nullptr)
		{
			ptr = x->info;
			os << *ptr << std::endl;
			x = x->next;
		}

		return os;
	}

	std::istream & operator >> (std::istream &is, Stack &r)
	{
		Stack_element *ptr = new Stack_element;
		ptr->next = nullptr;

		std::string *p_str = new std::string;
		is >> *p_str;
		ptr->info = p_str;

		ptr->next = r.m_top;
		r.m_top = ptr;

		++ r.m_size;

		return is;
	}	
}
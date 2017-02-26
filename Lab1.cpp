/* ------------------------------------
Author: Kosenkov Ivan
Email:  bouncer77rus@gmail.com
Date:	15.02.2017 22:12
----------------------------------- */
#include <iostream>
#include <string>
using namespace std;

bool test(const string &);

int main()
{
	setlocale(LC_ALL, "Russian");

	string str;

	cout << "¬ведите строку: " << endl;
	cin >> str;
	if (test(str) == true)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	system("pause");

	return 0;
}

bool test(const string &str)
{
	// 1 - {} , 2 - [], 3 - (), 4 - <>
	char a1 = '{', a2 = '}';
	char b1 = '[', b2 = ']';
	char c1 = '(', c2 = ')';
	char d1 = '<', d2 = '>';

	int aa1 = 0, aa2 = 0;
	int bb1 = 0, bb2 = 0;
	int cc1 = 0, cc2 = 0;
	int dd1 = 0, dd2 = 0;
	
	for (int i = 0; i < str.length(); ++i)
	{
		if (str[i] == a1)
			++aa1;
		if (str[i] == a2)
			++aa2;

		if (str[i] == b1)
			++bb1;
		if (str[i] == b2)
			++bb2;

		if (str[i] == c1)
			++cc1;
		if (str[i] == c2)
			++cc2;

		if (str[i] == d1)
			++dd1;
		if (str[i] == d2)
			++dd2;
	}

	if (aa1 == aa2)
	{
		if (bb1 == bb2)
			if (cc1 == cc2)
				if (dd1 == dd2)
					return true;							
	}

	return false;
}

#include "interval_tree.h"
#include <iostream>
using namespace std;

struct MIN{
	const string & operator()(const string &a, const string &b) const
	{
		if(a == "") return b;
		else if(b == "") return a;
		return (a <= b) ? a : b; 
	}
};
struct functor{
	bool operator()(const string &a, const string &b) const 
	{
		if(a == "") return false; // left
		else if(b == "") return true; // right
		return a <= b; // returns true (left) if a is minimum or false (right) if not 
	}
};
int main()
{
	interval_tree<string, MIN> T(50);
	T[5] = "interval";
	T[7] = "tree";
	T[8] = "is great";
	T[0] = "abc";
	
	cout << "minimum of [0,10] interval is \"" << T.query(0,10) <<"\""<< endl;
	cout << " and of [3,8] is \"" << T.query(3,8) <<"\"" << endl;
	
	cout << "let's change value 0 and 5\n";
	T[0] = "zero";
	T[5] = "zebra";
	cout << "minimum of [0,10] is \"" << T.query(0,10) <<"\""<< endl;
	cout << " and of [3,8] is \"" << T.query(3,8) <<"\"" << endl;
	
	cout << "sorted strings\n";
	int index;
	while(string(T[index = T.find(functor())]) != "")
	{
		cout << (string)T[index] << ", ";
		T[index] = "";
	}
	cout << endl;
	
}
/* OUTPUT
	minimum of [0,10] interval is "abc"
	and of [3,8] is "interval"
	let's change value 0 and 5
	minimum of [0,10] is "is great"
	and of [3,8] is "is great"
	sorted strings
	is great, tree, zebra, zero,
*/

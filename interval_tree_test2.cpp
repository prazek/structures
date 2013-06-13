#include "interval_tree.h"
#include <iostream>
using namespace std;

struct MAX{
	int operator()(int a, int b) const
	{
		return max(a,b);
	}
};
bool fun(int a, int b) 
{
	return a >= b;
}



int main()
{
	int v[] = {1,5,15,3,2,15,2,15,3,7};
	interval_tree<int, MAX> t(v, v + sizeof(v)/sizeof(int)); //MAX tree
	
	cout << "maximum of [0,10] interval = " << t.query(0,10) << endl;
	cout << "maximum of [3,4] interval = " << t.query(3,4) << endl;
	
	t[4] = 20;
	
	cout << "after changing value [4]\n";
	cout << "maximum of [0,10] interval = " << t.query(0,10) << endl;
	cout << "maximum of [3,4] interval = " << t.query(3,4) << endl;
	
	cout << "let's find out where are biggest numbers!\n";
	
	while( t[t.find(fun)] != 0)
	{
		int index = t.find(fun);
		cout << "the biggest number now is " << t[index] << " at " << index << endl;
		t[index] = 0;
	}
	
}
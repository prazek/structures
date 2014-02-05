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
/* Output
	maximum of [0,10] interval = 15
	maximum of [3,4] interval = 3
	after changing value [4]
	maximum of [0,10] interval = 20
	maximum of [3,4] interval = 20
	let's find out where are biggest numbers!
	the biggest number now is 20 at 4
	the biggest number now is 15 at 2
	the biggest number now is 15 at 5
	the biggest number now is 15 at 7
	the biggest number now is 7 at 9
	the biggest number now is 5 at 1
	the biggest number now is 3 at 3
	the biggest number now is 3 at 8
	the biggest number now is 2 at 6
	the biggest number now is 1 at 0
	*/

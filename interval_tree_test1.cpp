#include "interval_tree.h"
#include <iostream>
using namespace std;

int main()
{
	int v[] = {1,5,15,3,2,15,2,15,3,7};
	interval_tree<int, plus<int> > t(v, v + sizeof(v)/sizeof(int));
	
	cout << t.query(0,3) << endl; //sum <0,4>
	
	t[2] -= 10;
	
	cout << t.query(0,3) << endl;
	cout << "t[2] = " << t[2] << 
	" is the same as t.query(2,2) = " << t.query(2,2) << endl;
	
	cout <<"before clearing sum = " << t.query(0,t.size()-1) << endl;
	t.set_values(0);
	cout << "after clearing sum = " << t.query(0, t.size()-1) << endl;
	
}
/* OUTPUT
	24
	14
	t[2] = 5 is the same as t.query(2,2) = 5
	before clearing sum = 58
	after clearing sum = 0
*/
#include "interval_tree.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	int v[] = {1,5,15,3,2,15,2,15,3,7};
	interval_tree<int, plus<int> > t(v, v + sizeof(v)/sizeof(int));
	
	assert(t.query(0,3) == 24); //sum [0,4]
	
	t[2] -= 10;
	
	assert(t.query(0,3) == 14);
	assert(t[2] == 5);
    assert(t.query(2, 2) == 5);
	
	assert(t.query(0,t.size() - 1) == 58);
	assert(t.query() == 58);
	t.set_values(0);
	assert(t.query(0, t.size()-1) == 0);
	
}

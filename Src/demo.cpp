#include <iostream>
#include "common.h"
#include "types.h"
#include "mmath.h"
#include "mmath.cpp"

using std::cout;
using std::endl;
using mmath::Sort;
	
int main()
{
	double a[10] = {8.1, 4.7, 7.0, 6.9, 1, 9.2, 0, 3.3, 77, 10.01};
	Sort<double> d64Sort;

	d64Sort.quick_sort(a,0,9);
	
	cout<<"after quick_sort:"<<endl;

	for(int i = 0; i < 10; i++)
	{
		cout<<"No "<<i<<": "<<a[i]<<endl;
	}
	return 0;
}

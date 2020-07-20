#include <iostream>
#include "common.h"
#include "types.h"
#include "mmath.cpp"


using std::cout;
using std::endl;
using mmath::Sort;
	
int main()
{
	sint32 size = 0;
	sf8 a[11] = {0.1, 8.1, -4.7, 1, 6.9, 1, 9.2, 0, 3.3, -77, 10.01};
	Sort<sf8> sf8Sort(TRUE);

	//sf8Sort.quick_sort(a,0,10);
	sf8Sort.insert_sort(a,0,10);
	
	cout<<"after sort:"<<endl;

	for(int i = 0; i < sizeof(a)/sizeof(sf8); i++)
	{
		cout<<"No "<<i<<": "<<a[i]<<endl;
	}
	return 0;
}

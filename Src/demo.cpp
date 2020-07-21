#include <iostream>
#include "common.h"
#include "types.h"
#include "mmath.cpp"


using std::cout;
using std::endl;
using mmath::Sort;
	
int main()
{
	sf8 a1[11] = {0.1, 8.1, -4.7, 1, 6.9, 1, 9.2, 0, 3.3, -77, 10.01};
	sf8 a2[3] = {0.1, 8.1, -4.7};
	sf8 a3[2] = {0.1, -4.7};
	Sort<sf8> sf8Sort(TRUE);

#if 0
	sf8Sort.quick_sort(a1,0,10);
	sf8Sort.quick_sort(a2,0,2);
	sf8Sort.quick_sort(a3,0,1);

#elif 0
	sf8Sort.insert_sort(a1,0,10);
	sf8Sort.insert_sort(a2,0,2);
	sf8Sort.insert_sort(a3,0,1);

#elif 1
	sf8Sort.shell_sort(a1,0,10);
	sf8Sort.shell_sort(a2,0,2);
	sf8Sort.shell_sort(a3,0,1);

#endif

	cout<<"--after sort, a1:"<<endl;
	for(int i = 0; i < sizeof(a1)/sizeof(sf8); i++)
	{
		cout<<"\tNo "<<i<<": "<<a1[i]<<endl;
	}
	cout<<"\n--after sort, a2:"<<endl;
	for(int i = 0; i < sizeof(a2)/sizeof(sf8); i++)
	{
		cout<<"\tNo "<<i<<": "<<a2[i]<<endl;
	}
	cout<<"\n--after sort, a3:"<<endl;
	for(int i = 0; i < sizeof(a3)/sizeof(sf8); i++)
	{
		cout<<"\tNo "<<i<<": "<<a3[i]<<endl;
	}

	return 0;
}

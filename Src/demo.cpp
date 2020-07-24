#include <iostream>
#include "common.h"
#include "types.h"
#include "mmath.cpp"


using std::cout;
using std::endl;
using mmath::Sort;
	
int main()
{
	sf8 a1[20] = {0.1, 8.1, -4.7, 1, 6.9, 1, 9.2, 0, 3.3, -77, 10.01, -0.1, 2, 65, -4.7, 200, -7, 4, -6.9, -6.9};
	sf8 a2[3] = {0.1, 8.1, -4.7};
	sf8 a3[2] = {0.1, -4.7};
	//sint32 num_of_tested_arrays = 3;
	Sort<sf8> sf8Sort(TRUE);

#if 0
	sf8Sort.quick_sort(a1,0,19);
	sf8Sort.quick_sort(a2,0,2);
	sf8Sort.quick_sort(a3,0,1);

#elif 0
	sf8Sort.insert_sort(a1,0,19);
	sf8Sort.insert_sort(a2,0,2);
	sf8Sort.insert_sort(a3,0,1);

#elif 0
	sf8Sort.shell_sort(a1,0,19);
	sf8Sort.shell_sort(a2,0,2);
	sf8Sort.shell_sort(a3,0,1);

#elif 0
	sf8Sort.bubble_sort(a1,0,19);
	sf8Sort.bubble_sort(a2,0,2);
	sf8Sort.bubble_sort(a3,0,1);

#elif 0
	sf8Sort.heap_sort(a1,0,19);
	sf8Sort.heap_sort(a2,0,2);
	sf8Sort.heap_sort(a3,0,1);

#elif 1
	sf8Sort.merge_sort(a1,0,sizeof(a1)/sizeof(sf8)-1);
	sf8Sort.merge_sort(a2,0,sizeof(a2)/sizeof(sf8)-1);
	sf8Sort.merge_sort(a3,0,sizeof(a3)/sizeof(sf8)-1);

#endif


	cout<<"--The sort result is "<<(sf8Sort.test(a1,0,sizeof(a1)/sizeof(sf8)-1)==TRUE?"OK!":"FAILED!")<<endl;
	for(int i = 0; i < sizeof(a1)/sizeof(sf8); i++)
	{
		cout<<"\tNo "<<i<<": "<<a1[i]<<endl;
	}
	cout<<"--The sort result is "<<(sf8Sort.test(a2,0,sizeof(a2)/sizeof(sf8)-1)==TRUE?"OK!":"FAILED!")<<endl;
	for(int i = 0; i < sizeof(a2)/sizeof(sf8); i++)
	{
		cout<<"\tNo "<<i<<": "<<a2[i]<<endl;
	}
	cout<<"--The sort result is "<<(sf8Sort.test(a3,0,sizeof(a3)/sizeof(sf8)-1)==TRUE?"OK!":"FAILED!")<<endl;
	for(int i = 0; i < sizeof(a3)/sizeof(sf8); i++)
	{
		cout<<"\tNo "<<i<<": "<<a3[i]<<endl;
	}

	return 0;
}

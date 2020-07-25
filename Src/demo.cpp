#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "common.h"
#include "types.h"
#include "mmath.cpp"

using std::make_pair;
using std::pair;
using std::multimap;
using std::cout;
using std::endl;
using std::string;
using mmath::Sort;
	
int main()
{
	sf8 a1[20] = {0.1, 8.1, -4.7, 1, 6.9, 1, 9.2, 0, 3.3, -77, 10.01, -0.1, 2, 65, -4.7, 200, -7, 4, -6.9, -6.9};
	sf8 a2[3] = {0.1, 8.1, -4.7};
	sf8 a3[2] = {0.1, -4.7};
	multimap<string, pair<sf8*, sint32> > arrays;
	multimap<string, pair<sf8*, sint32> >::iterator iter;
	Sort<sf8> sf8Sort(TRUE);
	uint32 test_result = FALSE;

	arrays.insert(make_pair("a1", make_pair(a1, 20)));
	arrays.insert(make_pair("a2", make_pair(a2, 3)));
	arrays.insert(make_pair("a3", make_pair(a3, 2)));

	for (iter = arrays.begin(); iter != arrays.end(); iter++){
		//打印待排序数组相关信息
		cout << iter->first << ", addr: " << (iter->second).first << ", array size: " << (iter->second).second << endl;
		//进行排序
		sf8Sort.merge_sort((iter->second).first, 0, (iter->second).second-1);
		//对排序结果进行检验
		test_result = sf8Sort.test((iter->second).first, 0, (iter->second).second-1);
		//输出检验结果
		if(test_result==TRUE){
			cout<<"Sort of array "<<iter->first<<" complete successfully!"<<endl<<endl;
		}else{
			cout<<"Sort of array "<<iter->first<<" FAILED!"<<endl;
			for(sint32 i=0; i<(iter->second).second; i++){
				cout<<"["<<i<<"]: "<<(iter->second).first[i]<<endl;
			}
			break;  //一旦出错，立即停止
		}
		
	}
	return 0;
}

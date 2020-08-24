#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "common.h"
#include "types.h"
#include "mmath.cpp"
#include "mgeometry.cpp"

using std::make_pair;
using std::pair;
using std::multimap;
using std::cout;
using std::endl;
using std::string;
using mmath::Sort;
using mgeometry::Point;
using mgeometry::Line;

int main()
{
	sf8 a1[20] = {0.1, 8.1, -4.7, 1, 6.9, 9.2, 0, 3.3, 1, -77, 10.01, -0.1, 2, 65, -4.7, 200, -7, 4, -6.9, -6.9};
	sf8 a2[3] = {0.1, 8.1, 9};
	sf8 a3[6] = {0.1, 8.1, -4.7, 1, 6.9, 9.2};
	multimap<string, pair<sf8*, sint32> > arrays;
	multimap<string, pair<sf8*, sint32> >::iterator iter;
	Sort<sf8> sf8Sort(TRUE);
	uint32 test_result = FALSE;
	Point<sf8> p1;
	Point<sf8> p2(1,1);
	Point<sf8> p3(0,1);
	Point<sf8> p4(1,0);
	Line<sf8> l1(p1,p2);
	Line<sf8> l2;
	l2 = l1;
	cout<<p1<<endl;
	cout<<p2<<endl;
	cout<<l1<<endl;
	if(l1 == l2){
		cout<<"Two lines are same!\n";
	}
	cout<<"p1.distance_to_line(p2) "<<p1.distance_to_point(p2)<<endl;
	cout<<"p3.distance_to_line(l1) "<<p3.distance_to_line(l1)<<",p3.distance_to_line_ex(l1) "<<p3.distance_to_line_ex(l1)<<endl;
	cout<<"p4.distance_to_line(l1) "<<p4.distance_to_line(l1)<<",p4.distance_to_line_ex(l1) "<<p4.distance_to_line_ex(l1)<<endl;
#if 0
	arrays.insert(make_pair("a1", make_pair(a1, 20)));
	arrays.insert(make_pair("a2", make_pair(a2, 3)));
	arrays.insert(make_pair("a3", make_pair(a3, 6)));

	for (iter = arrays.begin(); iter != arrays.end(); iter++){
		//打印待排序数组相关信息
		cout << iter->first << ", addr: " << (iter->second).first << ", array size: " << (iter->second).second << endl;
		//进行排序
		sf8Sort.bitree_sort((iter->second).first, 0, (iter->second).second-1);
		#if 0
		//对排序结果进行检验
		test_result = sf8Sort.test((iter->second).first, 0, (iter->second).second-1);
		//输出检验结果
		if(test_result==OK){
			cout<<"Sort of array "<<iter->first<<" complete successfully!"<<endl<<endl;
		}else{
			cout<<"Sort of array "<<iter->first<<" FAILED!"<<endl;
			for(sint32 i=0; i<(iter->second).second; i++){
				cout<<"["<<i<<"]: "<<(iter->second).first[i]<<endl;
			}
			break;  //一旦出错，立即停止
		}
		#endif
	}
#endif
	return 0;
}

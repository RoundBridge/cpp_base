/******************************************************************************
FileName: 		mmath.cpp
Description:   	math definition
Author:   		Round Bridge
Date: 			2020.1.17
Modification History:
					2020.1.17 create file
Version: 		0.0.1
******************************************************************************/


#include "types.h"
#include "mmath.h"
#include <iostream>
using std::cout;
using std::endl;

namespace mmath
{
	template <class Type_Tools>
	void Tools<Type_Tools>::swap(Type_Tools *pdata, sint32 i, sint32 j) {
		Type_Tools temp = pdata[i];
		pdata[i] = pdata[j];
		pdata[j] = temp;
		return;
	}


	template <class Type_Sort>
	uint Sort<Type_Sort>::is_reverse(){
		return (reverse != FALSE);
	}

	
	template <class Type_Sort>
	sint32 Sort<Type_Sort>::partition(Type_Sort *pdata, sint32 left, sint32 right){
		sint32 pivot = left;
		sint32 index = pivot+1;
		sint32 i = index;
		uint reverse = is_reverse();

		/* this loop make sure numbers on the left of index is less than  pdata[pivot] */
		for(; i <= right; i++){
			if(FALSE == reverse){
				if(pdata[i] < pdata[pivot]){
					this->swap(pdata, i, index);
					index++;
				}
			}
			else{
				if(pdata[i] > pdata[pivot]){
					this->swap(pdata, i, index);
					index++;
				}
			}
		}
		/* here let the pivot element to its right place */
		this->swap(pdata, pivot, index-1);
		pivot = index-1;
		return pivot;
	}



	template <class Type_Sort>
	void Sort<Type_Sort>::quick_sort(Type_Sort *pdata, sint32 left, sint32 right){				
		if (left >= right) {
			return;	
		}
		
		sint32 divide = partition(pdata, left, right);	
		quick_sort(pdata, left, divide - 1);	
		quick_sort(pdata, divide + 1, right);
		return;
	}



	template <class Type_Sort>
	void Sort<Type_Sort>::insert_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;	
		}
		sint32 i, j, index;
		uint reverse = is_reverse();

		for(j = left + 1; j <= right; j++){
			index = j;
			for(i = j - 1; i >= left; i--){
				if(reverse)
				{
					if(pdata[index] > pdata[i]){
						this->swap(pdata, i, index);
						index = i;
					}
				}else{				
					if(pdata[index] < pdata[i]){
						this->swap(pdata, i, index);
						index = i;
					}
				}
			}
		}
		return;
	}



	template <class Type_Sort>
	void Sort<Type_Sort>::shell_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;	
		}
		sint32 i, j, step, index, k;
		uint reverse = is_reverse();

		step = (right - left + 1) / 2;
		while(step >= 1){
			for(k = 0; k < step; k++){
				/* this inner two loops is a insert sort */
				for(j = k +  step; j <= right; j += step){
					index = j;
					for(i = j - step; i >= left; i -= step){
						if(reverse){
							if(pdata[index] > pdata[i]){
								this->swap(pdata, i, index);
								index = i;
							}
						}else{
							if(pdata[index] < pdata[i]){
								this->swap(pdata, i, index);
								index = i;
							}
						}					
					}			
				}			
			}
			step /= 2;
		}

		return;
	}

	template <class Type_Sort>
	void Sort<Type_Sort>::bubble_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;
		}
		sint32 i, right_edge;
		uint reverse = is_reverse();

		for(right_edge = right; right_edge > left; right_edge--){
			for(i = left; i < right_edge; i++){
				if(reverse){
					if(pdata[i] < pdata[i+1]){
						this->swap(pdata, i, i+1);
					}
				}else{
					if(pdata[i] > pdata[i+1]){
						this->swap(pdata, i, i+1);
					}
				}
			}
		}
		return;
	}

	/*
		基于父节点和左右孩子创建包含三个元素的大顶堆
	*/
	template <class Type_Sort>
	void Sort<Type_Sort>::create_heap(Type_Sort *pdata, sint32 index, sint32 size){
		sint32 largest = index;
		sint32 smallest= index;
		sint32 temp    = index;	
		sint32 right, left;
		uint reverse = is_reverse();

		right = index * 2 + 2;  // index 结点的右孩子(如果有)
		left  = index * 2 + 1;  // index 结点的左孩子

		// find the largest element in this triple set
		if((right < size) && (pdata[largest] < pdata[right])){
			largest = right;
		}
		if((left < size) && (pdata[largest] < pdata[left])){
			largest = left;
		}

		// find the smallest element in this triple set
		if((right < size) && (pdata[smallest] > pdata[right])){
			smallest = right;
		}
		if((left < size) && (pdata[smallest] > pdata[left])){
			smallest = left;
		}

		if(reverse){
			temp = smallest;
		}else{
			temp = largest;
		}
		
		if(temp != index){
			this->swap(pdata, temp, index);
			//由于改变了位置，所以会影响到下面已经创建
			//好的大顶堆，因此需递归调整下面的堆
			create_heap(pdata, temp, size);
		}
			
		return;
		
	}

	template <class Type_Sort>
	void Sort<Type_Sort>::heap_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;
		}
		sint32 i;
		Type_Sort *pdata_temp = pdata + left;  //支持子数组排序
		sint32 size = right - left + 1;
		//根节点索引为0，则最后一个非叶子结点的索引为size/2-1		

		//创建整棵树的大顶堆
		for(i = size/2-1; i >= 0; i--){
			create_heap(pdata_temp, i, size);
		}

		// 交换堆顶和当前末尾的节点，重置大顶堆
		for(; size > 1;){
			this->swap(pdata_temp, 0, size-1);  //支持子数组排序
			size--;
			create_heap(pdata_temp, 0, size);
		}
		return;		
	}


	template <class Type_Sort>
	void Sort<Type_Sort>::merge(Type_Sort *pdata, sint32 left, sint32 mid, sint32 right){
		Type_Sort *backup = new Type_Sort[right - left + 1];
		uint reverse = is_reverse();
		sint32 i, j, index;

		for(i=left, j=mid+1, index=0; i<=mid && j<=right; ){
			if(reverse){
				backup[index++] = pdata[i]<pdata[j]?pdata[j++]:pdata[i++];
			}else{
				backup[index++] = pdata[i]>pdata[j]?pdata[j++]:pdata[i++];
			}					
		}

		//下面两个while 循环每次只可能运行一个
		while(i<=mid){
			backup[index++] = pdata[i++];
		}
		while(j<=right){
			backup[index++] = pdata[j++];
		}

		for(i=0; i<=right-left; i++){
			pdata[left+i] = backup[i];
		}
		
		delete [] backup;
		
		return;
	}

	template <class Type_Sort>
	void Sort<Type_Sort>::merge_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (right - left < 1 || left > right) {
			return;
		}

		sint32 mid = left + (right - left)/2;

		merge_sort(pdata, left, mid);
		merge_sort(pdata, mid+1, right);
		merge(pdata, left, mid, right);

		return;
	}


	template <class Type_Sort>
	void Sort<Type_Sort>::select_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;
		}
		uint reverse = is_reverse();
		sint32 i, j, temp;
		
		for(j = left; j <= right; j++){
			temp = j; 
			for(i = temp + 1; i <= right; i++){
				if(reverse){
					if(pdata[temp] < pdata[i]){
						temp = i;
					}
				}else{
					if(pdata[temp] > pdata[i]){
						temp = i;
					}
				}
			}
			this->swap(pdata, temp, j);
		}
		return;
	}
	

	template <class Type_Sort>
	uint32 Sort<Type_Sort>::test(Type_Sort *pdata, sint32 left, sint32 right){
		uint reverse = is_reverse();
		sint32 i;
		uint32 ret = TRUE;
		
		for(i=left; i<right; i++){
			if(reverse){
				if(pdata[i]<pdata[i+1]){
					cout<<"[class Sort] ERROR! REVERSE SORT FAILED! No."<<i<<": "<<pdata[i]<<",\tNo."<<i+1<<": "<<pdata[i+1]<<endl;
					ret = FALSE;
					break;
				}
			}else{
				if(pdata[i]>pdata[i+1]){
					cout<<"[class Sort] ERROR! SORT FAILED! No."<<i<<": "<<pdata[i]<<",\tNo."<<i+1<<": "<<pdata[i+1]<<endl;
					ret = FALSE;
					break;
				}
			}

		}
		return ret;
	}








	
}

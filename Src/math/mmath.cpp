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
	sint32 Sort<Type_Sort>::partition(Type_Sort *pdata, sint32 left, sint32 right){
		sint32 pivot = left;
		sint32 index = pivot+1;
		sint32 i = index;

		/* this loop make sure numbers on the left of index is less than  pdata[pivot] */
		for(; i <= right; i++){
			if(pdata[i] < pdata[pivot]){
				this->swap(pdata, i, index);
				index++;
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


}

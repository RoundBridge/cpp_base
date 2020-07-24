/******************************************************************************
FileName: 		mmath.h
Description:   	header file
Author:   		Round Bridge
Date: 			2020.1.17
Modification History:
					2020.1.17 create file
Version: 		0.0.1
******************************************************************************/


#ifndef _MMATH_H_
#define _MMATH_H_

#include "types.h"

namespace mmath
{
	template <class Type_Tools>
	class Tools{
	public:
		Tools(){}
		virtual ~Tools(){}
		void swap(Type_Tools *pdata, sint32 i, sint32 j);
	};


	template <class Type_Sort>
	class Sort : public Tools<Type_Sort>{
	public:
		Sort():Tools<Type_Sort>(){reverse=FALSE;}
		// if output in the order of bigger to smaller, set flag to TRUE
		Sort(uint flag):Tools<Type_Sort>(){reverse=flag;}		
		virtual ~Sort(){}		
		void quick_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void insert_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void shell_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void bubble_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void heap_sort(Type_Sort *pdata, sint32 left, sint32 right);		
		void merge_sort(Type_Sort *pdata, sint32 left, sint32 right);		
		uint32 test(Type_Sort *pdata, sint32 left, sint32 right);
		/*				
		void select_sort(Type *root, int size);
		Type *binary_search(Type *root, int size, Type *s);	
		*/
		
	private:
		uint reverse;		
		uint is_reverse();
		sint32 partition(Type_Sort *pdata, sint32 left, sint32 right);
		void create_heap(Type_Sort *pdata, sint32 index, sint32 size);
		void merge(Type_Sort *pdata, sint32 left, sint32 mid, sint32 right);
	};		
	



}






#endif


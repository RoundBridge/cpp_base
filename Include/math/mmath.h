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
		uint is_reverse();
		sint32 partition(Type_Sort *pdata, sint32 left, sint32 right);
		void quick_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void insert_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void shell_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void bubble_sort(Type_Sort *pdata, sint32 left, sint32 right);
		/*
		void adjust_heap(Type *root, int i, int size);		
		void create_heap(Type *root, int size);		
		void heap_sort(Type *root, int size);		
		void select_sort(Type *root, int size);						
		void merge_sort(Type *root, int l, int r);		
		void merge(Type *root, int l, int mid, int r);
		Type *binary_search(Type *root, int size, Type *s);	
		*/
	private:
		uint reverse;
	};		
	



}






#endif


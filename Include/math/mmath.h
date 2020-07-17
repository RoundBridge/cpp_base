
#ifndef _MMATH_H_
#define _MMATH_H_

#include "types.h"

namespace RoundBridge
{
	template <class Type>
	class sort {
	public:		
		//sort(sint32 (*cmp)(Type t1, Type t2));		
		//~sort(){}
		sint32 partition(Type *pdata, sint32 left, sint32 right);
		void quick_sort(Type *pdata, sint32 left, sint32 right);
		/*
		void adjust_heap(Type *root, int i, int size);		
		void create_heap(Type *root, int size);		
		void heap_sort(Type *root, int size);		
		void select_sort(Type *root, int size);		
		void shell_sort(Type *root, int size);				
		void merge_sort(Type *root, int l, int r);		
		void merge(Type *root, int l, int mid, int r);		
		void bubble_sort(Type *root, int size);		
		void insert_sort(Type *root, int size);		
		Type *binary_search(Type *root, int size, Type *s);	
		*/
	private:		
		//sint32 (*compare)(Type t1, Type t2);
	};



}






#endif


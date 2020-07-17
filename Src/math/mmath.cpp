#include "types.h"
#include "mmath.h"


namespace RoundBridge
{
#if 0
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

#endif
	template <class Type>
	void swap(Type *pdata, sint32 i, sint32 j) {
		Type temp = pdata[i];
		pdata[i] = pdata[j];
		pdata[j] = temp;
		return;
	}


	template <class Type>
	sint32 sort<Type>::partition(Type *pdata, sint32 left, sint32 right){
		sint32 pivot = left;
		sint32 index = pivot+1;
		sint32 i = index;

		/* this loop make sure numbers on the left of index is less than  pdata[pivot] */
		for(; i <= right; i++){
			if(pdata[i] < pdata[pivot]){
				swap(pdata, i, index);
				index++;
			}
		}
		/* here let the pivot element to its right place */
		swap(pdata, pivot, index-1);
		pivot = index-1;
		return pivot;
	}



	template <class Type>
	void sort<Type>::quick_sort(Type *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;	
		}	
		sint32 divide = partition(pdata, left, right);	
		quick_sort(pdata, left, divide - 1);	
		quick_sort(pdata, divide + 1, right);
		return;
	}


}

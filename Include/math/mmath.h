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
#include <vector>

using std::vector;

namespace mmath
{
	template <class Type_Tools>
	class Tools{
	public:
		Tools(){}
		virtual ~Tools(){}
		void swap(Type_Tools *pdata, sint32 i, sint32 j);
	};


	template <class Type_Bnode>
	class Bnode{
	public:
		Bnode(){data = (Type_Bnode)0; lchild = NULL; rchild = NULL; parent = NULL;}
		Bnode(Type_Bnode d){data = d; lchild = NULL; rchild = NULL; parent = NULL;}
		virtual ~Bnode(){}
		void set_data(Type_Bnode dat){data = dat;}
		Type_Bnode get_data(){return data;}
		Bnode *get_lchild(){return lchild;}
		Bnode *get_rchild(){return rchild;}
		Bnode *get_parent(){return parent;}
		void set_lchild(Bnode *addr){lchild = addr;}
		void set_rchild(Bnode *addr){rchild = addr;}
		void set_parent(Bnode *addr){parent = addr;}

	private:
		Bnode *parent;
		Type_Bnode data;
		Bnode *lchild;
		Bnode *rchild;
	};


	template <class Type_Btree>
	class Btree{
		public:
			Btree(){root = NULL;}
			Btree(Bnode<Type_Btree> *p){root = p;}
			virtual ~Btree(){}
			void set_root(Bnode<Type_Btree> *p){root = p;}
			Bnode<Type_Btree> *get_root(){return root;}
			Bnode<Type_Btree> *insert_node(Bnode<Type_Btree> *new_node);
			void traverse(Bnode<Type_Btree> *root, uint32 order); // 遍历顺序:前序0，中序1，后序2
			Bnode<Type_Btree> *find_node(Bnode<Type_Btree> *node);
			
		protected:
			Bnode<Type_Btree> *root;			
	};


	template <class Type_Bstree>
	class BStree: public Btree<Type_Bstree>{
	public:
		BStree():Btree<Type_Bstree>(){this->root = NULL;}
		BStree(Bnode<Type_Bstree> *p):Btree<Type_Bstree>(){this->root = p;}
		virtual ~BStree(){}
		state adjust_bstree(Bnode<Type_Bstree> *node);
		state delete_node(Bnode<Type_Bstree> *node);
		Bnode<Type_Bstree> *insert_node(Bnode<Type_Bstree> *new_node);
		Bnode<Type_Bstree> *insert_recursive(uint32 flag, Bnode<Type_Bstree> *root, Bnode<Type_Bstree> *parent_of_root, Bnode<Type_Bstree> *new_node);
	};

	
	/*
		class of sort, usage:
		1. Instantiate an object, i.e. Sort<T> sf8Sort, if you want to sort in a reverse order, then Sort<T> sf8Sort(TRUE).
		2. Pass the array to the sort method with the bounds of the array, sf8Sort.sort_method(array, left_ele_index, right_ele_index),
		sort_method stands for select_sort, quick_sort, insert_sort, shell_sort, bubble_sort, heap_sort, merge_sort.
		3. Support child array sort.
		4. To validate the result, use sf8Sort.test(array, left_ele_index, right_ele_index), TRUE for OK, FALSE the otherwise.
	*/
	template <class Type_Sort>
	class Sort : public Tools<Type_Sort>{
	public:
		Sort():Tools<Type_Sort>(){reverse=FALSE;}
		Sort(uint flag):Tools<Type_Sort>(){reverse=flag;}		
		virtual ~Sort(){}
		void select_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void quick_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void insert_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void shell_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void bubble_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void heap_sort(Type_Sort *pdata, sint32 left, sint32 right);		
		void merge_sort(Type_Sort *pdata, sint32 left, sint32 right);
		void bitree_sort(Type_Sort *pdata, sint32 left, sint32 right);
		uint32 test(Type_Sort *pdata, sint32 left, sint32 right);
		
	private:
		uint reverse;		
		uint is_reverse();
		sint32 partition(Type_Sort *pdata, sint32 left, sint32 right);
		void create_heap(Type_Sort *pdata, sint32 index, sint32 size);
		void merge(Type_Sort *pdata, sint32 left, sint32 mid, sint32 right);
		void get_data_from_bstree(Bnode<Type_Sort> *root, vector<Type_Sort> &sorted);
	};		
	



}






#endif


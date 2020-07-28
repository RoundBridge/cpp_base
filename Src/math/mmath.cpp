/******************************************************************************
FileName: 		mmath.cpp
Description:   	math definition
Author:   		Round Bridge
Date: 			2020.1.17
Modification History:
					2020.1.17 create file
Version: 		0.0.1
******************************************************************************/
#ifndef _MMATH_CPP_
#define _MMATH_CPP_


#include <iostream>
#include <deque>
#include <vector>
#include "types.h"
#include "mmath.h"

using std::cin;
using std::cout;
using std::endl;
using std::deque;
using std::vector;

namespace mmath
{
	template <class Type_Tools>
	void Tools<Type_Tools>::swap(Type_Tools *pdata, sint32 i, sint32 j) {
		Type_Tools temp = pdata[i];
		pdata[i] = pdata[j];
		pdata[j] = temp;
		return;
	}

	/*
		����˳��������£���������һ��һ������ڵ�
	*/
	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::insert_node(Bnode<Type_Btree> *new_node){
		deque<Bnode<Type_Btree> *> next_node;
		Bnode<Type_Btree> *node = NULL;

		if(NULL != new_node){
			new_node->set_lchild((Bnode<Type_Btree>*)NULL);
			new_node->set_rchild((Bnode<Type_Btree>*)NULL);
			new_node->set_parent((Bnode<Type_Btree>*)NULL);
		}else{
			cout<<"[class Btree] ERROR: NULL pointer input!"<<endl;
			return NULL;
		}
			
		if(NULL == this->get_root()){
			this->set_root(new_node);
			cout<<"[class Btree] Create a new bitree, insert the new node as the root node!"<<endl;
			return this->get_root();
		}else{
			node = this->get_root();
			while(NULL != node){
				if(NULL == node->get_lchild()){
					node->set_lchild(new_node);
					new_node->set_parent(node);
					return this->get_root();
				}else if(NULL == node->get_rchild()){
					node->set_rchild(new_node);
					new_node->set_parent(node);
					return this->get_root();
				}else{
					next_node.push_back(node->get_lchild());
					next_node.push_back(node->get_rchild());
					node = next_node.front();  //�������ж϶����е�һ��Ԫ�ص������������
					next_node.pop_front();  // ɾ����һ��Ԫ��
				}					
			}
		}
	}


	template <class Type_Btree>
	void Btree<Type_Btree>::traverse(Bnode<Type_Btree> *root, uint32 order){
		if(NULL == root){
			//cout<<"[class Btree] NO TREE TO TRAVERSE!"<<endl;
			return;
		}else{
			// ����˳��:ǰ��0������1������2
			if(0 == order){
				cout<<root->get_data()<<" ";
				traverse(root->get_lchild(), order);
				traverse(root->get_rchild(), order);
			}else if(1 == order){
				traverse(root->get_lchild(), order);
				cout<<root->get_data()<<" ";
				traverse(root->get_rchild(), order);
			}else{
				traverse(root->get_lchild(), order);
				traverse(root->get_rchild(), order);
				cout<<root->get_data()<<" ";
			}
			return;
		}
	}


	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::find_node(Bnode<Type_Btree> *node){
		deque<Bnode<Type_Btree> *> next_node;
		Bnode<Type_Btree> *temp = NULL;
		
		if(NULL == this->get_root()){
			cout<<"[class Btree] THE TREE IS NULL!"<<endl;
			return NULL;
		}else{
			temp = this->get_root();
			while(NULL != temp){
				if(temp->get_data() == node->get_data()){
					return temp;  // �ҵ��˸ýڵ�
				}else{
					if(NULL != temp->get_lchild()){next_node.push_back(temp->get_lchild());}
					if(NULL != temp->get_rchild()){next_node.push_back(temp->get_rchild());}
					if(next_node.size() > 0){
						temp = next_node.front();  //�������ж϶����е�һ��Ԫ�ص������������
						next_node.pop_front();	// ɾ����һ��Ԫ��
					}else{
						temp = NULL;
					}
				}
			}
			return NULL;  // �Ҳ����ýڵ�
		}
	}
	

	template <class Type_Bstree>
	Bnode<Type_Bstree>* BStree<Type_Bstree>::insert_recursive(uint32 flag, Bnode<Type_Bstree> *root, Bnode<Type_Bstree> *parent_of_root, Bnode<Type_Bstree> *new_node){
		if(NULL == root){  // ��ǰλ���ǿյģ����Բ���
			new_node->set_parent(parent_of_root);
			if(0 == flag){parent_of_root->set_lchild(new_node);}
			else{parent_of_root->set_rchild(new_node);}
			return new_node;
		}else{
			if(new_node->get_data() <= root->get_data()){
				insert_recursive(0, root->get_lchild(), root, new_node);
			}else{
				insert_recursive(1, root->get_rchild(), root, new_node);
			}
			return new_node;
		}		
	}


	template <class Type_Bstree>
	Bnode<Type_Bstree>* BStree<Type_Bstree>::insert_node(Bnode<Type_Bstree> *new_node){
		if(NULL != new_node){
			new_node->set_lchild((Bnode<Type_Bstree>*)NULL);
			new_node->set_rchild((Bnode<Type_Bstree>*)NULL);
			new_node->set_parent((Bnode<Type_Bstree>*)NULL);
		}else{
			cout<<"[class Bstree] ERROR: NULL pointer input!"<<endl;
			return NULL;
		}

		if(NULL == this->get_root()){
			this->set_root(new_node);
			cout<<"[class Bstree] Create a new bstree, insert the new node as the root node!"<<endl;
			return this->get_root();
		}else{
			if(new_node->get_data() <= this->get_root()->get_data()){
				insert_recursive(0, this->get_root()->get_lchild(), this->get_root(), new_node);
			}else{
				insert_recursive(1, this->get_root()->get_rchild(), this->get_root(), new_node);
			}
			return this->get_root();
		}
	}

	/*
	1.Ҫɾ���Ľڵ�ֻ�����ӣ���ô���øýڵ�ĸ��׽��ָ��
	�ýڵ�����ӣ�Ȼ��ɾ���ýڵ�
	2.Ҫɾ���Ľڵ�ֻ���Һ��ӣ���ô���øýڵ�ĸ��׽��ָ��
	�ýڵ���Һ��ӣ�Ȼ��ɾ���ýڵ�
	(�������������������Ӧ����֮ǰ����һ���жϣ������ж�
	����ڵ��Ƿ��Ǹ��ڵ㣬����Ǹ��ڵ�Ļ�����ֱ���ø��ڵ�
	ָ������ڵ�����ӻ��Һ��ӣ�Ȼ��ɾ������ڵ�)
	3.Ҫɾ���Ľڵ�����Һ��Ӷ�����:
		a.�ҵ��ýڵ���������е������ӣ�Ҳ���������������
		���ĵ�һ���ڵ�?
		b.������ֵ��Ҫɾ���Ľڵ��ֵ���н���
		c.Ȼ��ɾ������ڵ㼴�൱�ڰ�������ɾ���Ľڵ�ɾ����
	*/
	template <class Type_Bstree>
	state BStree<Type_Bstree>::adjust_bstree(Bnode<Type_Bstree> *node){
		Bnode<Type_Bstree> *root = this->get_root();
		Bnode<Type_Bstree> *temp = NULL, *replace = NULL;
		state ret = OK;
		
		if(NULL == root || NULL == node){
			cout<<"[class Bstree] NULL POINTER!"<<endl;
			return NULL_PTR;
		}
		
		if(NULL == node->get_lchild() && NULL == node->get_rchild()){ // ɾ���ڵ���Ҷ�ӽ��
			if(root == node){  // ͬʱ���Ǹ��ڵ�
				this->set_root(NULL);
			}else{
				if(node == node->get_parent()->get_lchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_parent()->set_lchild(NULL);
				}else if(node == node->get_parent()->get_rchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_parent()->set_rchild(NULL);
				}else{
					cout<<"[class Bstree] 1.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
			}
		}else if(NULL != node->get_lchild() && NULL == node->get_rchild()){ //ֻ������
			if(root == node){  // ͬʱ���Ǹ��ڵ�
				node->get_lchild()->set_parent(NULL);
				this->set_root(node->get_lchild());
			}else{
				if(node == node->get_parent()->get_lchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_lchild()->set_parent(node->get_parent());
					node->get_parent()->set_lchild(node->get_lchild());
				}else if(node == node->get_parent()->get_rchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_lchild()->set_parent(node->get_parent());
					node->get_parent()->set_rchild(node->get_lchild());
				}else{
					cout<<"[class Bstree] 2.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
			}
		}else if(NULL == node->get_lchild() && NULL != node->get_rchild()){ //ֻ���Һ���
			if(root == node){  // ͬʱ���Ǹ��ڵ�
				node->get_rchild()->set_parent(NULL);
				this->set_root(node->get_rchild());
			}else{
				if(node == node->get_parent()->get_lchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_rchild()->set_parent(node->get_parent());
					node->get_parent()->set_lchild(node->get_rchild());
				}else if(node == node->get_parent()->get_rchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_rchild()->set_parent(node->get_parent());
					node->get_parent()->set_rchild(node->get_rchild());
				}else{
					cout<<"[class Bstree] 3.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
			}
		}else{  //ɾ���ڵ�������ӣ������Һ���
			temp = node->get_rchild();
			while(temp){  //��ѭ���ҵ�ɾ���ڵ�������������ߵĽ�㣬�ýڵ��ֵ���ŵ�ɾ���ڵ��λ��
				replace = temp;
				temp = temp->get_lchild();
			}				
			if(replace == replace->get_parent()->get_lchild()){
				//�滻�ڵ����丸�ڵ������
				replace->get_parent()->set_lchild(replace->get_rchild());
			}else if(replace == replace->get_parent()->get_rchild()){
				//�滻�ڵ����丸�ڵ���Һ���
				//��������Ǵ��ڵ�:ɾ���ڵ����������ÿ���ڵ㶼ֻ��������
				replace->get_parent()->set_rchild(replace->get_rchild());
			}else{
				cout<<"[class Bstree] 4.REPLACE NODE ERROR!"<<endl;
				return PARAM_ERR;
			}
			if(replace->get_rchild()){
				replace->get_rchild()->set_parent(replace->get_parent());
			}
			else{
				//��ʱ��replace�ڵ���Ҷ�ӽ��	
			}
			node->set_data(replace->get_data());
			//if(root == node){}
			// ɾ���ڵ�ͬʱ���Ǹ��ڵ㣬����Ҫ������Ϊ��ʱ����Ϊ��			
		}
		return ret;
	}


	template <class Type_Bstree>
	state BStree<Type_Bstree>::delete_node(Bnode<Type_Bstree> *node){
		Bnode<Type_Bstree>* del_node = this->find_node(node);
		state ret = OK;
		
		if(NULL == del_node){
			cout<<"[class Bstree] NO SUCH NODE TO DELETE!"<<endl;
			return NULL_PTR;
		}else{
			ret = adjust_bstree(del_node);
			return ret;
		}
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
		���ڸ��ڵ�����Һ��Ӵ�����������Ԫ�صĴ󶥶�
	*/
	template <class Type_Sort>
	void Sort<Type_Sort>::create_heap(Type_Sort *pdata, sint32 index, sint32 size){
		sint32 largest = index;
		sint32 smallest= index;
		sint32 temp    = index;	
		sint32 right, left;
		uint reverse = is_reverse();

		right = index * 2 + 2;  // index �����Һ���(�����)
		left  = index * 2 + 1;  // index ��������

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
			//���ڸı���λ�ã����Ի�Ӱ�쵽�����Ѿ�����
			//�õĴ󶥶ѣ������ݹ��������Ķ�
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
		Type_Sort *pdata_temp = pdata + left;  //֧������������
		sint32 size = right - left + 1;
		//���ڵ�����Ϊ0�������һ����Ҷ�ӽ�������Ϊsize/2-1		

		//�����������Ĵ󶥶�
		for(i = size/2-1; i >= 0; i--){
			create_heap(pdata_temp, i, size);
		}

		// �����Ѷ��͵�ǰĩβ�Ľڵ㣬���ô󶥶�
		for(; size > 1;){
			this->swap(pdata_temp, 0, size-1);  //֧������������
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

		//��������while ѭ��ÿ��ֻ��������һ��
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
	void Sort<Type_Sort>::get_data_from_bstree(Bnode<Type_Sort> *root, vector<Type_Sort> &sorted){
		//if(NULL == root || NULL == sorted){} //�����ж������Ƿ�Ϊ��
		if(NULL == root){}
		else{
			get_data_from_bstree(root->get_lchild(), sorted);
			sorted.push_back(root->get_data());
			get_data_from_bstree(root->get_rchild(), sorted);
		}
		return;
	}

#if 1
	template <class Type_Sort>
	void Sort<Type_Sort>::bitree_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;
		}

		Type_Sort *pdata_temp = pdata + left;  // ֧��������
		BStree<Type_Sort> bstree;
		Bnode<Type_Sort> *node = new Bnode<Type_Sort>[right - left + 1];
		vector<Type_Sort> sorted;
		sint32 i, right_side = right - left;
		uint reverse = is_reverse();

		for(i=0; i<=right_side; i++){
			node[i].set_data(pdata_temp[i]);
			bstree.insert_node(&node[i]);
		}
		get_data_from_bstree(bstree.get_root(), sorted);
		for(i=0; i<=right_side; i++){
			if(reverse){
				pdata_temp[i] = sorted.at(right_side-i);
			}else{
				pdata_temp[i] = sorted.at(i);
			}
		}

		delete [] node;
		
		return;		
	}
#else
	template <class Type_Sort>
	void Sort<Type_Sort>::bitree_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;
		}
		state ret = OK;
		sint8 flag = 0;
		Type_Sort del_num;
		Type_Sort *pdata_temp = pdata + left;  // ֧��������
		BStree<Type_Sort> bstree;
		Bnode<Type_Sort> *node = new Bnode<Type_Sort>[right - left + 1];
		vector<Type_Sort> sorted;
		sint32 i, j = 0, right_side = right - left;
		uint reverse = is_reverse();

		for(i=0; i<=right_side; i++){
			node[i].set_data(pdata_temp[i]);
			bstree.insert_node(&node[i]);
		}
		get_data_from_bstree(bstree.get_root(), sorted);
		for(i=0; i<=right_side-j; i++){
			if(reverse){
				cout<<sorted.at(right_side-j-i)<<", ";
			}else{
				cout<<sorted.at(i)<<", ";
			}
		}
		sorted.clear();
		
		cout<<"\nIf you want to delete a number, press y, else press n.";
		cin>>flag;
		while(flag == 'y'){
			cout<<"\nPlease input the number you want to delete: "<<endl;
			cin>>del_num;	
			Bnode<Type_Sort> del_node(del_num);
			ret = bstree.delete_node(&del_node);
			if(OK == ret){
				j++;
				get_data_from_bstree(bstree.get_root(), sorted);
				for(i=0; i<=right_side-j; i++){
					if(reverse){
						pdata_temp[i] = sorted.at(right_side-j-i);
						cout<<sorted.at(right_side-j-i)<<", ";
					}else{
						pdata_temp[i] = sorted.at(i);
						cout<<sorted.at(i)<<", ";
					}
				}
				sorted.clear();
				if(OK == test(pdata_temp, 0, right_side-j)){
					cout<<"\nDelete node and sort successfully!"<<endl;
				}else{
					cout<<"\nDelete node and sort FAILED!"<<endl;
				}
			}else{
				cout<<"delete_node err, ret = "<<ret;
			}			
			cout<<"\nContinue to delete?[y|n]: ";
			cin>>flag;
		}

		delete [] node;
		
		return; 	
	}

#endif

	template <class Type_Sort>
	uint32 Sort<Type_Sort>::test(Type_Sort *pdata, sint32 left, sint32 right){
		uint reverse = is_reverse();
		sint32 i;
		uint32 ret = OK;
		
		for(i=left; i<right; i++){
			if(reverse){
				if(pdata[i]<pdata[i+1]){
					cout<<"[class Sort] ERROR! REVERSE SORT FAILED! ["<<i<<"]: "<<pdata[i]<<", ["<<i+1<<"]: "<<pdata[i+1]<<endl;
					ret = FAILED;
					break;
				}
			}else{
				if(pdata[i]>pdata[i+1]){
					cout<<"[class Sort] ERROR! SORT FAILED! ["<<i<<"]: "<<pdata[i]<<", ["<<i+1<<"]: "<<pdata[i+1]<<endl;
					ret = FAILED;
					break;
				}
			}

		}
		return ret;
	}








	
}

#endif

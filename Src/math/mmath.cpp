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
#include <cmath>
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


	template <class Type_Bnode>
	uint Bnode<Type_Bnode>::is_lchild(){
		if(!this->is_root()){
			return (this == this->get_parent()->get_lchild());
		}else{
			return FALSE;
		}
	}


	template <class Type_Bnode>
	uint Bnode<Type_Bnode>::is_rchild(){
		if(!this->is_root()){
			return (this == this->get_parent()->get_rchild());
		}else{
			return FALSE;
		}
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
				cout<<root->get_data()<<"(node_h/l_h/r_h)=("<<root->get_node_h()<<"/"<<root->get_ltree_h()<<"/"<<root->get_rtree_h()<<") ";
				if(root->get_parent()){cout<<"  parent: "<<root->get_parent()->get_data();}
				else{cout<<"  root node!";}
				
				if(root->get_lchild()){cout<<"  l_child: "<<root->get_lchild()->get_data();}
				else{cout<<"  l_child: NULL!";}
				
				if(root->get_rchild()){cout<<"  r_child: "<<root->get_rchild()->get_data();}
				else{cout<<"  r_child: NULL!";}
				cout<<endl;

				traverse(root->get_lchild(), order);
				traverse(root->get_rchild(), order);
			}else if(1 == order){
				traverse(root->get_lchild(), order);
				
				cout<<root->get_data()<<"(node_h/l_h/r_h)=("<<root->get_node_h()<<"/"<<root->get_ltree_h()<<"/"<<root->get_rtree_h()<<") ";
				if(root->get_parent()){cout<<"  parent: "<<root->get_parent()->get_data();}
				else{cout<<"  root node!";}
				
				if(root->get_lchild()){cout<<"  l_child: "<<root->get_lchild()->get_data();}
				else{cout<<"  l_child: NULL!";}
				
				if(root->get_rchild()){cout<<"  r_child: "<<root->get_rchild()->get_data();}
				else{cout<<"  r_child: NULL!";}
				cout<<endl;
				
				traverse(root->get_rchild(), order);
			}else{
				traverse(root->get_lchild(), order);
				traverse(root->get_rchild(), order);
				
				cout<<root->get_data()<<"(node_h/l_h/r_h)=("<<root->get_node_h()<<"/"<<root->get_ltree_h()<<"/"<<root->get_rtree_h()<<") ";
				if(root->get_parent()){cout<<"  parent: "<<root->get_parent()->get_data();}
				else{cout<<"  root node!";}
				
				if(root->get_lchild()){cout<<"  l_child: "<<root->get_lchild()->get_data();}
				else{cout<<"  l_child: NULL!";}
				
				if(root->get_rchild()){cout<<"  r_child: "<<root->get_rchild()->get_data();}
				else{cout<<"  r_child: NULL!";}
				cout<<endl;
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


	template <class Type_Btree>
	sint Btree<Type_Btree>::depth(Bnode<Type_Btree> *node){
		if(NULL == node){return 0;}
		else{
			sint ld = depth(node->get_lchild());
			sint rd = depth(node->get_rchild());
			return ld > rd ? ld+1 : rd+1;
		}
	}


	template <class Type_Btree>
	uint Btree<Type_Btree>::is_balanced(Bnode<Type_Btree> *node){
		if(NULL == node){  // ����Ҳ��ƽ���
			//cout<<"[class Btree] WARNING: NULL TREE!"<<endl;
			return TRUE;
		}
		return abs(depth(node->get_lchild()) - depth(node->get_rchild())) <= 1 && is_balanced(node->get_lchild()) && is_balanced(node->get_rchild());
	}


	/*
		����:
		��ĳ�������Ϊ��ת���(root)�������ӽ���Ϊ��ת���
		�ĸ���㣬���ӽ������ӽ���Ϊ��ת�������ӽ�㣬
		���ӽ�㱣�ֲ��䣬��ת����Ϊ���ӽ������ӽڵ㡣

		ע��:���øú�����ֻ�ܱ�֤���صĽ�㼰������������
		ltree_h/rtree_h/node_h��Ϣ����ȷ�ԣ������Ϊ���ؽ��ĵ�����
		���丸�ڵ�ֱ��������·���ϵĽ���ltree_h/rtree_h/node_h��Ϣ
		�ı仯����Ҫ�����߶�����и��¡�
	*/
	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::left_rotate(Bnode<Type_Btree> *root){
		if(NULL == root){return root;}
		Bnode<Type_Btree> *temp = root->get_rchild();
		if(NULL == temp){
			cout<<"[class Btree] left_rotate error, root has no right child!\n";
			return root;
		}
		if(!root->is_root()){  // ���root���Ǹ��ڵ�
			//��root�ĸ��ڵ��temp��ϵ����
			if(root->is_lchild()){
				root->get_parent()->set_lchild(temp);
			}else{
				root->get_parent()->set_rchild(temp);
			}			
		}else{  // ���root�Ǹ��ڵ㣬�򽫸��ڵ㻻��temp
			this->set_root(temp);
		}		
		temp->set_parent(root->get_parent());  // ���root�Ǹ��ڵ㣬����������ó���NULL
		root->set_parent(temp);
		Bnode<Type_Btree> *child;
		child = temp->get_lchild();
		root->set_rchild(child);
		if(child){
			child->set_parent(root);
		}		
		temp->set_lchild(root);

		//��������ֻ��ı���ת�������Һ��ӵ�ltree_h/rtree_h/node_h��Ϣ
		temp->set_ltree_h(depth(temp->get_lchild()));
		temp->set_rtree_h(depth(temp->get_rchild()));
		temp->refresh_node_h();
		root->set_ltree_h(depth(root->get_lchild()));
		root->set_rtree_h(depth(root->get_rchild()));
		root->refresh_node_h();
		
		return temp;
	}


	/*
		����:
		��ĳ�������Ϊ��ת���(root)�������ӽ���Ϊ��ת���
		�ĸ���㣬���ӽ������ӽ���Ϊ��ת�������ӽ�㣬
		���ӽ�㱣�ֲ��䣬��ת����Ϊ���ӽ������ӽڵ㡣

		ע��:���øú�����ֻ�ܱ�֤���صĽ�㼰������������
		ltree_h/rtree_h/node_h��Ϣ����ȷ�ԣ������Ϊ���ؽ��ĵ�����
		���丸�ڵ�ֱ��������·���ϵĽ���ltree_h/rtree_h/node_h��Ϣ
		�ı仯����Ҫ�����߶�����и��¡�
	*/
	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::right_rotate(Bnode<Type_Btree> *root){
		if(NULL == root){return root;}
		Bnode<Type_Btree> *temp = root->get_lchild(); 
		if(NULL == temp){
			cout<<"[class Btree] right_rotate error, root has no left child!\n";
			return root;
		}
		if(!root->is_root()){
			//��root�ĸ��ڵ��temp��ϵ����
			if(root->is_lchild()){
				root->get_parent()->set_lchild(temp);
			}else{
				root->get_parent()->set_rchild(temp);
			}
		}else{  // ���root�Ǹ��ڵ㣬�򽫸��ڵ㻻��temp
			this->set_root(temp);
		}
		temp->set_parent(root->get_parent());  // ���root�Ǹ��ڵ㣬����������ó���NULL
		root->set_parent(temp);
		Bnode<Type_Btree> *child;
		child = temp->get_rchild();
		root->set_lchild(child);
		if(child){
			child->set_parent(root);
		}	
		temp->set_rchild(root);

		//��������ֻ��ı���ת���������ӵ�ltree_h/rtree_h/node_h��Ϣ
		temp->set_ltree_h(depth(temp->get_lchild()));
		temp->set_rtree_h(depth(temp->get_rchild()));
		temp->refresh_node_h();
		root->set_ltree_h(depth(root->get_lchild()));
		root->set_rtree_h(depth(root->get_rchild()));
		root->refresh_node_h();
		
		return temp;
	}


	/*
		����-����:
		�ȶ�root�������������ٶ�root���� 

		ע��:���øú�����ֻ�ܱ�֤���صĽ�㼰������������
		ltree_h/rtree_h/node_h��Ϣ����ȷ�ԣ������Ϊ���ؽ��ĵ�����
		���丸�ڵ�ֱ��������·���ϵĽ���ltree_h/rtree_h/node_h��Ϣ
		�ı仯����Ҫ�����߶�����и��¡�
	*/
	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::leftright_rotate(Bnode<Type_Btree> *root){
		if(NULL == root){return root;}
		root->set_lchild(left_rotate(root->get_lchild()));
		root->set_ltree_h(depth(root->get_lchild()));
		root->refresh_node_h();
		return right_rotate(root);
	}


	/*
		����-����
		�ȶ�root�������������ٶ�root���� 

		ע��:���øú�����ֻ�ܱ�֤���صĽ�㼰������������
		ltree_h/rtree_h/node_h��Ϣ����ȷ�ԣ������Ϊ���ؽ��ĵ�����
		���丸�ڵ�ֱ��������·���ϵĽ���ltree_h/rtree_h/node_h��Ϣ
		�ı仯����Ҫ�����߶�����и��¡�
	*/
	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::rightleft_rotate(Bnode<Type_Btree> *root){
		if(NULL == root){return root;}
		root->set_rchild(right_rotate(root->get_rchild()));
		root->set_rtree_h(depth(root->get_rchild()));
		root->refresh_node_h();
		return left_rotate(root);
	}


	/*
		��nodeΪ������ϵݹ����node��root·���ϵ����������߶�
		�͸��ڵ�Ľ��߶�(��ǰ�������node���ڵ�ĸ߶���Ϣ��
		node����ĸ߶���Ϣ��ǰһ�εݹ�����и��¡�)
		level��ʾnode�ĸ߶ȵȼ�������ǰnode������λ����ltree_h��rtree_h
		�Ľϴ�ֵ����ֹ�ظ����ӡ�������ʾ:�������Ҳ���2�Ĺ����У�
		6.9��ltree_h�ǲ�Ӧ�����ӵģ�ӦһֱΪ2��������6.9��level����2��
				6.9                                             6.9
		3.3                   ===>                     3.3
		        4                                  2               4
	*/
	template <class Type_Btree>
	state Btree<Type_Btree>::refresh_height_from_current_node_to_root(Bnode<Type_Btree> *node, sint32 level){
		sint32 parent_level = level+1;
		if(node->is_root()){  // node�Ǹ��ڵ�
			return OK;
		}else{
			if(node->is_lchild()){  // node������
				// node���ڵ���������߶�ֻ����parent_level
				node->get_parent()->set_ltree_h(parent_level); 				
				// node���ڵ�Ľڵ�߶�ˢ��
				node->get_parent()->refresh_node_h();
				// node���ڵ�Ϊ�µĸ�����ʼ�ڵ�
				return refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}else if(node->is_rchild()){
				// node���ڵ���������߶�ֻ����parent_level
				node->get_parent()->set_rtree_h(parent_level); 
				// node���ڵ�Ľڵ�߶�ˢ��
				node->get_parent()->refresh_node_h();
				// node���ڵ�Ϊ�µĸ�����ʼ�ڵ�
				return refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}else{
				cout<<"[class Btree] refresh_height_from_current_node_to_root ERROR: invalid node!"<<endl;
				return FAILED;
			}
		}
	}


	template <class Type_Bstree>
	Bnode<Type_Bstree>* BStree<Type_Bstree>::insert_recursive(uint32 flag, 
					Bnode<Type_Bstree> *root, Bnode<Type_Bstree> *parent_of_root, 
					Bnode<Type_Bstree> *new_node){
					
		if(NULL == root){  // ��ǰλ���ǿյģ����Բ���
			new_node->set_parent(parent_of_root);
			new_node->set_node_h(1);
			new_node->set_ltree_h(0);
			new_node->set_rtree_h(0);
			if(0 == flag){
				parent_of_root->set_lchild(new_node);
			}else{
				parent_of_root->set_rchild(new_node);
			}
			if(OK != this->refresh_height_from_current_node_to_root(new_node, 0)){
				cout<<"[class BStree] refresh_height_from_current_node_to_root ERROR!"<<endl;
			}
			return new_node;
		}else{
			if(new_node->get_data() <= root->get_data()){
				insert_recursive(0, root->get_lchild(), root, new_node);
				
				if(!this->is_balanced(root)){
					Bnode<Type_Bstree> *temp = NULL;
					if(new_node->get_data() > root->get_lchild()->get_data()){
						// �����������ұߣ�����������
						temp = this->left_rotate(root->get_lchild());
						this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
					}
					// �ڵ�����
					temp = this->right_rotate(root);
					this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
				}			
			}else{
				insert_recursive(1, root->get_rchild(), root, new_node);

				if(!this->is_balanced(root)){
					Bnode<Type_Bstree> *temp = NULL;
					if(new_node->get_data() <= root->get_rchild()->get_data()){
						// �������Һ�����ߣ��Һ���������
						temp = this->right_rotate(root->get_rchild());
						this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
					}
					// �ڵ�����
					temp = this->left_rotate(root);
					this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
				}
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
			cout<<"[class Bstree] insert_node ERROR: NULL pointer input!"<<endl;
			return this->get_root();
		}

		if(NULL == this->get_root()){
			this->set_root(new_node);
			this->get_root()->set_node_h(1);
			this->get_root()->set_ltree_h(0);
			this->get_root()->set_rtree_h(0);
			cout<<"[class Bstree] Create a new bstree, insert the new node as the root node!"<<endl;
			return this->get_root();
		}else{
			//���Ը��ڵ�ĵݹ�����³���insert_recursive�У���������е�flag=0��ʵ��û�������
			//��������Ŀ������insert_recursive�еݹ鷵�ؽ���ƽ�����ʱ�����������root����
			//����Ҫ���parent_of_root������ת�������parent_of_root��ת�ǻ��������
			insert_recursive(0, this->get_root(), NULL, new_node);
			//�ı�rootֻ������תʱ�ſ��ܷ������������������������Ѿ���Ը��ڵ�ĸı�
			//�����˴���������ֻҪֱ�ӷ���this->get_root()���ɡ�
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

	ע:��֤ת���������ltree_h/rtree_h/node_h��Ϣ����ȷ��
	*/
	template <class Type_Bstree>
	state BStree<Type_Bstree>::delete_node_and_adjust_to_bstree(Bnode<Type_Bstree> *node){
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
					node->get_parent()->set_ltree_h(0);
				}else if(node == node->get_parent()->get_rchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_parent()->set_rchild(NULL);
					node->get_parent()->set_rtree_h(0);					
				}else{
					cout<<"[class Bstree] 1.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
				node->get_parent()->refresh_node_h();
				ret = this->refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}
		}else if(NULL != node->get_lchild() && NULL == node->get_rchild()){ //ֻ������
			if(root == node){  // ͬʱ���Ǹ��ڵ�
				node->get_lchild()->set_parent(NULL);
				this->set_root(node->get_lchild());
				//��������²���Ҫ����ltree_h/rtree_h/node_h��Ϣ
			}else{
				if(node == node->get_parent()->get_lchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_lchild()->set_parent(node->get_parent());
					node->get_parent()->set_lchild(node->get_lchild());
					node->get_parent()->set_ltree_h(node->get_lchild()->get_node_h());
				}else if(node == node->get_parent()->get_rchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_lchild()->set_parent(node->get_parent());
					node->get_parent()->set_rchild(node->get_lchild());
					node->get_parent()->set_rtree_h(node->get_lchild()->get_node_h());
				}else{
					cout<<"[class Bstree] 2.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
				node->get_parent()->refresh_node_h();
				ret = this->refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}
		}else if(NULL == node->get_lchild() && NULL != node->get_rchild()){ //ֻ���Һ���
			if(root == node){  // ͬʱ���Ǹ��ڵ�
				node->get_rchild()->set_parent(NULL);
				this->set_root(node->get_rchild());
				//��������²���Ҫ����ltree_h/rtree_h/node_h��Ϣ
			}else{
				if(node == node->get_parent()->get_lchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_rchild()->set_parent(node->get_parent());
					node->get_parent()->set_lchild(node->get_rchild());
					node->get_parent()->set_ltree_h(node->get_rchild()->get_node_h());
				}else if(node == node->get_parent()->get_rchild()){//ɾ���ڵ�����Ҷ�ӽ��
					node->get_rchild()->set_parent(node->get_parent());
					node->get_parent()->set_rchild(node->get_rchild());
					node->get_parent()->set_rtree_h(node->get_rchild()->get_node_h());
				}else{
					cout<<"[class Bstree] 3.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
				node->get_parent()->refresh_node_h();
				ret = this->refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}
		}else{  //ɾ���ڵ�������ӣ������Һ���
			temp = node->get_rchild();
			while(temp){  //��ѭ���ҵ�ɾ���ڵ�������������ߵĽ�㣬�ýڵ��ֵ���ŵ�ɾ���ڵ��λ��
				replace = temp;
				temp = temp->get_lchild();
			}
			//�滻�ڵ㲻���������ӣ������������滻�ڵ�
			if(replace == replace->get_parent()->get_lchild()){
				//�滻�ڵ����丸�ڵ������
				replace->get_parent()->set_lchild(replace->get_rchild());
				if(replace->get_rchild()){
					replace->get_parent()->set_ltree_h(replace->get_rchild()->get_node_h());
				}else{
					replace->get_parent()->set_ltree_h(0);
				}				
			}else if(replace == replace->get_parent()->get_rchild()){
				//�滻�ڵ����丸�ڵ���Һ���
				//��������Ǵ��ڵ�:ɾ���ڵ����������ÿ���ڵ㶼ֻ��������
				replace->get_parent()->set_rchild(replace->get_rchild());
				if(replace->get_rchild()){
					replace->get_parent()->set_rtree_h(replace->get_rchild()->get_node_h());
				}else{
					replace->get_parent()->set_rtree_h(0);
				}
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
			replace->get_parent()->refresh_node_h();
			ret = this->refresh_height_from_current_node_to_root(replace->get_parent(), replace->get_parent()->get_node_h()-1);
		}
		return ret;
	}


	//������������ת����ƽ�������������ͬʱ��֤ת�����
	//ltree_h/rtree_h/node_h��Ϣ����ȷ��
	template <class Type_Bstree>
	state BStree<Type_Bstree>::adjust_to_balanced_bstree(Bnode<Type_Bstree> *root){		
		state ret = OK;

		while(!this->is_balanced(root)){
			ret = adjust_to_balanced_bstree(root->get_lchild());
			ret |= adjust_to_balanced_bstree(root->get_rchild());

			sint32 rtree_h = 0, rltree_h = 0, rrtree_h = 0;  //�������������������ӣ����������Һ���
			sint32 ltree_h = 0, lltree_h = 0, lrtree_h = 0;  //�������������������ӣ����������Һ���
			Bnode<Type_Bstree> *l = NULL, *r = NULL, *temp = NULL;

			// �п��ܴ�������������ƽ�������¸��ڵ㲻ƽ������
			if(!this->is_balanced(root)){
				ltree_h = root->get_ltree_h();
				rtree_h = root->get_rtree_h();
				
				if(root->get_lchild()){  //�����������
					l = root->get_lchild();
					lltree_h = l->get_ltree_h();
					lrtree_h = l->get_rtree_h();
				}
				if(root->get_rchild()){  //�����������
					r = root->get_rchild();
					rltree_h = r->get_ltree_h();
					rrtree_h = r->get_rtree_h();
				}
				//��һ��L��ʾroot�����������������ߡ�
				if(ltree_h > rtree_h){
					//�ڶ���L��ʾroot�����ӵ����������������ߣ�
					//����root�����ӵ����������ȸߡ�
					if(lltree_h >= lrtree_h){// LL��
						temp = this->right_rotate(root);
					}
					//�ڶ���R��ʾroot�����ӵ�����������������
					else{//LR��
						temp = this->leftright_rotate(root);
					}
				}
				//��һ��R��ʾroot�����������������ߡ�
				else{
					//�ڶ���R��ʾroot���Һ��ӵ����������������ߣ�
					//����root���Һ��ӵ����������ȸߡ�
					if(rltree_h <= rrtree_h){// RR��
						temp = this->left_rotate(root);
					}
					//�ڶ���L��ʾroot���Һ��ӵ����������������ߡ�
					else{//RL��
						temp = this->rightleft_rotate(root);
					}
				}
				ret |= this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
			}
		}
		return ret;
	}


	/*
		��һ�ö�������������ƽ�������������ɾ��һ���ڵ㣬
		��֤ɾ��������һ��ƽ�����������
	*/
	template <class Type_Bstree>
	state BStree<Type_Bstree>::delete_node_pro(Bnode<Type_Bstree> *node){
		state ret = OK;

		//�ȵõ�һ�ö���������
		if(OK != (ret = delete_node(node))){
			cout<<"[class Bstree] delete_node_pro failed, ret="<<ret<<endl;
			return ret;
		}else{
			/*----------------------
			uint balance = this->is_balanced(this->get_root());
			cout<<"------before adjust_to_balanced_bstree------balance: "<<(balance?"TRUE":"FALSE")<<"------------------"<<endl;	
			this->traverse(this->get_root(), 1);
			cout<<endl;
			----------------------*/		
			//�ٽ�����������ת����ƽ�����������
			if(OK != (ret = adjust_to_balanced_bstree(this->get_root()))){
				cout<<"[class Bstree] adjust_to_balanced_bstree failed, ret="<<ret<<endl;
			}
			return ret;			
		}
	}


	/*
		��һ�ö�����������ɾ��һ���ڵ㣬��֤ɾ������
		����һ�ö���������
	*/
	template <class Type_Bstree>
	state BStree<Type_Bstree>::delete_node(Bnode<Type_Bstree> *node){
		Bnode<Type_Bstree>* del_node = this->find_node(node);
		state ret = OK;
		
		if(NULL == del_node){
			cout<<"[class Bstree] NO SUCH NODE TO DELETE!"<<endl;
			return NULL_PTR;
		}else{
			ret = delete_node_and_adjust_to_bstree(del_node);
			return ret;
		}
	}


	template <class Type_Bstree>
	Bnode<Type_Bstree>* BStree<Type_Bstree>::bulid_balanced_bstree_recursive(Type_Bstree *pdata, 
											 sint32 left, sint32 right, Bnode<Type_Bstree>* addr){
        sint32 mid = (left + right) / 2;
		
		addr[mid].set_data(pdata[mid]);
		addr[mid].set_lchild(NULL);
		addr[mid].set_rchild(NULL);
		addr[mid].set_parent(NULL);
		addr[mid].set_ltree_h(0);
		addr[mid].set_rtree_h(0);
		addr[mid].set_node_h(1);
		
		if (left <= mid - 1){
			Bnode<Type_Bstree> *lchild = bulid_balanced_bstree_recursive(pdata, left, mid - 1, addr);
			addr[mid].set_lchild(lchild);
			lchild->set_parent(&addr[mid]);
			this->refresh_height_from_current_node_to_root(lchild, lchild->get_node_h()-1);			
		}
		if (mid + 1 <= right){
			Bnode<Type_Bstree> *rchild = bulid_balanced_bstree_recursive(pdata,  mid + 1, right, addr);
			addr[mid].set_rchild(rchild);
			rchild->set_parent(&addr[mid]);
			this->refresh_height_from_current_node_to_root(rchild, rchild->get_node_h()-1);
		}
		
		return (addr+mid);
	}


	template <class Type_Bstree>
	Bnode<Type_Bstree>* BStree<Type_Bstree>::bulid_balanced_bstree(Type_Bstree *pdata, 
											 sint32 left, sint32 right, Bnode<Type_Bstree>* addr){
		if (right - left < 0 || NULL == addr || NULL == pdata){  // û������
			return NULL;
		}else{
			Bnode<Type_Bstree> *root;
			Sort<Type_Bstree> sorted;
			Type_Bstree *pdata_temp = new Type_Bstree[right - left + 1];

			memcpy(pdata_temp, pdata + left, (right - left + 1)*sizeof(Type_Bstree));
			//������
			sorted.quick_sort(pdata_temp, 0, right - left);
			//����̰�ķ�����
			root = bulid_balanced_bstree_recursive(pdata_temp, 0, right - left, addr);

			this->set_root(root);
			
			delete [] pdata_temp;

			return root;  //�������ĸ��ڵ�
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

#if 0
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

#elif 0
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
		uint balance = FALSE, reverse = is_reverse();

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
		cout<<endl;
		balance = bstree.is_balanced(bstree.get_root());
		cout<<"------------------balance: "<<(balance?"TRUE":"FALSE")<<"------------------"<<endl;			
		bstree.traverse(bstree.get_root(), 1);
		cout<<endl;
		sorted.clear();
		
		cout<<"\nIf you want to delete a number, press y, else press n.";
		cin>>flag;
		while(flag == 'y'){
			cout<<"\nPlease input the number you want to delete: "<<endl;
			cin>>del_num;	
			Bnode<Type_Sort> del_node(del_num);
			ret = bstree.delete_node(&del_node);
			if(OK == ret){
				balance = bstree.is_balanced(bstree.get_root());
				cout<<"------------------balance: "<<(balance?"TRUE":"FALSE")<<"------------------"<<endl;	
				bstree.traverse(bstree.get_root(), 1);
				cout<<endl;
				
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

#elif 1
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
		uint balance = FALSE, reverse = is_reverse();

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
		cout<<endl;
		balance = bstree.is_balanced(bstree.get_root());
		cout<<"------------------balance: "<<(balance?"TRUE":"FALSE")<<"------------------"<<endl;			
		bstree.traverse(bstree.get_root(), 1);
		cout<<endl;
		sorted.clear();
		
		cout<<"\nIf you want to delete a number, press y, else press n.";
		cin>>flag;
		while(flag == 'y'){
			cout<<"\nPlease input the number you want to delete: "<<endl;
			cin>>del_num;	
			Bnode<Type_Sort> del_node(del_num);
			ret = bstree.delete_node_pro(&del_node);
			if(OK == ret){
				balance = bstree.is_balanced(bstree.get_root());
				cout<<"------------------balance: "<<(balance?"TRUE":"FALSE")<<"------------------"<<endl;	
				bstree.traverse(bstree.get_root(), 1);
				cout<<endl;
				
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

#elif 0
	template <class Type_Sort>
	void Sort<Type_Sort>::bitree_sort(Type_Sort *pdata, sint32 left, sint32 right){
		if (left >= right) {
			return;
		}

		Type_Sort *pdata_temp = pdata + left;  // ֧��������
		BStree<Type_Sort> bstree;
		Bnode<Type_Sort> *node = new Bnode<Type_Sort>[right - left + 1];
		sint32 i, right_side = right - left;
		uint balance = 0, reverse = is_reverse();
		
		for(i=0; i<=right_side; i++){
			node[i].set_data(pdata_temp[i]);
			bstree.insert_node(&node[i]);
			balance = bstree.is_balanced(bstree.get_root());
			cout<<"------------------data num: "<<i+1<<", balance: "<<(balance?"TRUE":"FALSE")<<endl;			
		}
		bstree.traverse(bstree.get_root(), 1);

		delete [] node;
		
		return; 	
	}

#elif 0
	template <class Type_Sort>
	void Sort<Type_Sort>::bitree_sort(Type_Sort *pdata, sint32 left, sint32 right){
		BStree<Type_Sort> bstree;
		Bnode<Type_Sort> *root;
		uint balance = 0;
		Bnode<Type_Sort> *addr = new Bnode<Type_Sort>[right - left + 1];

		root = bstree.bulid_balanced_bstree(pdata, left, right, addr);
		balance = bstree.is_balanced(bstree.get_root());
		cout<<"------------------balance: "<<(balance?"TRUE":"FALSE")<<"------------------"<<endl;	
		bstree.traverse(bstree.get_root(), 1);
		cout<<endl;
		
		delete [] addr;
		
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

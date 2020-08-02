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
		按照顺序从上往下，从左往右一个一个插入节点
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
					node = next_node.front();  //接下来判断队列中第一个元素的左右子树情况
					next_node.pop_front();  // 删除第一个元素
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
			// 遍历顺序:前序0，中序1，后序2
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
					return temp;  // 找到了该节点
				}else{
					if(NULL != temp->get_lchild()){next_node.push_back(temp->get_lchild());}
					if(NULL != temp->get_rchild()){next_node.push_back(temp->get_rchild());}
					if(next_node.size() > 0){
						temp = next_node.front();  //接下来判断队列中第一个元素的左右子树情况
						next_node.pop_front();	// 删除第一个元素
					}else{
						temp = NULL;
					}
				}
			}
			return NULL;  // 找不到该节点
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
		if(NULL == node){  // 空树也是平衡的
			//cout<<"[class Btree] WARNING: NULL TREE!"<<endl;
			return TRUE;
		}
		return abs(depth(node->get_lchild()) - depth(node->get_rchild())) <= 1 && is_balanced(node->get_lchild()) && is_balanced(node->get_rchild());
	}


	/*
		左旋:
		以某个结点作为旋转结点(root)，其右子结点变为旋转结点
		的父结点，右子结点的左子结点变为旋转结点的右子结点，
		左子结点保持不变，旋转结点变为右子结点的左子节点。

		注意:调用该函数后，只能保证返回的结点及其左右子树的
		ltree_h/rtree_h/node_h信息的正确性，如果因为返回结点的调整导
		致其父节点直至树根的路径上的结点的ltree_h/rtree_h/node_h信息
		的变化，需要调用者额外进行更新。
	*/
	template <class Type_Btree>
	Bnode<Type_Btree>* Btree<Type_Btree>::left_rotate(Bnode<Type_Btree> *root){
		if(NULL == root){return root;}
		Bnode<Type_Btree> *temp = root->get_rchild();
		if(NULL == temp){
			cout<<"[class Btree] left_rotate error, root has no right child!\n";
			return root;
		}
		if(!root->is_root()){  // 如果root不是根节点
			//将root的父节点和temp联系起来
			if(root->is_lchild()){
				root->get_parent()->set_lchild(temp);
			}else{
				root->get_parent()->set_rchild(temp);
			}			
		}else{  // 如果root是根节点，则将根节点换成temp
			this->set_root(temp);
		}		
		temp->set_parent(root->get_parent());  // 如果root是根节点，则这里就设置成了NULL
		root->set_parent(temp);
		Bnode<Type_Btree> *child;
		child = temp->get_lchild();
		root->set_rchild(child);
		if(child){
			child->set_parent(root);
		}		
		temp->set_lchild(root);

		//左旋操作只会改变旋转结点和其右孩子的ltree_h/rtree_h/node_h信息
		temp->set_ltree_h(depth(temp->get_lchild()));
		temp->set_rtree_h(depth(temp->get_rchild()));
		temp->refresh_node_h();
		root->set_ltree_h(depth(root->get_lchild()));
		root->set_rtree_h(depth(root->get_rchild()));
		root->refresh_node_h();
		
		return temp;
	}


	/*
		右旋:
		以某个结点作为旋转结点(root)，其左子结点变为旋转结点
		的父结点，左子结点的右子结点变为旋转结点的左子结点，
		右子结点保持不变，旋转结点变为左子结点的右子节点。

		注意:调用该函数后，只能保证返回的结点及其左右子树的
		ltree_h/rtree_h/node_h信息的正确性，如果因为返回结点的调整导
		致其父节点直至树根的路径上的结点的ltree_h/rtree_h/node_h信息
		的变化，需要调用者额外进行更新。
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
			//将root的父节点和temp联系起来
			if(root->is_lchild()){
				root->get_parent()->set_lchild(temp);
			}else{
				root->get_parent()->set_rchild(temp);
			}
		}else{  // 如果root是根节点，则将根节点换成temp
			this->set_root(temp);
		}
		temp->set_parent(root->get_parent());  // 如果root是根节点，则这里就设置成了NULL
		root->set_parent(temp);
		Bnode<Type_Btree> *child;
		child = temp->get_rchild();
		root->set_lchild(child);
		if(child){
			child->set_parent(root);
		}	
		temp->set_rchild(root);

		//右旋操作只会改变旋转结点和其左孩子的ltree_h/rtree_h/node_h信息
		temp->set_ltree_h(depth(temp->get_lchild()));
		temp->set_rtree_h(depth(temp->get_rchild()));
		temp->refresh_node_h();
		root->set_ltree_h(depth(root->get_lchild()));
		root->set_rtree_h(depth(root->get_rchild()));
		root->refresh_node_h();
		
		return temp;
	}


	/*
		左旋-右旋:
		先对root的左子树左旋再对root右旋 

		注意:调用该函数后，只能保证返回的结点及其左右子树的
		ltree_h/rtree_h/node_h信息的正确性，如果因为返回结点的调整导
		致其父节点直至树根的路径上的结点的ltree_h/rtree_h/node_h信息
		的变化，需要调用者额外进行更新。
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
		右旋-左旋
		先对root的右子树右旋再对root左旋 

		注意:调用该函数后，只能保证返回的结点及其左右子树的
		ltree_h/rtree_h/node_h信息的正确性，如果因为返回结点的调整导
		致其父节点直至树根的路径上的结点的ltree_h/rtree_h/node_h信息
		的变化，需要调用者额外进行更新。
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
		以node为起点向上递归更新node到root路径上的左右子树高度
		和各节点的结点高度(当前处理的是node父节点的高度信息，
		node自身的高度信息在前一次递归过程中更新。)
		level表示node的高度等级，即当前node所处的位置上ltree_h和rtree_h
		的较大值，防止重复增加。如下所示:从左往右插入2的过程中，
		6.9的ltree_h是不应该增加的，应一直为2，即这里6.9的level就是2。
				6.9                                             6.9
		3.3                   ===>                     3.3
		        4                                  2               4
	*/
	template <class Type_Btree>
	state Btree<Type_Btree>::refresh_height_from_current_node_to_root(Bnode<Type_Btree> *node, sint32 level){
		sint32 parent_level = level+1;
		if(node->is_root()){  // node是根节点
			return OK;
		}else{
			if(node->is_lchild()){  // node是左孩子
				// node父节点的左子树高度只能是parent_level
				node->get_parent()->set_ltree_h(parent_level); 				
				// node父节点的节点高度刷新
				node->get_parent()->refresh_node_h();
				// node父节点为新的更新起始节点
				return refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}else if(node->is_rchild()){
				// node父节点的右子树高度只能是parent_level
				node->get_parent()->set_rtree_h(parent_level); 
				// node父节点的节点高度刷新
				node->get_parent()->refresh_node_h();
				// node父节点为新的更新起始节点
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
					
		if(NULL == root){  // 当前位置是空的，可以插入
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
						// 插入在左孩子右边，左孩子先左旋
						temp = this->left_rotate(root->get_lchild());
						this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
					}
					// 节点右旋
					temp = this->right_rotate(root);
					this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
				}			
			}else{
				insert_recursive(1, root->get_rchild(), root, new_node);

				if(!this->is_balanced(root)){
					Bnode<Type_Bstree> *temp = NULL;
					if(new_node->get_data() <= root->get_rchild()->get_data()){
						// 插入在右孩子左边，右孩子先右旋
						temp = this->right_rotate(root->get_rchild());
						this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
					}
					// 节点左旋
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
			//将对根节点的递归调用下沉到insert_recursive中，下面调用中的flag=0其实是没有意义的
			//这样做的目的是在insert_recursive中递归返回进行平衡调整时，能正好针对root进行
			//否则要针对parent_of_root进行旋转，而针对parent_of_root旋转是会有问题的
			insert_recursive(0, this->get_root(), NULL, new_node);
			//改变root只会在旋转时才可能发生，由于在左旋和右旋中已经针对根节点的改变
			//进行了处理，故这里只要直接返回this->get_root()即可。
			return this->get_root();
		}
	}

	/*
	1.要删除的节点只有左孩子，那么就让该节点的父亲结点指向
	该节点的左孩子，然后删除该节点
	2.要删除的节点只有右孩子，那么就让该节点的父亲结点指向
	该节点的右孩子，然后删除该节点
	(对于上面这两种情况还应该在之前进行一个判断，就是判断
	这个节点是否是根节点，如果是根节点的话，就直接让根节点
	指向这个节点的左孩子或右孩子，然后删除这个节点)
	3.要删除的节点的左右孩子都存在:
		a.找到该节点的右子树中的最左孩子（也就是右子树中序遍
		历的第一个节点?
		b.把它的值和要删除的节点的值进行交换
		c.然后删除这个节点即相当于把我们想删除的节点删除了

	注:保证转换后的树的ltree_h/rtree_h/node_h信息的正确性
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
		
		if(NULL == node->get_lchild() && NULL == node->get_rchild()){ // 删除节点是叶子结点
			if(root == node){  // 同时又是根节点
				this->set_root(NULL);
			}else{
				if(node == node->get_parent()->get_lchild()){//删除节点是左叶子结点
					node->get_parent()->set_lchild(NULL);
					node->get_parent()->set_ltree_h(0);
				}else if(node == node->get_parent()->get_rchild()){//删除节点是右叶子结点
					node->get_parent()->set_rchild(NULL);
					node->get_parent()->set_rtree_h(0);					
				}else{
					cout<<"[class Bstree] 1.NODE TO BE DELETE ERROR!"<<endl;
					return PARAM_ERR;
				}
				node->get_parent()->refresh_node_h();
				ret = this->refresh_height_from_current_node_to_root(node->get_parent(), node->get_parent()->get_node_h()-1);
			}
		}else if(NULL != node->get_lchild() && NULL == node->get_rchild()){ //只有左孩子
			if(root == node){  // 同时又是根节点
				node->get_lchild()->set_parent(NULL);
				this->set_root(node->get_lchild());
				//此种情况下不需要更新ltree_h/rtree_h/node_h信息
			}else{
				if(node == node->get_parent()->get_lchild()){//删除节点是左叶子结点
					node->get_lchild()->set_parent(node->get_parent());
					node->get_parent()->set_lchild(node->get_lchild());
					node->get_parent()->set_ltree_h(node->get_lchild()->get_node_h());
				}else if(node == node->get_parent()->get_rchild()){//删除节点是右叶子结点
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
		}else if(NULL == node->get_lchild() && NULL != node->get_rchild()){ //只有右孩子
			if(root == node){  // 同时又是根节点
				node->get_rchild()->set_parent(NULL);
				this->set_root(node->get_rchild());
				//此种情况下不需要更新ltree_h/rtree_h/node_h信息
			}else{
				if(node == node->get_parent()->get_lchild()){//删除节点是左叶子结点
					node->get_rchild()->set_parent(node->get_parent());
					node->get_parent()->set_lchild(node->get_rchild());
					node->get_parent()->set_ltree_h(node->get_rchild()->get_node_h());
				}else if(node == node->get_parent()->get_rchild()){//删除节点是右叶子结点
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
		}else{  //删除节点既有左孩子，又有右孩子
			temp = node->get_rchild();
			while(temp){  //该循环找到删除节点右子树中最左边的结点，该节点的值将放到删除节点的位置
				replace = temp;
				temp = temp->get_lchild();
			}
			//替换节点不可能有左孩子，否则左孩子是替换节点
			if(replace == replace->get_parent()->get_lchild()){
				//替换节点是其父节点的左孩子
				replace->get_parent()->set_lchild(replace->get_rchild());
				if(replace->get_rchild()){
					replace->get_parent()->set_ltree_h(replace->get_rchild()->get_node_h());
				}else{
					replace->get_parent()->set_ltree_h(0);
				}				
			}else if(replace == replace->get_parent()->get_rchild()){
				//替换节点是其父节点的右孩子
				//这种情况是存在的:删除节点的右子树的每个节点都只有右子树
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
				//此时的replace节点是叶子结点	
			}
			node->set_data(replace->get_data());
			//if(root == node){}
			// 删除节点同时又是根节点，不需要处理，因为此时树不为空			
			replace->get_parent()->refresh_node_h();
			ret = this->refresh_height_from_current_node_to_root(replace->get_parent(), replace->get_parent()->get_node_h()-1);
		}
		return ret;
	}


	//将二叉排序树转换成平衡二叉排序树，同时保证转换后的
	//ltree_h/rtree_h/node_h信息的正确性
	template <class Type_Bstree>
	state BStree<Type_Bstree>::adjust_to_balanced_bstree(Bnode<Type_Bstree> *root){		
		state ret = OK;

		while(!this->is_balanced(root)){
			ret = adjust_to_balanced_bstree(root->get_lchild());
			ret |= adjust_to_balanced_bstree(root->get_rchild());

			sint32 rtree_h = 0, rltree_h = 0, rrtree_h = 0;  //右子树，右子树的左孩子，右子树的右孩子
			sint32 ltree_h = 0, lltree_h = 0, lrtree_h = 0;  //左子树，左子树的左孩子，左子树的右孩子
			Bnode<Type_Bstree> *l = NULL, *r = NULL, *temp = NULL;

			// 有可能存在两棵子树都平衡的情况下父节点不平衡的情况
			if(!this->is_balanced(root)){
				ltree_h = root->get_ltree_h();
				rtree_h = root->get_rtree_h();
				
				if(root->get_lchild()){  //如果有左子树
					l = root->get_lchild();
					lltree_h = l->get_ltree_h();
					lrtree_h = l->get_rtree_h();
				}
				if(root->get_rchild()){  //如果有右子树
					r = root->get_rchild();
					rltree_h = r->get_ltree_h();
					rrtree_h = r->get_rtree_h();
				}
				//第一个L表示root的左子树比右子树高。
				if(ltree_h > rtree_h){
					//第二个L表示root的左孩子的左子树比右子树高，
					//或者root的左孩子的左右子树等高。
					if(lltree_h >= lrtree_h){// LL型
						temp = this->right_rotate(root);
					}
					//第二个R表示root的左孩子的右子树比左子树高
					else{//LR型
						temp = this->leftright_rotate(root);
					}
				}
				//第一个R表示root的右子树比左子树高。
				else{
					//第二个R表示root的右孩子的右子树比左子树高，
					//或者root的右孩子的左右子树等高。
					if(rltree_h <= rrtree_h){// RR型
						temp = this->left_rotate(root);
					}
					//第二个L表示root的右孩子的左子树比右子树高。
					else{//RL型
						temp = this->rightleft_rotate(root);
					}
				}
				ret |= this->refresh_height_from_current_node_to_root(temp, temp->get_node_h()-1);
			}
		}
		return ret;
	}


	/*
		从一棵二叉排序树或者平衡二叉排序树中删除一个节点，
		保证删完后的树是一棵平衡二叉排序树
	*/
	template <class Type_Bstree>
	state BStree<Type_Bstree>::delete_node_pro(Bnode<Type_Bstree> *node){
		state ret = OK;

		//先得到一棵二叉排序树
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
			//再将二叉排序树转换成平衡二叉排序树
			if(OK != (ret = adjust_to_balanced_bstree(this->get_root()))){
				cout<<"[class Bstree] adjust_to_balanced_bstree failed, ret="<<ret<<endl;
			}
			return ret;			
		}
	}


	/*
		从一棵二叉排序树中删除一个节点，保证删完后的树
		仍是一棵二叉排序树
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
		if (right - left < 0 || NULL == addr || NULL == pdata){  // 没有数据
			return NULL;
		}else{
			Bnode<Type_Bstree> *root;
			Sort<Type_Bstree> sorted;
			Type_Bstree *pdata_temp = new Type_Bstree[right - left + 1];

			memcpy(pdata_temp, pdata + left, (right - left + 1)*sizeof(Type_Bstree));
			//先排序
			sorted.quick_sort(pdata_temp, 0, right - left);
			//二分贪心法构造
			root = bulid_balanced_bstree_recursive(pdata_temp, 0, right - left, addr);

			this->set_root(root);
			
			delete [] pdata_temp;

			return root;  //返回树的根节点
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
	void Sort<Type_Sort>::get_data_from_bstree(Bnode<Type_Sort> *root, vector<Type_Sort> &sorted){
		//if(NULL == root || NULL == sorted){} //不能判断引用是否为空
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

		Type_Sort *pdata_temp = pdata + left;  // 支持子数组
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
		Type_Sort *pdata_temp = pdata + left;  // 支持子数组
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
		Type_Sort *pdata_temp = pdata + left;  // 支持子数组
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

		Type_Sort *pdata_temp = pdata + left;  // 支持子数组
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

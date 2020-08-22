/******************************************************************************
FileName: 		mgeometry.cpp
Description:   	mgeometry definition
Author:   		Round Bridge
Date: 			2020.8.22
Modification History:
					2020.8.22 create file
Version: 		0.0.1
******************************************************************************/

#ifndef _MGEOMETRY_CPP_
#define _MGEOMETRY_CPP_

#include "mgeometry.h"

namespace mgeometry
{
	template <class Type_Point>
	ostream& operator <<(ostream& outputstream, const Point<Type_Point>& p){
		outputstream<<"("<<p.x<<", "<<p.y<<")";
		return outputstream;
	}
	
	//�������ã����������������Ĳ����ֵ���a = b = c;
	//�����ֵ���֮������Ч������Ϊ���ø�ֵ�������
	//�����á�����ʱҲ�������������ͱ���һ��
	template <class Type_Point>
	Point<Type_Point>& Point<Type_Point>::operator=(const Point<Type_Point>& rightside){
		this->x = rightside.x;
		this->y = rightside.y;
		return *this;
	}
	
	template <class Type_Point>
	Type_Point Point<Type_Point>::get_point_x() const{
		return this->x;			
	}

	template <class Type_Point>
	Type_Point Point<Type_Point>::get_point_y() const{
		return this->y;			
	}

	template <class Type_Point>
	void set_point(const Point<Type_Point>& a){
		this->x = a.x;
		this->y = a.y;
		return;
	}
}

#endif


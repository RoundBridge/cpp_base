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

	template <class Type_Point>
	bool operator ==(const Point<Type_Point>& p1, const Point<Type_Point>& p2){
		return((p1.get_point_x() == p2.get_point_x())&&(p1.get_point_y() == p2.get_point_y()));
	}


	template <class Type_Line>
	ostream& operator <<(ostream& outputstream, const Line<Type_Line>& l){
		outputstream<<"("<<l.A<<")x+("<<l.B<<")y+("<<l.C<<")=0";
		outputstream<<"   k="<<l.k<<",  b="<<l.b<<",  a="<<l.a;
		return outputstream;
	}

	template <class Type_Line>
	bool operator ==(const Line<Type_Line>& l1, const Line<Type_Line>& l2){
		return((l1.get_coefficient_A() == l2.get_coefficient_A())
			&&(l1.get_coefficient_B() == l2.get_coefficient_B())
			&&(l1.get_coefficient_C() == l2.get_coefficient_C()));
	}


	//返回引用，允许像下面这样的层叠赋值语句a = b = c;
	//层叠赋值语句之所以有效，是因为内置赋值运算符在
	//起作用。重载时也做到和内置类型保持一致
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
	void Point<Type_Point>::set_point(const Point<Type_Point>& a){
		this->x = a.x;
		this->y = a.y;
		return;
	}

	template <class Type_Point>
	sf8 Point<Type_Point>::distance_to_point(const Point<Type_Point>& p){
		return sqrt((p.x - this->x)*(p.x - this->x) + (p.y - this->y)*(p.y - this->y));
	}

	template <class Type_Point>
	sf8 Point<Type_Point>::distance_to_line_ex(const Line<Type_Point>& l){
		sf8 n = l.get_coefficient_A() * this->x + l.get_coefficient_B() * this->y + l.get_coefficient_C();
		sf8 d = sqrt(l.get_coefficient_A() * l.get_coefficient_A() + l.get_coefficient_B() * l.get_coefficient_B());
		return n/d;
	}

	template <class Type_Point>
	sf8 Point<Type_Point>::distance_to_line(const Line<Type_Point>& l){
		return fabs(distance_to_line_ex(l));
	}


	template <class Type_Line>
	Line<Type_Line>& Line<Type_Line>::operator =(const Line<Type_Line>& rightside){
		this->A = rightside.A;
		this->B = rightside.B;
		this->C = rightside.C;
		this->k = rightside.k;
		this->b = rightside.b;
		this->a = rightside.a;
		return *this;
	}

	template <class Type_Line>
	void Line<Type_Line>::compute_kba(){
		if(!is_valid_line()){
			this->k = 0.0;
			this->b = 0.0;
			this->a = 0.0;
			return;
		}
		if (0.0 == this->B){
			this->k = (this->A > 0.0)?-DBL_MAX:DBL_MAX;
			this->b = (this->C > 0.0)?-DBL_MAX:DBL_MAX;
		}else{
			this->k = this->A / this->B * (-1.0);
			this->b = this->C / this->B * (-1.0);
		}
		
		if (0.0 == this->A){
			this->a = (this->C > 0.0)?-DBL_MAX:DBL_MAX;
		}else{
			this->a = this->C / this->A * (-1.0);
		}
		return;
	}

	template <class Type_Line>
	Line<Type_Line>::Line(const Point<Type_Line>& p1, const Point<Type_Line>& p2){
		if(p1 == p2){
			A = 0.0;
			B = 0.0;
			C = 0.0;
		}else{
			A = p2.get_point_y() - p1.get_point_y();
			B = p1.get_point_x() - p2.get_point_x();
			C = p1.get_point_y() * p2.get_point_x() - p2.get_point_y() * p1.get_point_x();
		}
		compute_kba();
	}
}

#endif


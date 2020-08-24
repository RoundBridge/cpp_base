/******************************************************************************
FileName: 		mgeometry.h
Description:   	header file
Author:   		Round Bridge
Date: 			2020.8.22
Modification History:
					2020.8.22 create file
Version: 		0.0.1
******************************************************************************/

#ifndef _MGEOMETRY_H_
#define _MGEOMETRY_H_

#include <cmath>
#include <iostream>
#include "types.h"
#include "float.h"

using std::ostream;

namespace mgeometry
{
	//友元模板函数需要先声明下，不然链接出错
	template <class Type_Point>	class Point;
	template <class Type_Point>
	ostream& operator <<(ostream& outputstream, const Point<Type_Point>& p);

	template <class Type_Line>	class Line;
	template <class Type_Line>
	ostream& operator <<(ostream& outputstream, const Line<Type_Line>& l);

	
	class Geometry{
	public:
		virtual sf8 length() const=0;
		virtual sf8 area() const=0;
		virtual sf8 volume() const=0;
	};


	template <class Type_Point>
	class Point{
	public:
		Point(Type_Point a=(Type_Point)0, Type_Point b=(Type_Point)0):x(a),y(b){}
		Point(const Point<Type_Point>& a){x=a.x; y=a.y;}
		Point<Type_Point>& operator =(const Point<Type_Point>& rightside);
		friend ostream& operator << <Type_Point>(ostream& outputstream, const Point<Type_Point>& p);
		virtual ~Point(){}
		Type_Point get_point_x() const;  //const表示不能改变调用对象的值
		Type_Point get_point_y() const;
		void set_point(const Point<Type_Point>& a);
		sf8 distance_to_line_ex(const Line<Type_Point>& l); //带符号，有正负
		sf8 distance_to_line(const Line<Type_Point>& l);
		sf8 distance_to_point(const Point<Type_Point>& p);
	private:
		Type_Point x;
		Type_Point y;
	};


	template <class Type_Line>
	class Line{
	public:
		Line(sf8 a=0.0, sf8 b=0.0, sf8 c=0.0):A(a),B(b),C(c){compute_kba();}
		Line(const Point<Type_Line>& p1, const Point<Type_Line>& p2);
		virtual ~Line(){}
		/*
			当在类中声明并定义了一个普通的公共成员函数，
			即如果下面的get_coefficient_A()函数后面不加const，
			在其他函数里定义了一个此类的常对象，如果试
			图使常对象调用非”常成员函数“就会产生如下
			问题:		
		 		error: 不能讲this指针从"const classtype" 转换为 "classtype &"?	
			解决方案是将成员函数定义为常成员函数（常成员
			函数保证调用此函数的对象不会被改变?
		*/
		sf8 get_coefficient_A()const{return A;} //常成员函数保证调用此函数的对象不会被改变
		sf8 get_coefficient_B()const{return B;}
		sf8 get_coefficient_C()const{return C;}
		sf8 get_coefficient_k()const{return k;}
		sf8 get_coefficient_b()const{return b;}
		sf8 get_coefficient_a()const{return a;}

		Line<Type_Line>& operator =(const Line<Type_Line>& rightside);
		friend ostream& operator << <Type_Line>(ostream& outputstream, const Line<Type_Line>& l);
		bool is_valid_line(){return !((A==0.0)&&(B==0.0));}
		
	private:
		void compute_kba();
		sf8 A;
		sf8 B;
		sf8 C;
		sf8 k;  //斜率
		sf8 b;  //纵截距
		sf8 a;  //横截距
	};
}


#endif


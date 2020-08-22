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

#include <iostream>
#include "types.h"

using std::ostream;

namespace mgeometry
{
	//友元模板函数需要先声明下，不然链接出错
	template <class Type_Point>	class Point;
	template <class Type_Point>
	ostream& operator <<(ostream& outputstream, const Point<Type_Point>& p);
	
	class Geometry{
	public:
		virtual double length() const=0;
		virtual double area() const=0;
		virtual double volume() const=0;
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
	private:
		Type_Point x;
		Type_Point y;
	};

}


#endif


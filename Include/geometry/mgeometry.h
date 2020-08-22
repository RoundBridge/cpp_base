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

#include "types.h"

namespace mgeometry
{
	class Geometry{
	public:
		virtual double length() const=0;
		virtual double area() const=0;
		virtual double volume() const=0;
	};

	template <class Type_Point>
	class Point{
	public:
		Point(){x=(Type_Point)0; y=(Type_Point)0;}
		Point(Type_Point a, Type_Point b){x=a; y=b;}
		Point(const Point<Type_Point>& a){x=a.x; y=a.y;}
		Point<Type_Point>& operator=(const Point<Type_Point>& rightside);
		virtual ~Point(){}
		Type_Point get_point_x() const;  //const��ʾ���ܸı���ö����ֵ
		Type_Point get_point_y() const;
		void set_point(const Point<Type_Point>& a);
	private:
		Type_Point x;
		Type_Point y;
	};

}


#endif


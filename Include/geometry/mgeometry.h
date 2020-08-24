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
	//��Ԫģ�庯����Ҫ�������£���Ȼ���ӳ���
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
		Type_Point get_point_x() const;  //const��ʾ���ܸı���ö����ֵ
		Type_Point get_point_y() const;
		void set_point(const Point<Type_Point>& a);
		sf8 distance_to_line_ex(const Line<Type_Point>& l); //�����ţ�������
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
			��������������������һ����ͨ�Ĺ�����Ա������
			����������get_coefficient_A()�������治��const��
			�����������ﶨ����һ������ĳ����������
			ͼʹ��������÷ǡ�����Ա�������ͻ��������
			����:		
		 		error: ���ܽ�thisָ���"const classtype" ת��Ϊ "classtype &"?	
			��������ǽ���Ա��������Ϊ����Ա����������Ա
			������֤���ô˺����Ķ��󲻻ᱻ�ı�?
		*/
		sf8 get_coefficient_A()const{return A;} //����Ա������֤���ô˺����Ķ��󲻻ᱻ�ı�
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
		sf8 k;  //б��
		sf8 b;  //�ݽؾ�
		sf8 a;  //��ؾ�
	};
}


#endif


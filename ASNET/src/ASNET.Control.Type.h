#pragma once
#include"ASNET.Graph.h"

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG


namespace ASNET {
	namespace Control {

		//简单的Color类，和D2D1::Color兼容
		class Color {
		public:
			float r, g, b, a;
			//默认构造函数
			Color();
			//D2D1::Color的赋值
			Color(ASNET::Graph::Color color);
			//D2D1::Color的枚举赋值
			Color(ASNET::Graph::Color::Enum color);
			//赋值
			Color(float _r, float _g, float _b, float _a);
			//赋值
			Color(ASNET::Graph::Color color, float _a);

			//返回D2D1::Color类型
			operator ASNET::Graph::Color();

			//向量减法
			ASNET::Control::Color operator-(ASNET::Control::Color color);
			//向量加法
			ASNET::Control::Color operator+(ASNET::Control::Color color);
			//向量乘法
			ASNET::Control::Color operator*(float scale);

		};
	}
}
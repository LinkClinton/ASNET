#pragma once
#include"ASNET.Graph.h"

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG


namespace ASNET {
	namespace Control {

		//�򵥵�Color�࣬��D2D1::Color����
		class Color {
		public:
			float r, g, b, a;
			//Ĭ�Ϲ��캯��
			Color();
			//D2D1::Color�ĸ�ֵ
			Color(ASNET::Graph::Color color);
			//D2D1::Color��ö�ٸ�ֵ
			Color(ASNET::Graph::Color::Enum color);
			//��ֵ
			Color(float _r, float _g, float _b, float _a);
			//��ֵ
			Color(ASNET::Graph::Color color, float _a);

			//����D2D1::Color����
			operator ASNET::Graph::Color();

			//��������
			ASNET::Control::Color operator-(ASNET::Control::Color color);
			//�����ӷ�
			ASNET::Control::Color operator+(ASNET::Control::Color color);
			//�����˷�
			ASNET::Control::Color operator*(float scale);

		};
	}
}
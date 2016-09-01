#pragma once

#include"ASNET.Control.h"


//�򵥵Ŀؼ�Label
//�̳���Control
//���IsShowû�б�����Ϊtrue�Ļ�Ҳ���޷����Ƴ�����
namespace ASNET {
	namespace Control {
		

		class Label:public Control {
		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
		public:

			wchar_t*                 Name; //Label������
			wchar_t*                 Text; //Label�ı�������

			bool                     IsCanSelect; //������䷶Χ�ڵ�ʱ���Ƿ���ʾѡ��

			ASNET::Control::Color    BackColor; //������ɫ
			ASNET::Control::Color    TextColor; //�ı���ɫ

			ASNET::Graph::Font*      TextFont; //ʹ�õ�����

			ASNET::Graph::TextAlign  Horizontal; //�ı����Ű�
			ASNET::Graph::TextAlign  Vertical; //�ı����Ű�
		public:
			Label(ASNET::Graph::Graph* graph,
				float left, float right, float top, float bottom,
				wchar_t* name, wchar_t* text, wchar_t* fontface, float fontsize,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Center,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Center);
			~Label();

			

			void reset(wchar_t* fontface, float fontsize);


		};
	}
}


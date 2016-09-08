#pragma once

#include"ASNET.Control.h"


//�򵥵Ŀؼ�Label
//�̳���Control
//���IsShowû�б�����Ϊtrue�Ļ�Ҳ���޷����Ƴ�����
namespace ASNET {
	namespace Control {
		
		//�򵥵�Label��
		class Label:public Control {
		protected:
			//���ƺ���������������ؼ��Ļ��Ʒ���
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override; 
		public:

			wchar_t*                 Name; //Label������
			wchar_t*                 Text; //Label�ı�������

			bool                     Selectibility; //������䷶Χ�ڵ�ʱ���Ƿ���ʾ�߿��ʾѡ��

			ASNET::Control::Color    BackColor; //������ɫ
			ASNET::Control::Color    TextColor; //�ı���ɫ

			ASNET::Graph::Font*      TextFont; //ʹ�õ�����

			ASNET::Graph::TextAlign  Horizontal; //�ı���ƽ�з�����Ű�
			ASNET::Graph::TextAlign  Vertical; //�ı�����ֱ������Ű�
		public:
			//���캯������������ؼ�
			Label(ASNET::Graph::Graph* graph,
				float left, float right, float top, float bottom,
				wchar_t* name, wchar_t* text, wchar_t* fontface, float fontsize,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Center,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Center);
			//�����������ǵ�delete
			~Label();

			//������������������С
			void reset(wchar_t* fontface, float fontsize);


		};
	}
}


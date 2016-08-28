#pragma once

#include"ASNET.Control.Base.h"

#include<memory>

//�򵥵Ŀؼ�Label
//�̳���Control
//��OnDraw���ǻ��ƿؼ��Ĵ��룬����ĳ��ԭ��
//���ƿؼ��Ĵ���Ҫ�Լ��������ƺ����е���
//���IsShowû�б�����Ϊtrue�Ļ�Ҳ���޷����Ƴ�����
namespace ASNET {
	namespace Control {
		

		class Label:public Control {
		protected:
		
			
		public:

			wchar_t*                 Name;
			wchar_t*                 Text;

			ASNET::Control::Color    BackColor;
			ASNET::Control::Color    TextColor;

			ASNET::Graph::Font*      TextFont;

			ASNET::Graph::TextAlign  Horizontal;
			ASNET::Graph::TextAlign  Vertical;
		public:
			Label(ASNET::Graph::Graph* graph,
				float left, float right, float top, float bottom,
				wchar_t* name, wchar_t* text, wchar_t* fontface, float fontsize,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Center,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Center);
			~Label();

			//Draw the label
			void OnDraw(void* sender, ASNET::Graph::Graph* graph);

			void reset(wchar_t* fontface, float fontsize);

			
		};


	}
}
#pragma once

#include"ASNET.Control.h"

#include<memory>

//�򵥵Ŀؼ�Label
//�̳���Control
//���IsShowû�б�����Ϊtrue�Ļ�Ҳ���޷����Ƴ�����
namespace ASNET {
	namespace Control {
		

		class Label:public Control {
		protected:
		
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
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

		

			void reset(wchar_t* fontface, float fontsize);

			
		};


	}
}
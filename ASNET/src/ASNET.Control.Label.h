#pragma once

#include"ASNET.Control.Base.h"

#include<memory>

//简单的控件Label
//继承自Control
//在OnDraw中是绘制控件的代码，由于某种原因
//绘制控件的代码要自己在主绘制函数中调用
//如果IsShow没有被设置为true的话也是无法绘制出来的
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
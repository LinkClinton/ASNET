#pragma once

#include"ASNET.Control.h"


//简单的控件Label
//继承自Control
//如果IsShow没有被设置为true的话也是无法绘制出来的
namespace ASNET {
	namespace Control {
		

		class Label:public Control {
		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
		public:

			wchar_t*                 Name; //Label的名字
			wchar_t*                 Text; //Label文本的内容

			bool                     IsCanSelect; //鼠标在其范围内的时候是否显示选中

			ASNET::Control::Color    BackColor; //背景颜色
			ASNET::Control::Color    TextColor; //文本颜色

			ASNET::Graph::Font*      TextFont; //使用的字体

			ASNET::Graph::TextAlign  Horizontal; //文本的排版
			ASNET::Graph::TextAlign  Vertical; //文本的排版
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


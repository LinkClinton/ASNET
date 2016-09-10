#pragma once
#include"ASNET.Control.h"


//简单的按钮类
namespace ASNET {
	namespace Control {

		//按钮风格
		enum class ButtonStyle {
			Simple
		};


		//简单的按钮类
		class Button :public Control {
		private:
			//Simple类型的按钮绘制方案
			void SimpleDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		protected:
			bool					 IsKeyDown; //是否被按下
		protected:
			//描述如何绘制
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
			//当鼠标按钮弹起的时候触发
			void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//当鼠标按钮按下的时候触发
			void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			//当键盘按键按下的时候触发
			void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//当键盘按键弹起的时候触发
			void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		public:
			wchar_t*				 Name;//按钮的名字
			wchar_t*				 Text;//按钮的文本内容


			ButtonStyle              Style; //按钮的风格

			
			ASNET::Control::Color    TextColor; //文本颜色

			ASNET::Graph::Font*      TextFont;  //使用的字体


			ASNET::Graph::TextAlign  Horizontal; //文本的平行方向的排版
			ASNET::Graph::TextAlign  Vertical; //文本的竖直方向的排版

		public:
			//构造函数
			Button(ASNET::Graph::Graph* graph,
				float left, float right, float top,
				float bottom, wchar_t* name, wchar_t* text, ASNET::Graph::Font* font,
				ASNET::Control::ButtonStyle style = ASNET::Control::ButtonStyle::Simple,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Center,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Center);
			//记得delete
			~Button(); 



			
		};


	}
}
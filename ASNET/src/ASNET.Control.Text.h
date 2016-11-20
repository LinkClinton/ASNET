#pragma once

#include"ASNET.Control.h"

namespace ASNET {

	namespace Control {

	
		//文本控件，一般作为一个控件的内容，而不是单独的控件
		class Text {
		private:
			ASNET::Graph::Graph*    ParentGraph; //渲染的类
			ASNET::Graph::Interface ParentInterface; //渲染接口

			IDWriteTextLayout*    g_text; //文本布局
			ID2D1SolidColorBrush* g_brush; //画刷

			ASNET::Graph::Word    g_word; //文本内容
			ASNET::Graph::Size    g_size; //文本框大小
			ASNET::Graph::Color   g_color; //文本颜色

			int				      g_cursor_pos; //光标位置
			bool                  g_cursor_show; //文本是否显示
			bool				  g_cursor_direct;//文本方向，true代表在当前字符的左边


			int					  g_text_left_pos; //用于文本裁剪，将设置文本最左边显示的位置
			int                   g_text_right_pos; //用于文本裁剪，将设置文本最右边的显示的位置
			bool                  g_text_clip; //是否使用文本裁剪
		protected:
			void InitalizeCursorAnimation(); //初始化光标动画

			ASNET::Control::Animation CursorAnimation; //光标动画
		private:
			void UpdateText(); //更新文本布局
			void UpdateColor(); //更新文本画刷
			void DrawCursor(ASNET::Graph::Point origin); //绘制光标
		public:
			//构造函数
			Text(ASNET::Graph::Graph* graph, ASNET::Graph::Word word,
				ASNET::Graph::Size size, ASNET::Graph::Font* fontface,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			//设置文本内容
			void SetWord(ASNET::Graph::Word word);

			//设置文本颜色
			void SetColor(ASNET::Graph::Color color);
			
			//是否启用文本裁剪
			void SetClip(bool is);

			//设置左边部分的文本裁剪
			void SetLeftClip(int left);

			//设置右边部分的文本裁剪
			void SetRightClip(int right);
			
			//返回文本内容
			auto GetWord()->ASNET::Graph::Word;
			
			//返回文本颜色
			auto GetColor()->ASNET::Graph::Color;

			//返回某个字符的像素位置
			auto GetRealX(int textposition = 0)->float;
			
			//返回某个字符的像素位置
			auto GetRealY(int textposition = 0)->float;
			
			//返回某个字符的像素位置
			auto GetRealPosition(int textposition = 0, bool isleft = false)->ASNET::Graph::Point;

			//返回文本的高度
			auto GetHeight()->float;
			
			//返回距离这个像素点最近的字符的位置，坐标系相对于文本
			auto GetTextPosition(ASNET::Graph::Point point)->int;

			//绘制自己
			void OnDraw(ASNET::Graph::Point origin);

			ASNET::Graph::TextAlign Horizontal; //布局
			ASNET::Graph::TextAlign Vertical; //布局

			ASNET::Graph::Font* FontFace; //字体
			
			//插入一个字符
			void Insert(wchar_t buff);

			//删除一个字符
			void Delete();

			//显示光标
			void CursorShow(); 

			//隐藏光标
			void CursorHide();

			//光标往上移动
			void CursorUp();

			//光标往左移动
			void CursorLeft();

			//光标往下移动
			void CursorDown();

			//光标往右移动
			void CuesorRight();
			
			//设置光标的位置
			void SetCursorPosition(int textposition = 0 , bool IsLeft = false);

			//设置光标的位置，将设置到距离point最近的字符的位置,坐标系相对于文本
			void SetCursorPosition(ASNET::Graph::Point point);



			static auto KeycodeToWideChar(void* sender, ASNET::Keycode keycode)->wchar_t;
		};

	}

}
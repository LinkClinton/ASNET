#pragma once

#include<map>
#include<vector>
#include<functional>
#ifdef _WINDOWS7
#include<d2d1.h>
#else 
#include<d2d1_1.h>
#endif // _WINDOWS7


#include<d3d11.h>
#include<dwrite.h>
#include<wincodec.h>

#include"ASNET.Control.Timer.h"

#include"ASNET.Physics.h"

namespace ASNET {

	namespace Graph {

		class Graph;


		typedef D2D_RECT_F		 Rect; //源自D2D_RECT_F
		typedef D2D_SIZE_F       Size; //源自D2D_SIZE_F
		typedef D2D_POINT_2F     Point; //源自D2D_POINT_2F
		typedef std::wstring     Word; //源自wstring


		class Color :public ASNET::Physics::Vector4 {
		public:
			Color();

			Color(Color color, float a);

			Color(D2D1::ColorF::Enum color);

			Color(ASNET::Physics::Vector4 vector4);

			Color(float r, float g, float b, float a);

			operator D2D1::ColorF();

		};


		//字体
		class Font {
		private:
			ASNET::Graph::Graph* ParentGraph; //渲染用的指针接口

			IDWriteTextFormat*	 textformat; //textformat
			friend class Graph;
		public:
			//构造函数
			Font(ASNET::Graph::Graph* Graph);
			
			//析构函数，记得delete
			~Font();
			
			//返回字体大小
			auto FontSize()->float;
			
			//重新加载字体
			void reset(ASNET::Graph::Word fontname, float fontsize);

			operator IDWriteTextFormat*();
		};


		//图片
		class Image {
		protected:
			ASNET::Graph::Graph* ParentGraph; //渲染用的指针接口
			ID2D1Bitmap* bitmap; //位图缓存

			friend class Graph;

			Image() = default;
		public:
			//构造函数
			Image(ASNET::Graph::Graph* Graph);
			
			//析构函数
			~Image();
			
			//返回图片宽度
			auto GetWidth()->float;
			
			//返回图片高度
			auto GetHieght()->float;
			
			//重新加载图片
			void reset(ASNET::Graph::Word filename);
		};


		//字体布局
		enum class TextAlign {
			Left, Center, Right, Top, Bottom
		};

		//提供一个面，单独作为一个坐标
		class Surface {
		private:
			ASNET::Graph::Graph* ParentGraph; //渲染接口
		protected:
			float g_width; //宽度
			float g_height; //高度
			float x; //位置x
			float y; //位置y

			void BeginDraw(); //开始绘制
			void EndDraw(); //结束绘制
		public:
			//构造函数
			Surface(ASNET::Graph::Graph* graph); 

			//绘制线
			virtual void DrawLine(ASNET::Graph::Point p1, ASNET::Graph::Point p2,
				ASNET::Graph::Color color, float width = 1.0f);

			//绘制矩形
			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = D2D1::ColorF::White);

			//绘制图片
			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);

			//绘制文字
			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			//返回宽度
			auto Width()->float;

			//返回高度
			auto Height()->float;

			//返回位置x
			auto PositionX()->float;

			//返回位置y
			auto PositionY()->float;

			//设置宽度
			void SetWidth(float width);

			//设置高度
			void SetHeight(float height);

			//设置位置x
			void SetPositionX(float posx);

			//设置位置Y
			void SetPositionY(float posy);

		};

		//接口，用于获取Graph内部的接口
		class Interface {
		public:
			ID2D1RenderTarget*   DeviceContext2D;
			ID3D11DeviceContext* DeviceContext3D;
			IDWriteFactory*      DeviceContextWrite;
		};
		

	}

}
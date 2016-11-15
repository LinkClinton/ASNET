#pragma once

#include<map>
#include<vector>
#include<functional>

#include<d2d1.h>
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
			ASNET::Graph::Graph* ParentGraph;
		protected:
			float g_width;
			float g_height;
			float x;
			float y;

			void BeginDraw();
			void EndDraw();
		public:
			Surface(ASNET::Graph::Graph* graph);

			virtual void DrawLine(ASNET::Graph::Point p1, ASNET::Graph::Point p2,
				ASNET::Graph::Color color, float width = 1.0f);

			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = D2D1::ColorF::White);

			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);

			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			auto Width()->float;
			auto Height()->float;
			auto PositionX()->float;
			auto PositionY()->float;

			void SetWidth(float width);
			void SetHeight(float height);
			void SetPositionX(float posx);
			void SetPositionY(float posy);

		};

		class Interface {
		public:
			ID2D1RenderTarget*   DeviceContext2D;
			ID3D11DeviceContext* DeviceContext3D;
			IDWriteFactory*      DeviceContextWrite;
		};
		

	}

}
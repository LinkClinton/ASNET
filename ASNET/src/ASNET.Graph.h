#pragma once
#include<vector>
#include<functional>

#include<d2d1.h>
#include<d3d11.h>
#include<dwrite.h>
#include<wincodec.h>

#include"ASNET.Control.Timer.h"

#undef LoadImage

//简单的2D绘制的类
//基本是用Direct2D做的
//因为某种坑的原因，使用的是d2d1而不是d2d1_1
//同样其所有的资源文件创建的时候保持其nullptr，因为会在加载的时候将其创建
//注意不用的时候delete
namespace ASNET {
	//class Window;
	namespace Graph {
		class Graph;


		typedef D2D_RECT_F		 Rect;
		typedef D2D1::ColorF     Color;
		typedef D2D_POINT_2F     Point;
		typedef wchar_t*         Word;

		

		class Font {
		private:
			ASNET::Graph::Graph* ParentGraph;

			IDWriteTextFormat*	 textformat;
			friend class Graph;
		public:
			Font(ASNET::Graph::Graph* Graph);
			~Font();
			auto FontSize()->float;

			void reset(ASNET::Graph::Word fontname, float fontsize);
		};



		class Image {
		private:
			ASNET::Graph::Graph* ParentGraph;

			ID2D1Bitmap* bitmap;
			friend class Graph;
		public:
			Image(ASNET::Graph::Graph* Graph);
			~Image();
			auto GetWidth()->float;
			auto GetHieght()->float;

			void reset(ASNET::Graph::Word filename);
		};

		enum class TextAlign {
			Left, Center, Right, Top, Bottom
		};

		class Graph {
		protected:
			//Information
			HWND					g_hwnd; 
			int						g_width;
			int						g_height;
			bool					g_windowed;
		protected:
			//Direct2D
			ID2D1Factory*			g_factory;

			ID2D1RenderTarget*      g_devicecontext2d;

			//d2d1_1
			//ID2D1Device*            g_device2d;
			//ID2D1DeviceContext*     g_devicecontext2d;

			//Direct3D11
			ID3D11Device*			g_device3d;
			IDXGISwapChain*			g_swapchain;
			ID3D11DeviceContext*    g_devicecontext3d;
			ID3D11RenderTargetView* g_rendertargetview;
			ID3D11DepthStencilView* g_depthstencilview;

			//Dwrite
			IDWriteFactory*			g_writefactory;

			//IWIC
			IWICImagingFactory*     g_imagefactory;
			friend class Window;
			friend class Image;
			friend class Font;
			void Initalize(HWND hwnd, bool IsWindowed);
		protected:
			ASNET::Control::Timer   g_timer;
			float					g_render_time;
		public:
			Graph();
			Graph(HWND hwnd, bool IsWindowed = true);
			~Graph();
			void Clear(ASNET::Graph::Color color = ASNET::Graph::Color::White);

			void Present();

			auto FPS()->float;

			auto RenderTime()->float;

			virtual void DrawLine(ASNET::Graph::Point P1,
				ASNET::Graph::Point P2, ASNET::Graph::Color color, float width = 1.0f);

			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = ASNET::Graph::Color::White);

			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);

			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = ASNET::Graph::Color::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);
			
			virtual void LoadImage(ASNET::Graph::Word filename,
				ASNET::Graph::Image* &image);

			virtual void LoadFont(ASNET::Graph::Font* &font,
				ASNET::Graph::Word fontname, float fontsize);



		};
	

		typedef std::function<void(void*, ASNET::Graph::Graph*)> EventGraphDrawHandler;
		

	}
}


#pragma once

#include<d2d1_1.h>
#include<dwrite.h>
#include<d3d11.h>
#undef LoadImage
namespace ASNET {
	namespace Graph {

		typedef D2D_RECT_F		 Rect;
		typedef D2D1::ColorF     Color;
		typedef D2D_POINT_2F     Point;
		typedef wchar_t*         Word;

		struct Font {
		private:
			IDWriteTextFormat* textformat;
		public:
			Font();
			~Font();
			auto FontSize()->int;
		};

		struct Image {
		private:
			ID2D1Bitmap* bitmap;
		public:
			Image();
			~Image();
			auto GetWidth()->float;
			auto GetHieght()->float;
		};

		enum class TextAlign {
			Left, Center, Right, Up, Down
		};

		class Graph {
		protected:
			HWND					g_hwnd; 
			int						g_width;
			int						g_height;
			bool					g_windowed;
		protected:
			//Direct2D
			ID2D1Factory1*			g_factory;
			ID2D1Device*            g_device2d;
			ID2D1RenderTarget*		g_rendertarget;
			ID2D1DeviceContext*     g_devicecontext2d;

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
		public:
			Graph(HWND hwnd, int width, int height, bool IsWindowed = true);

			void BeginDraw();

			void EndDraw();

			void DrawLine(ASNET::Graph::Point P1,
				ASNET::Graph::Point P2, ASNET::Graph::Color Color, int width = 1.0f);

			void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color Color, int width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = ASNET::Graph::Color::White);

			void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);

			void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Up);
			
			void LoadImage(ASNET::Graph::Image* image);

			void LoadFont(ASNET::Graph::Font* font, ASNET::Graph::Word fontname,
				int fontsize);



		};
	}
}
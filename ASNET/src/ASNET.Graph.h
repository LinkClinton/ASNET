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


		typedef D2D_RECT_F		 Rect; //源自D2D_RECT_F
		typedef D2D1::ColorF     Color; //源自D2D1::ColorF
		typedef D2D_POINT_2F     Point; //源自D2D_POINT_2F
		typedef wchar_t*         Word; //源自wchar_t*

		
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
		};


		//图片
		class Image {
		private:
			ASNET::Graph::Graph* ParentGraph; //渲染用的指针接口

			ID2D1Bitmap* bitmap; //位图缓存
			friend class Graph; 
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

		class Graph {
		protected:
			//Information
			HWND					g_hwnd;   //句柄
			int						g_width; //宽度
			int						g_height; //高度
			bool					g_windowed; //是否使窗口化
		protected:
			//Direct2D 
			ID2D1Factory*			g_factory; //Direct2D Factory

			ID2D1RenderTarget*      g_devicecontext2d; //Direct2D DeviceContext

			//d2d1_1
			//ID2D1Device*            g_device2d;
			//ID2D1DeviceContext*     g_devicecontext2d;

			//Direct3D11
			ID3D11Device*			g_device3d; //Direct3D Device
			IDXGISwapChain*			g_swapchain; //DXGI SwapChain
			ID3D11DeviceContext*    g_devicecontext3d; //Direct3D DeviceContext
			ID3D11RenderTargetView* g_rendertargetview; //Direct3D RenderTargetView
			ID3D11DepthStencilView* g_depthstencilview; //Direct3D DepthStencilView

			//Dwrite
			IDWriteFactory*			g_writefactory; //DWrite Factory

			//IWIC
			IWICImagingFactory*     g_imagefactory; //Image Factory
			friend class Window;
			friend class Image;
			friend class Font;
			//初始化函数
			void Initalize(HWND hwnd, bool IsWindowed);
		protected:
			ASNET::Control::Timer   g_timer; //计时器
			float					g_render_time; //上一帧渲染用的时间
		public:
			//构造函数
			Graph();
			//构造函数
			Graph(HWND hwnd, bool IsWindowed = true);
			//析构函数
			~Graph();
			//清理
			void Clear(ASNET::Graph::Color color = ASNET::Graph::Color::White);
			//刷新
			void Present();
			//返回FPS
			auto FPS()->float;
			//返回渲染一帧用的时间
			auto RenderTime()->float;

			//绘制线
			virtual void DrawLine(ASNET::Graph::Point P1,
				ASNET::Graph::Point P2, ASNET::Graph::Color color, float width = 1.0f);
			//绘制矩形
			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = ASNET::Graph::Color::White);
			//绘制图片
			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);
			//绘制文本
			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = ASNET::Graph::Color::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);
			//加载图片
			virtual void LoadImage(ASNET::Graph::Word filename,
				ASNET::Graph::Image* &image);
			//加载字体
			virtual void LoadFont(ASNET::Graph::Font* &font,
				ASNET::Graph::Word fontname, float fontsize);



		};
	

		typedef std::function<void(void*, ASNET::Graph::Graph*)> EventGraphDrawHandler;
		

	}
}


#include"ASNET.Graph.Direct3D.h"
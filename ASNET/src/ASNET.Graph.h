#pragma once
#include<vector>
#include<functional>

#include<d2d1.h>
#include<d3d11.h>
#include<dwrite.h>
#include<wincodec.h>

#include"ASNET.Control.Timer.h"

#undef LoadImage

//�򵥵�2D���Ƶ���
//��������Direct2D����
//��Ϊĳ�ֿӵ�ԭ��ʹ�õ���d2d1������d2d1_1
//ͬ�������е���Դ�ļ�������ʱ�򱣳���nullptr����Ϊ���ڼ��ص�ʱ���䴴��
//ע�ⲻ�õ�ʱ��delete
namespace ASNET {
	//class Window;
	namespace Graph {
		class Graph;


		typedef D2D_RECT_F		 Rect; //Դ��D2D_RECT_F
		typedef D2D1::ColorF     Color; //Դ��D2D1::ColorF
		typedef D2D_POINT_2F     Point; //Դ��D2D_POINT_2F
		typedef wchar_t*         Word; //Դ��wchar_t*

		
		//����
		class Font {
		private:
			ASNET::Graph::Graph* ParentGraph; //��Ⱦ�õ�ָ��ӿ�

			IDWriteTextFormat*	 textformat; //textformat
			friend class Graph;
		public:
			//���캯��
			Font(ASNET::Graph::Graph* Graph);
			//�����������ǵ�delete
			~Font();
			//���������С
			auto FontSize()->float;
			//���¼�������
			void reset(ASNET::Graph::Word fontname, float fontsize);
		};


		//ͼƬ
		class Image {
		private:
			ASNET::Graph::Graph* ParentGraph; //��Ⱦ�õ�ָ��ӿ�

			ID2D1Bitmap* bitmap; //λͼ����
			friend class Graph; 
		public:
			//���캯��
			Image(ASNET::Graph::Graph* Graph);
			//��������
			~Image();
			//����ͼƬ���
			auto GetWidth()->float;
			//����ͼƬ�߶�
			auto GetHieght()->float;
			//���¼���ͼƬ
			void reset(ASNET::Graph::Word filename);
		};

		//���岼��
		enum class TextAlign {
			Left, Center, Right, Top, Bottom
		};

		class Graph {
		protected:
			//Information
			HWND					g_hwnd;   //���
			int						g_width; //���
			int						g_height; //�߶�
			bool					g_windowed; //�Ƿ�ʹ���ڻ�
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
			//��ʼ������
			void Initalize(HWND hwnd, bool IsWindowed);
		protected:
			ASNET::Control::Timer   g_timer; //��ʱ��
			float					g_render_time; //��һ֡��Ⱦ�õ�ʱ��
		public:
			//���캯��
			Graph();
			//���캯��
			Graph(HWND hwnd, bool IsWindowed = true);
			//��������
			~Graph();
			//����
			void Clear(ASNET::Graph::Color color = ASNET::Graph::Color::White);
			//ˢ��
			void Present();
			//����FPS
			auto FPS()->float;
			//������Ⱦһ֡�õ�ʱ��
			auto RenderTime()->float;

			//������
			virtual void DrawLine(ASNET::Graph::Point P1,
				ASNET::Graph::Point P2, ASNET::Graph::Color color, float width = 1.0f);
			//���ƾ���
			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = ASNET::Graph::Color::White);
			//����ͼƬ
			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);
			//�����ı�
			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = ASNET::Graph::Color::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);
			//����ͼƬ
			virtual void LoadImage(ASNET::Graph::Word filename,
				ASNET::Graph::Image* &image);
			//��������
			virtual void LoadFont(ASNET::Graph::Font* &font,
				ASNET::Graph::Word fontname, float fontsize);



		};
	

		typedef std::function<void(void*, ASNET::Graph::Graph*)> EventGraphDrawHandler;
		

	}
}


#include"ASNET.Graph.Direct3D.h"
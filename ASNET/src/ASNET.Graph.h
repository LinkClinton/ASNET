#pragma once


#include"ASNET.Graph.Graphics.h"

#undef LoadImage

/*
* �򵥵�2D���Ƶ���
* ��������Direct2D����
* ��Ϊĳ�ֿӵ�ԭ��ʹ�õ���d2d1������d2d1_1
* ͬ�������е���Դ�ļ�������ʱ�򱣳���nullptr����Ϊ���ڼ��ص�ʱ���䴴��
* ע�ⲻ�õ�ʱ��delete
*/

namespace ASNET {
	class Window;
	namespace Graph {
		
		class Graph {
		protected:
			//Information
			HWND					g_hwnd;   //���
			int						g_width; //���
			int						g_height; //�߶�
			bool					g_windowed; //�Ƿ�ʹ���ڻ�
			float					g_dpix; //
			float					g_dpiy;
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
			friend class Surface;
			friend class Window;
			friend class Image;
			friend class Font;
			//��ʼ������
			void Initalize(HWND hwnd, bool IsWindowed);
			//���캯��
			Graph();
		protected:
			ASNET::Control::Timer   g_timer; //��ʱ��
			float					g_render_time; //��һ֡��Ⱦ�õ�ʱ��
		public:
			//���캯��
			Graph(HWND hwnd, bool IsWindowed = true);
			//��������
			~Graph();
			//����
			void Clear(ASNET::Graph::Color color = D2D1::ColorF::White);
			//ˢ��
			void Present();
			//����FPS
			auto FPS()->float;
			//������Ⱦһ֡�õ�ʱ��
			auto RenderTime()->float;
			//
			auto GetDpiX()->float;
			//
			auto GetDpiY()->float;

			
			//������
			virtual void DrawLine(ASNET::Graph::Point P1,
				ASNET::Graph::Point P2, ASNET::Graph::Color color, float width = 1.0f);
			//���ƾ���
			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = D2D1::ColorF::White);
			//����ͼƬ
			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);
			//�����ı�
			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);
			//����ͼƬ
			virtual void LoadImage(ASNET::Graph::Word filename,
				ASNET::Graph::Image* &image);

			//��������
			virtual void LoadFont(ASNET::Graph::Font* &font,
				ASNET::Graph::Word fontname, float fontsize);

			virtual auto Interface()->ASNET::Graph::Interface;

		};
	

		typedef std::function<void(void*, ASNET::Graph::Graph*)> EventGraphDrawHandler;
		

	}
}


#include"ASNET.Graph.Direct3D.h"
#include"ASNET.Graph.Animation.h"
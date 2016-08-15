#include"Window.Graph.h"

#include<wincodec.h>
#include<dxgi.h>




namespace ASNET {
	namespace Graph {

		template<typename T>
		void release(T Interface) {
			if (Interface)
				Interface->Release();
			Interface = NULL;
		}

		ASNET::Graph::Font::Font(){
			textformat = NULL;
		}

		ASNET::Graph::Font::~Font(){
			if (textformat)
				textformat->Release();
			textformat = NULL;
		}

		auto ASNET::Graph::Font::FontSize() -> float{
			return textformat->GetFontSize();
		}





		ASNET::Graph::Image::Image(){
			bitmap = NULL;
		}

		ASNET::Graph::Image::~Image(){
			if (bitmap)
				bitmap->Release();
			bitmap = NULL;
		}

		auto ASNET::Graph::Image::GetWidth() -> float{
			return bitmap->GetSize().width;
		}

		auto ASNET::Graph::Image::GetHieght() -> float{
			return	bitmap->GetSize().height;
		}




	

		ASNET::Graph::Graph::Graph(HWND hwnd, bool IsWindowed){
			CoInitialize(NULL);
			CoCreateInstance(
				CLSID_WICImagingFactory,
				nullptr,
				CLSCTX_INPROC,
				IID_IWICImagingFactory,
				(void **)(&g_imagefactory));

			D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, (ID2D1Factory**)&g_factory);

			D3D_FEATURE_LEVEL Features[3] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0 };
			D3D_FEATURE_LEVEL MyFeature;
			D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_BGRA_SUPPORT, Features, 3,
				D3D11_SDK_VERSION, &g_device3d, &MyFeature, &g_devicecontext3d);

			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(IDWriteFactory),
				(IUnknown**)(&g_writefactory)
			);

			

			RECT rc;
			GetClientRect(hwnd, &rc);
			UINT width = rc.right - rc.left;
			UINT height = rc.bottom - rc.top;

			UINT MSAA4xQuality(0);
			g_device3d->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAA4xQuality);
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Width = width;
			sd.BufferDesc.Height = height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = hwnd;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;
			IDXGIDevice *DXGIDevice(NULL);
			g_device3d->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGIDevice));
			IDXGIAdapter *DXGIAdapter(NULL);
			DXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DXGIAdapter));
			IDXGIFactory *DXGIFactory(NULL);
			DXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&DXGIFactory));
			DXGIFactory->CreateSwapChain(g_device3d, &sd, &g_swapchain);

			DXGIFactory->Release();
			DXGIAdapter->Release();

			ID3D11Texture2D *BackBuffer(NULL);
			g_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
			g_device3d->CreateRenderTargetView(BackBuffer, NULL, &g_rendertargetview);

			BackBuffer->Release();


			D3D11_TEXTURE2D_DESC descDepth;
			ZeroMemory(&descDepth, sizeof(descDepth));
			descDepth.Width = width;
			descDepth.Height = height;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.SampleDesc.Count = 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			ID3D11Texture2D *DepthStencilBuffer(NULL);


			g_device3d->CreateTexture2D(&descDepth, NULL, &DepthStencilBuffer);
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = descDepth.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;

			g_device3d->CreateDepthStencilView(DepthStencilBuffer, &descDSV, &g_depthstencilview);
			g_devicecontext3d->OMSetRenderTargets(1, &g_rendertargetview, g_depthstencilview);

			DepthStencilBuffer->Release();

			D3D11_VIEWPORT ViewPort = { 0 };
			ViewPort.Width = (FLOAT)(width);
			ViewPort.Height = (FLOAT)(height);
			ViewPort.MinDepth = 0.f;
			ViewPort.MaxDepth = 1.f;
			ViewPort.TopLeftX = 0.f;
			ViewPort.TopLeftY = 0.f;
			g_devicecontext3d->RSSetViewports(1, &ViewPort);



			IDXGISurface* Surface;
			g_swapchain->GetBuffer(0, IID_PPV_ARGS(&Surface));

			FLOAT dpiX;
			FLOAT dpiY;
			g_factory->GetDesktopDpi(&dpiX, &dpiY);

			g_factory->CreateDevice(DXGIDevice, &g_device2d);

			g_device2d->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &g_devicecontext2d);

			D2D1_BITMAP_PROPERTIES1 bitmapProperties =
				D2D1::BitmapProperties1(
					D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
					D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
					dpiX,
					dpiY
				);

			ID2D1Bitmap1* TargetBitmap;


			g_devicecontext2d->CreateBitmapFromDxgiSurface(Surface,
				&bitmapProperties, &TargetBitmap);

			g_devicecontext2d->SetTarget(TargetBitmap);

			DXGIDevice->Release();

			
		}

		Graph::~Graph()
		{
			release(g_factory);
			release(g_imagefactory);
			release(g_writefactory);
			release(g_device2d);
			release(g_device3d);
			release(g_devicecontext2d);
			release(g_devicecontext3d);
			release(g_rendertargetview);
			release(g_depthstencilview);
			release(g_swapchain);
		}

		void ASNET::Graph::Graph::Clear(ASNET::Graph::Color color){
			float rgba[4];
			rgba[0] = color.r;
			rgba[1] = color.g;
			rgba[2] = color.b;
			rgba[3] = color.a;
			g_devicecontext3d->ClearRenderTargetView(g_rendertargetview, rgba);
			g_devicecontext3d->ClearDepthStencilView(g_depthstencilview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
			g_devicecontext2d->BeginDraw();
		}

		void ASNET::Graph::Graph::Present() {
			g_devicecontext2d->EndDraw();
			g_swapchain->Present(0, 0);
		}

		void ASNET::Graph::Graph::DrawLine(ASNET::Graph::Point P1, 
			ASNET::Graph::Point P2, ASNET::Graph::Color color, float width){
			ID2D1SolidColorBrush* Brush;
			g_devicecontext2d->CreateSolidColorBrush(color, &Brush);
			g_devicecontext2d->DrawLine(P1, P2, Brush, width);

			release(Brush);
		}

		void ASNET::Graph::Graph::DrawRectangle(ASNET::Graph::Rect rect,
			ASNET::Graph::Color color, float width,
			bool IsFill, ASNET::Graph::Color FillColor) {
			ID2D1SolidColorBrush* Brush;
			g_devicecontext2d->CreateSolidColorBrush(color, &Brush);
			g_devicecontext2d->DrawRectangle(rect, Brush, width);
			
			release(Brush);
			Brush = NULL;

			if (IsFill) {
				g_devicecontext2d->CreateSolidColorBrush(FillColor, &Brush);
				g_devicecontext2d->FillRectangle(rect, Brush);
				
				release(Brush);
			}
		}

		void ASNET::Graph::Graph::DrawImage(ASNET::Graph::Image * image,
			ASNET::Graph::Rect rect){
			g_devicecontext2d->DrawBitmap(image->bitmap, rect);
		}

		void ASNET::Graph::Graph::DrawWord(ASNET::Graph::Word word,
			ASNET::Graph::Rect rect,
			ASNET::Graph::Font * font, 
			ASNET::Graph::Color  color,
			ASNET::Graph::TextAlign horizontal, 
			ASNET::Graph::TextAlign vertical){
			switch (horizontal){
			case ASNET::Graph::TextAlign::Center: {
				font->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				break;
			}
			case ASNET::Graph::TextAlign::Left: {
				font->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				break;
			}
			case ASNET::Graph::TextAlign::Right: {
				font->textformat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				break;
			}
			default:
				break;
			}
			switch (vertical){
			case ASNET::Graph::TextAlign::Center: {
				font->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				break;
			}
			case ASNET::Graph::TextAlign::Top: {
				font->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				break;
			}
			case ASNET::Graph::TextAlign::Bottom: {
				font->textformat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				break;
			}
			default:
				break;
			}
			ID2D1SolidColorBrush* Brush;
			IDWriteTextLayout*    Layout;

			g_devicecontext2d->CreateSolidColorBrush(color, &Brush);

			g_writefactory->CreateTextLayout(word, (UINT32)wcslen(word), font->textformat, (FLOAT)(rect.right - rect.left),
				(FLOAT)(rect.bottom - rect.top), &Layout);



			g_devicecontext2d->DrawTextLayout(D2D1::Point2F(rect.left, rect.top), Layout, Brush);

			release(Brush);
			release(Layout);
			

		}

		void ASNET::Graph::Graph::LoadImage(ASNET::Graph::Word filename,
			ASNET::Graph::Image * image){
			IWICBitmapDecoder *pDecoder = NULL;
			IWICBitmapFrameDecode *pSource = NULL;
			IWICStream *pStream = NULL;
			IWICFormatConverter *pConverter = NULL;
			HRESULT hr = g_imagefactory->CreateDecoderFromFilename(
				filename,
				NULL,
				GENERIC_READ,
				WICDecodeMetadataCacheOnLoad,
				&pDecoder
			);
			if (SUCCEEDED(hr))
			{
				hr = pDecoder->GetFrame(0, &pSource);
			}
			else MessageBox(NULL, TEXT("Failed in frame"), TEXT("Error"), 0);
			if (SUCCEEDED(hr))
			{
				// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
				hr = g_imagefactory->CreateFormatConverter(&pConverter);
			}
			else MessageBox(NULL, TEXT("Failed in Converter"), TEXT("Error"), 0);
			if (SUCCEEDED(hr))
			{
				hr = pConverter->Initialize(
					pSource,
					GUID_WICPixelFormat32bppPBGRA,
					WICBitmapDitherTypeNone,
					NULL,
					0.f,
					WICBitmapPaletteTypeMedianCut
				);
			}
			else MessageBox(NULL, TEXT("Failed n Initialize"), TEXT("Error"), 0);
			if (SUCCEEDED(hr))
			{
				hr = g_devicecontext2d->CreateBitmapFromWicBitmap(
					pConverter,
					NULL,
					&image->bitmap
				);
			}
		}

		void Graph::LoadFont(ASNET::Graph::Font * font, 
			ASNET::Graph::Word fontname, float fontsize){
			release(font->textformat);
			g_writefactory->CreateTextFormat(fontname, NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				fontsize, L"zh-cn", &font->textformat);
		}

		



		





	}
}
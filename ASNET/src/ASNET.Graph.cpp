#include"ASNET.Graph.h"


#include<dxgi.h>


#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")

namespace ASNET {
	namespace Graph {

		template<typename T>
		void release(T &Interface) {
			if (Interface)
				Interface->Release();
			Interface = NULL;
		}

		ASNET::Graph::Font::Font(ASNET::Graph::Graph* Graph) {
			ParentGraph = Graph;
			textformat = NULL;
		}

		ASNET::Graph::Font::~Font() {
			if (textformat)
				textformat->Release();
			textformat = NULL;
		}

		auto ASNET::Graph::Font::FontSize() -> float {
			return textformat->GetFontSize();
		}

		void Font::reset(ASNET::Graph::Word fontname, float fontsize) {
			release(textformat);

			ParentGraph->g_writefactory->CreateTextFormat(&fontname[0], NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				fontsize, L"zh-cn", &textformat);
		}





		ASNET::Graph::Image::Image(ASNET::Graph::Graph* Graph) {
			ParentGraph = Graph;
			bitmap = NULL;
		}

		ASNET::Graph::Image::~Image() {
			if (bitmap)
				bitmap->Release();
			bitmap = NULL;
		}

		auto ASNET::Graph::Image::GetWidth() -> float {
			return bitmap->GetSize().width;
		}

		auto ASNET::Graph::Image::GetHieght() -> float {
			return	bitmap->GetSize().height;
		}

		void Image::reset(ASNET::Graph::Word filename) {
			release(bitmap);

			IWICBitmapDecoder *pDecoder = NULL;
			IWICBitmapFrameDecode *pSource = NULL;
			IWICStream *pStream = NULL;
			IWICFormatConverter *pConverter = NULL;
			HRESULT hr = ParentGraph->g_imagefactory->CreateDecoderFromFilename(
				&filename[0],
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
				hr = ParentGraph->g_imagefactory->CreateFormatConverter(&pConverter);
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
				hr = ParentGraph->g_devicecontext2d->CreateBitmapFromWicBitmap(
					pConverter,
					NULL,
					&bitmap
				);
			}
			release(pDecoder);
			release(pSource);
			release(pStream);
			release(pConverter);
		}






		void Graph::Initalize(HWND hwnd, bool IsWindowed) {
			HRESULT hr = CoInitialize(NULL);
			hr = CoCreateInstance(
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

			DXGI_SWAP_CHAIN_DESC Swap = { 0 };
			Swap.BufferDesc.Width = width;
			Swap.BufferDesc.Height = height;
			Swap.BufferDesc.RefreshRate.Denominator = 1;
			Swap.BufferDesc.RefreshRate.Numerator = 60;
			Swap.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			Swap.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			Swap.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			Swap.BufferCount = 1;
			Swap.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			Swap.Flags = 0;
			Swap.OutputWindow = hwnd;
			Swap.SampleDesc.Count = 4;
			Swap.SampleDesc.Quality = MSAA4xQuality - 1;
			Swap.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			Swap.Windowed = IsWindowed;

			IDXGIDevice *DXGIDevice(NULL);
			g_device3d->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DXGIDevice));
			IDXGIAdapter *DXGIAdapter(NULL);
			DXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DXGIAdapter));
			IDXGIFactory *DXGIFactory(NULL);
			DXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&DXGIFactory));
			DXGIFactory->CreateSwapChain(g_device3d, &Swap, &g_swapchain);

			DXGIFactory->Release();
			DXGIAdapter->Release();

			ID3D11Texture2D *BackBuffer(NULL);
			g_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
			g_device3d->CreateRenderTargetView(BackBuffer, NULL, &g_rendertargetview);



			D3D11_TEXTURE2D_DESC Desc = { 0 };
			Desc.Width = width;
			Desc.Height = height;
			Desc.MipLevels = 1;
			Desc.ArraySize = 1;
			Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			Desc.MiscFlags = 0;
			Desc.SampleDesc.Count = 4;
			Desc.SampleDesc.Quality = MSAA4xQuality - 1;
			Desc.Usage = D3D11_USAGE_DEFAULT;
			Desc.CPUAccessFlags = 0;
			ID3D11Texture2D *DepthStencilBuffer(NULL);


			g_device3d->CreateTexture2D(&Desc, NULL, &DepthStencilBuffer);


			g_device3d->CreateDepthStencilView(DepthStencilBuffer, NULL, &g_depthstencilview);
			g_devicecontext3d->OMSetRenderTargets(1, &g_rendertargetview, g_depthstencilview);


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

			g_factory->ReloadSystemMetrics();

			FLOAT dpiX;
			FLOAT dpiY;
			g_factory->GetDesktopDpi(&dpiX, &dpiY);

			g_dpix = dpiX;
			g_dpiy = dpiY;

			//d2d1
			g_factory->CreateDxgiSurfaceRenderTarget(Surface, D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE::D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
				dpiX,
				dpiY
			), &g_devicecontext2d);
			g_devicecontext2d->SetTextRenderingParams();
			g_devicecontext2d->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE::D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
			//d2d1_1
			/*g_factory->CreateDevice(DXGIDevice, &g_device2d);

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
			*/
			DXGIDevice->Release();
			BackBuffer->Release();

			DepthStencilBuffer->Release();
		}
		//do not use this
		Graph::Graph() {
		}

		ASNET::Graph::Graph::Graph(HWND hwnd, bool IsWindowed) {
			Initalize(hwnd, IsWindowed);
		}

		Graph::~Graph()
		{
			release(g_factory);
			release(g_imagefactory);
			release(g_writefactory);
			//d2d1_1
			//release(g_device2d);
			release(g_device3d);
			release(g_devicecontext2d);
			release(g_devicecontext3d);
			release(g_rendertargetview);
			release(g_depthstencilview);
			release(g_swapchain);
		}

		void ASNET::Graph::Graph::Clear(ASNET::Graph::Color color) {
			g_timer.Start();
			float rgba[4];
			rgba[0] = color.x;
			rgba[1] = color.y;
			rgba[2] = color.z;
			rgba[3] = color.w;
			g_devicecontext3d->ClearRenderTargetView(g_rendertargetview, rgba);
			g_devicecontext3d->ClearDepthStencilView(g_depthstencilview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
			g_devicecontext2d->BeginDraw();
		}

		void ASNET::Graph::Graph::Present() {
			g_devicecontext2d->EndDraw();
			g_swapchain->Present(0, 0);
			g_timer.End();
			g_render_time = g_timer.GetTime();
		}

		auto Graph::FPS() -> float {
			return 1.0f / g_render_time;
		}

		auto Graph::RenderTime() -> float {
			return g_render_time;
		}

		auto Graph::GetDpiX() -> float{
			return g_dpix;
		}

		auto Graph::GetDpiY()->float {
			return g_dpiy;
		}



		void ASNET::Graph::Graph::DrawLine(ASNET::Graph::Point P1,
			ASNET::Graph::Point P2, ASNET::Graph::Color color, float width) {
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
			ASNET::Graph::Rect rect) {
			g_devicecontext2d->DrawBitmap(image->bitmap, rect);
		}

		void Graph::DrawImageSurface(ASNET::Graph::ImageSurface * imagesurface,
			ASNET::Graph::Rect rect)
		{
			g_devicecontext2d->DrawBitmap(imagesurface->bitmap, rect);
		}

		void ASNET::Graph::Graph::DrawWord(ASNET::Graph::Word word,
			ASNET::Graph::Rect rect,
			ASNET::Graph::Font * font,
			ASNET::Graph::Color  color,
			ASNET::Graph::TextAlign horizontal,
			ASNET::Graph::TextAlign vertical) {
			switch (horizontal) {
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
			switch (vertical) {
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

			g_writefactory->CreateTextLayout(&word[0], word.length(), font->textformat, (FLOAT)(rect.right - rect.left),
				(FLOAT)(rect.bottom - rect.top), &Layout);


			if (Layout)
				g_devicecontext2d->DrawTextLayout(D2D1::Point2F(rect.left, rect.top), Layout, Brush);

			release(Brush);
			release(Layout);


		}

		void ASNET::Graph::Graph::LoadImage(ASNET::Graph::Word filename,
			ASNET::Graph::Image * &image) {
			if (image) return;
			image = new ASNET::Graph::Image(this);
			IWICBitmapDecoder *pDecoder = NULL;
			IWICBitmapFrameDecode *pSource = NULL;
			IWICStream *pStream = NULL;
			IWICFormatConverter *pConverter = NULL;
			HRESULT hr = g_imagefactory->CreateDecoderFromFilename(
				&filename[0],
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
			release(pDecoder);
			release(pSource);
			release(pStream);
			release(pConverter);
		}

		void Graph::LoadImageSurface(ASNET::Graph::Size size, 
			ASNET::Graph::ImageSurface *& imagesurface)
		{
			if (imagesurface) return;
			imagesurface = new ImageSurface(this);
			g_imagefactory->CreateBitmap(
				(UINT)(size.width), (UINT)(size.height),
				GUID_WICPixelFormat32bppPRGBA,
				WICBitmapCacheOnDemand,
				&imagesurface->wicbitmap
			);

			g_devicecontext2d->CreateBitmapFromWicBitmap(imagesurface->wicbitmap, &imagesurface->bitmap);

			imagesurface->Lock();
			

		}



		void Graph::LoadFont(ASNET::Graph::Font * &font,
			ASNET::Graph::Word fontname, float fontsize) {
			if (font) return;

			font = new ASNET::Graph::Font(this);
			g_writefactory->CreateTextFormat(&fontname[0], NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				fontsize, L"zh-cn", &font->textformat);
		}












		Color::Color()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 1;
		}

		Color::Color(float r, float g, float b, float a)
		{
			x = r;
			y = g;
			z = b;
			w = a;
		}

		Color::Color(Color color, float a)
		{
			x = color.x;
			y = color.y;
			z = color.z;
			w = a;
		}

		Color::Color(D2D1::ColorF::Enum color)
		{
			D2D1::ColorF colorf = color;
			x = colorf.r;
			y = colorf.g;
			z = colorf.b;
			w = colorf.a;
		}

		Color::Color(ASNET::Physics::Vector4 vector4)
		{
			x = vector4.x;
			y = vector4.y;
			z = vector4.z;
			w = vector4.w;
		}

		Color::operator D2D1::ColorF()
		{
			return D2D1::ColorF(x, y, z, w);
		}









		void ImageSurface::Lock()
		{
			WICRect rect = { 0,0,(int)GetWidth(),(int)GetHieght() };

			wicbitmap->Lock(&rect, WICBitmapLockWrite, &wicbitmaplock);

			wicbitmaplock->GetStride(&stride);
			wicbitmaplock->GetDataPointer(&buffsize, &pixel);
		}

		void ImageSurface::UnLock()
		{
			wicbitmaplock->Release();
			wicbitmaplock = nullptr;
		}

		ImageSurface::ImageSurface(ASNET::Graph::Graph * Graph)
		{
			ParentGraph = Graph;
			bitmap = nullptr;
			wicbitmap = nullptr;
			wicbitmaplock = nullptr;
		}

		void ImageSurface::SetPixel(int x, int y, ASNET::Graph::Color color, bool NeedFlush)
		{
			int start = (y - 1)*stride + (x - 1) * 4;
			pixel[start] = (UINT)color.x * 255;
			pixel[start + 1] = (UINT)color.y * 255;
			pixel[start + 2] = (UINT)color.z * 255;
			pixel[start + 3] = (UINT)color.w * 255;
			if (NeedFlush)
				Flush();
		}

		void ImageSurface::Flush()
		{
			UnLock();
			ParentGraph->g_devicecontext2d->CreateBitmapFromWicBitmap(wicbitmap, &bitmap);
			Lock();
		}

		void ImageSurface::reset(ASNET::Graph::Size size)
		{
			wicbitmap->Release();
			bitmap->Release();
			ParentGraph->g_imagefactory->CreateBitmap(
				(UINT)size.width, (UINT)size.height,
				GUID_WICPixelFormat32bppPRGBA,
				WICBitmapCacheOnDemand,
				&wicbitmap
			);
			ParentGraph->g_devicecontext2d->CreateBitmapFromWicBitmap(wicbitmap, &bitmap);

			Lock();


		}

	}
}
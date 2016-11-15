

#include"ASNET.Graph.Graphics.h"
#include"ASNET.Graph.h"

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

		void ASNET::Graph::Font::reset(ASNET::Graph::Word fontname, float fontsize) {
			release(textformat);

			ParentGraph->g_writefactory->CreateTextFormat(&fontname[0], NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				fontsize, L"zh-cn", &textformat);
		}

		Font::operator IDWriteTextFormat*()
		{
			return textformat;
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

		void ASNET::Graph::Image::reset(ASNET::Graph::Word filename) {
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
			else MessageBox(NULL, TEXT("Failed in Initialize"), TEXT("Error"), 0);
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











		Surface::Surface(ASNET::Graph::Graph * graph)
		{
			ParentGraph = graph;
			g_width = 0;
			g_height = 0;
			x = 0;
			y = 0;
		}

		void Surface::BeginDraw()
		{
			ParentGraph->g_devicecontext2d->PushAxisAlignedClip(
				D2D1::RectF(x, y, x + g_width, y + g_height),
				D2D1_ANTIALIAS_MODE::D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
			);
			ParentGraph->g_devicecontext2d->SetTransform(
				D2D1::Matrix3x2F::Translation(D2D1::SizeF(x, y)));
		}

		void Surface::DrawLine(ASNET::Graph::Point p1,
			ASNET::Graph::Point p2, ASNET::Graph::Color color, float width)
		{
			BeginDraw();
			ParentGraph->DrawLine(p1, p2, color, width);
			EndDraw();
		}

		void Surface::DrawRectangle(ASNET::Graph::Rect rect,
			ASNET::Graph::Color color, float width,
			bool IsFill, ASNET::Graph::Color FillColor)
		{
			BeginDraw();
			ParentGraph->DrawRectangle(rect, color, width, IsFill, FillColor);
			EndDraw();
		}

		void Surface::DrawImage(ASNET::Graph::Image * image,
			ASNET::Graph::Rect rect)
		{
			BeginDraw();
			ParentGraph->DrawImage(image, rect);
			EndDraw();
		}

		void Surface::DrawWord(ASNET::Graph::Word word, ASNET::Graph::Rect rect,
			ASNET::Graph::Font * font, ASNET::Graph::Color color,
			ASNET::Graph::TextAlign horizontal, ASNET::Graph::TextAlign vertical)
		{
			BeginDraw();
			ParentGraph->DrawWord(word, rect, font, color, horizontal, vertical);
			EndDraw();
		}

		void Surface::EndDraw()
		{
			ParentGraph->g_devicecontext2d->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
			ParentGraph->g_devicecontext2d->PopAxisAlignedClip();

		}





		auto Surface::Width() -> float
		{
			return g_width;
		}

		auto Surface::Height() -> float
		{
			return g_height;
		}

		auto Surface::PositionX() -> float
		{
			return x;
		}

		auto Surface::PositionY() -> float
		{
			return y;
		}

		void Surface::SetWidth(float width)
		{
			g_width = width;
		}

		void Surface::SetHeight(float height)
		{
			g_height = height;
		}

		void Surface::SetPositionX(float posx)
		{
			x = posx;
		}

		void Surface::SetPositionY(float posy)
		{
			y = posy;
		}

	}
}
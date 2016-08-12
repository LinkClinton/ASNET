#include"Window.Graph.h"

namespace ASNET {
	namespace Graph {

		ASNET::Graph::Font::Font(){
			textformat = NULL;
		}

		ASNET::Graph::Font::~Font(){
			if (textformat)
				textformat->Release();
			textformat = NULL;
		}

		auto ASNET::Graph::Font::FontSize() -> int{
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






		ASNET::Graph::Graph::Graph(HWND hwnd, int width, int height, bool IsWindowed){

		}

	}
}
#pragma once
#include"ASNET.Control.h"

namespace ASNET {
	namespace Control {

		class TextBox :public ASNET::Control::Control {
		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
			void OnStoping()override;
		public:
			TextBox(ASNET::Graph::Graph* graph,
				float left, float right, float top, float bottom,
				wchar_t* name, ASNET::Graph::Font* font);

			

			wchar_t* Name;
			wchar_t* Text;

			ASNET::Graph::Color TextColor;
			ASNET::Graph::Font* TextFont;
		};


	}
}
#pragma once
#include"ASNET.Control.h"

#include"ASNET.Control.Text.h"

namespace ASNET {
	namespace Control {


		class TextBox :public ASNET::Control::Control {
		private:
			ASNET::Control::Text* g_text;
		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
			void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e)override;
			//void OnStoping()override;
		public:
			TextBox(ASNET::Graph::Graph* graph,
				float left, float right, float top,
				float bottom, wchar_t* name,ASNET::Graph::Font* fontface);


			wchar_t* Name;


		};


	}
}
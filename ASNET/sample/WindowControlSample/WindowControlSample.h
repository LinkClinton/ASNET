#pragma once
#include<ASNET.h>

namespace ASNET {
	namespace Sample {

		class ControlWindow :public ASNET::Window {
		private:
		protected:
		public:
			ControlWindow();
			~ControlWindow();
		};

		class ControlStartPage:public ASNET::Page::Page {
		private:
			const int Note1Size = 70;
		private:
			//Resource
			ASNET::Graph::Font* Consolas20;
		private:
			ASNET::Control::Label* Note1;
			ASNET::Control::Button* Button1;
		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
			void OnLoading(void* sender, void* any)override;
		public:
			ControlStartPage();
			~ControlStartPage();
		};


	}
}
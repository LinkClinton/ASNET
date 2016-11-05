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
			ASNET::Graph::ImageSurface* Surface;
			ASNET::Graph::Font* Consolas20;
		private:
			ASNET::Control::Label* Note1;
			ASNET::Control::Button* Button1;
		private:
			//event
			static void OnButton1_MouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
			void OnInitalize(void* sender)override;
			void OnLoading(void* sender, void* any)override;
			void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e)override;
		public:
			ControlStartPage();
			~ControlStartPage();
		};

		class ControlSecondPage :public ASNET::Page::Page {
		private:
			const int Button1Size = 70;
			//Resource
			ASNET::Graph::Font* Consolas40;
		private:
			//Control
			ASNET::Control::Button* Button1;
		private:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
			void OnInitalize(void* sender);
			void OnLoading(void* sender, void* any)override;
			
		private:
			static void OnButton1_MouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		public:
			ControlSecondPage();
			~ControlSecondPage();
		};

	}
}
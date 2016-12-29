#pragma once
#include<ASNET.h>
#include<ASNET.Control.Button.h>
#include<ASNET.Control.TextBox.h>
namespace ASNET {
	namespace Sample {

		class ControlWindow :public ASNET::Window {
		private:
		public:
			void OnKeyDown(void*sender, ASNET::Event::EventBoardClick* e)override;
			ASNET::Graph::Graph* MyGraph;
		public:
			ControlWindow();
			~ControlWindow();
		};

		class ControlStartPage:public ASNET::Page::Page {
		private:
			const int Note1Size = 70;
		private:
			//Resource
			ASNET::Graph::Surface* surface;
			ASNET::Graph::Font* Consolas20;
			ASNET::Graph::Font* Consolas12;
		private:
			ASNET::Control::TextBox* TextBox1;
			ASNET::Control::Button*  Button1;
		private:
			//event
			static void OnButton1_MouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			static void OnButton1_KeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			static auto Get(float _float)->ASNET::Graph::Word;
		protected:
			void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
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
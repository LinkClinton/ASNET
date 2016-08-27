#pragma once

#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"

namespace ASNET {
	namespace Page {
		class Page;
	}
	namespace Control {

		class Color {
		public:
			float r, g, b, a;
			Color();
			Color(ASNET::Graph::Color color);
			Color(ASNET::Graph::Color::Enum color);
			Color(float _r, float _g, float _b, float _a);

			operator ASNET::Graph::Color();
		};

		//所有的事件，只有在控件范围内才会被使用
		class Control {
		private:
			friend class ASNET::Page::Page;
		protected:
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		public:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
		public:
			bool  IsActive;
			bool  IsFocus;
			bool  IsShow;

			float Left;
			float Right;
			float Top;
			float Bottom;

			ASNET::Graph::Graph*     ParentGraph;
		public:
			Control();

			operator ASNET::Graph::Rect();

			void Show();

			void Hide();
			
			void GetFocus();

			void LostFocus();

			void Active();

			void UnActive();

		};


	}
}
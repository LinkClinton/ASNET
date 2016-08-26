#pragma once

#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"

namespace ASNET {
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


		class Control {
		protected:
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		protected:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
		public:
			Control() {};
		};


	}
}
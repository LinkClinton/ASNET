#pragma once
#include"Window.Event.h"
#include"Window.Graph.h"
namespace ASNET {
	namespace Page {
		class Page {
		private:
		protected:
			ASNET::Graph::Graph*       graph;
		protected:
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
			virtual void OnDraw(void* sender, void* render); //How to draw the page
			virtual void OnInitalize(void* sender,void* render); //On Load the Page
		protected:
			ASNET::Event::EventMouseMoveHander		MouseMoveHander;
			ASNET::Event::EventMouseClickHander		MouseButtonUpHander;
			ASNET::Event::EventMouseClickHander		MouseButtonDownHander;
			ASNET::Event::EventBoardClickHander		BoardUpHander;
			ASNET::Event::EventBoardClickHander		BoardDownHander;
			ASNET::Event::EventSizeChangeHander		SizeChangeHander;
		public:
		};
	}
}
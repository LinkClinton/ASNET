#pragma once
#include"Window.Event.h"
#include"Window.Graph.h"
#include"Window.EventHander.h"

#include<vector>

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
			virtual void OnDraw(void* sender, ASNET::Graph::Graph* render); 
			virtual void OnInitalize(void* sender, void* any);
		protected:
			ASNET::Event::EventMouseMoveHanders			MouseMoveHander;
			ASNET::Event::EventMouseClickHanders		MouseButtonUpHander;
			ASNET::Event::EventMouseClickHanders		MouseButtonDownHander;
			ASNET::Event::EventBoardClickHanders		BoardUpHander;
			ASNET::Event::EventBoardClickHanders		BoardDownHander;
			ASNET::Event::EventSizeChangeHanders		SizeChangeHander;
			ASNET::Event::EventGraphDrawHanders			GraphDrawHander;
			
		public:
		};
	}
}
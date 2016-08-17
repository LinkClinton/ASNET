#pragma once
#include"Window.Event.h"
#include"Window.Graph.h"

#include<vector>

namespace ASNET {

	namespace Event {

	


		typedef std::vector<ASNET::Event::EventBaseHandler>				EventBaseHandlers;
		typedef std::vector<ASNET::Graph::EventGraphDrawHandler>		EventGraphDrawHandlers;
		typedef std::vector<ASNET::Event::EventMouseMoveHandler>		EventMouseMoveHandlers;
		typedef std::vector<ASNET::Event::EventMouseWheelHandler>		EventMouseWheelHandlers;
		typedef std::vector<ASNET::Event::EventMouseClickHandler>		EventMouseClickHandlers;
		typedef std::vector<ASNET::Event::EventBoardClickHandler>		EventBoardClickHandlers;
		typedef std::vector < ASNET::Event::EventSizeChangeHandler>		EventSizeChangeHandlers;
		
		class EventHandler {
		public:
			friend ASNET::Event::EventBaseHandlers operator +=(
				ASNET::Event::EventBaseHandlers &handlers,
				ASNET::Event::EventBaseHandler handler
				);
		
			friend ASNET::Event::EventGraphDrawHandlers operator +=(
				ASNET::Event::EventGraphDrawHandlers &handlers,
				ASNET::Graph::EventGraphDrawHandler handler
				);

			friend ASNET::Event::EventMouseMoveHandlers operator +=(
				ASNET::Event::EventMouseMoveHandlers &handlers,
				ASNET::Event::EventMouseMoveHandler handler
				);

			friend ASNET::Event::EventMouseWheelHandlers operator +=(
				ASNET::Event::EventMouseWheelHandlers &handlers,
				ASNET::Event::EventMouseWheelHandler handler
				);

			friend ASNET::Event::EventMouseClickHandlers operator +=(
				ASNET::Event::EventMouseClickHandlers &handlers,
				ASNET::Event::EventMouseClickHandler handler
				);

			friend ASNET::Event::EventBoardClickHandlers operator +=(
				ASNET::Event::EventBoardClickHandlers &handlers,
				ASNET::Event::EventBoardClickHandler handler
				);

			friend ASNET::Event::EventSizeChangeHandlers operator +=(
				ASNET::Event::EventSizeChangeHandlers &handlers,
				ASNET::Event::EventSizeChangeHandler handler
				);
		
			static auto GetSenderMessage(void* sender)->ASNET::Window*;

			
		};
		
		template<typename Handlers, typename EventArg>
		static void DoEventHandlers(Handlers handlers, void * sender, EventArg eventarg) {
			int size = handlers.size();
			for (int i = 0; i < size; i++)
				handlers[i](sender, eventarg);
		}

	}

}
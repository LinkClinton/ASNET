#include"ASNET.Window.Event.h"

#include<Windows.h>

namespace ASNET {
	namespace Event {


		//need finish
		

		ASNET::Event::EventBaseHandlers operator+=(
			ASNET::Event::EventBaseHandlers &handlers, 
			ASNET::Event::EventBaseHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventGraphDrawHandlers operator+=(
			ASNET::Event::EventGraphDrawHandlers &handlers,
			ASNET::Graph::EventGraphDrawHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventMouseMoveHandlers operator+=(
			ASNET::Event::EventMouseMoveHandlers &handlers,
			ASNET::Event::EventMouseMoveHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventMouseWheelHandlers operator +=(
			ASNET::Event::EventMouseWheelHandlers &handlers,
			ASNET::Event::EventMouseWheelHandler handler
			) {
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventMouseClickHandlers operator+=(
			ASNET::Event::EventMouseClickHandlers &handlers,
			ASNET::Event::EventMouseClickHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventBoardClickHandlers operator+=(
			ASNET::Event::EventBoardClickHandlers &handlers, 
			ASNET::Event::EventBoardClickHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventSizeChangeHandlers operator+=(
			ASNET::Event::EventSizeChangeHandlers &handlers, 
			ASNET::Event::EventSizeChangeHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

		ASNET::Event::EventGetFocusHandlers operator+=(
			ASNET::Event::EventGetFocusHandlers & handlers,
			ASNET::Event::EventGetFocusHandler handler){
			handlers.push_back(handler);
			return handlers;
		}

	



		


		auto EventHandler::GetSenderMessage(void * sender) -> ASNET::Window *
		{
			return (ASNET::Window*)sender;
		}

	}
}
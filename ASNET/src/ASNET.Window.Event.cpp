#include"ASNET.Window.Event.h"

#include<Windows.h>

namespace ASNET {
	namespace Event {


		//need finish
		

		ASNET::Event::EventBaseHandlers operator+=(
			ASNET::Event::EventBaseHandlers &handers, 
			ASNET::Event::EventBaseHandler hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventGraphDrawHandlers operator+=(
			ASNET::Event::EventGraphDrawHandlers &handers,
			ASNET::Graph::EventGraphDrawHandler hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventMouseMoveHandlers operator+=(
			ASNET::Event::EventMouseMoveHandlers &handers,
			ASNET::Event::EventMouseMoveHandler hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventMouseWheelHandlers operator +=(
			ASNET::Event::EventMouseWheelHandlers &handers,
			ASNET::Event::EventMouseWheelHandler hander
			) {
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventMouseClickHandlers operator+=(
			ASNET::Event::EventMouseClickHandlers &handers,
			ASNET::Event::EventMouseClickHandler hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventBoardClickHandlers operator+=(
			ASNET::Event::EventBoardClickHandlers &handers, 
			ASNET::Event::EventBoardClickHandler hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventSizeChangeHandlers operator+=(
			ASNET::Event::EventSizeChangeHandlers &handers, 
			ASNET::Event::EventSizeChangeHandler hander){
			handers.push_back(hander);
			return handers;
		}

		


		auto EventHandler::GetSenderMessage(void * sender) -> ASNET::Window *
		{
			return (ASNET::Window*)sender;
		}

	}
}
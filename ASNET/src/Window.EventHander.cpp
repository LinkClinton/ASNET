#include"Window.EventHander.h"

#include<Windows.h>

namespace ASNET {
	namespace Event {


		//need finish
		

		ASNET::Event::EventBaseHanders operator+=(
			ASNET::Event::EventBaseHanders &handers, 
			ASNET::Event::EventBaseHander hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventGraphDrawHanders operator+=(
			ASNET::Event::EventGraphDrawHanders &handers,
			ASNET::Graph::EventGraphDrawHander hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventMouseMoveHanders operator+=(
			ASNET::Event::EventMouseMoveHanders &handers,
			ASNET::Event::EventMouseMoveHander hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventMouseWheelHanders operator +=(
			ASNET::Event::EventMouseWheelHanders &handers,
			ASNET::Event::EventMouseWheelHander hander
			) {
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventMouseClickHanders operator+=(
			ASNET::Event::EventMouseClickHanders &handers,
			ASNET::Event::EventMouseClickHander hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventBoardClickHanders operator+=(
			ASNET::Event::EventBoardClickHanders &handers, 
			ASNET::Event::EventBoardClickHander hander){
			handers.push_back(hander);
			return handers;
		}

		ASNET::Event::EventSizeChangeHanders operator+=(
			ASNET::Event::EventSizeChangeHanders &handers, 
			ASNET::Event::EventSizeChangeHander hander){
			handers.push_back(hander);
			return handers;
		}

		


		auto EventHander::GetSenderMessage(void * sender) -> ASNET::Window *
		{
			return (ASNET::Window*)sender;
		}

	}
}
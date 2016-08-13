#include"Window.EventHander.h"

namespace ASNET {
	namespace Event {



		ASNET::Event::EventBaseHanders operator+=(
			ASNET::Event::EventBaseHanders handers, 
			ASNET::Event::EventBaseHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventBaseHanders(handers);
		}

		ASNET::Event::EventMouseHanders operator+=(
			ASNET::Event::EventMouseHanders handers, 
			ASNET::Event::EventMouseHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventMouseHanders(handers);
		}

		ASNET::Event::EventBoardHanders operator+=(
			ASNET::Event::EventBoardHanders handers,
			ASNET::Event::EventBoardHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventBoardHanders(handers);
		}

		ASNET::Event::EventGraphDrawHanders operator+=(
			ASNET::Event::EventGraphDrawHanders handers,
			ASNET::Graph::EventGraphDrawHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventGraphDrawHanders(handers);
		}

		ASNET::Event::EventMouseMoveHanders operator+=(
			ASNET::Event::EventMouseMoveHanders handers,
			ASNET::Event::EventMouseMoveHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventMouseMoveHanders(handers);
		}

		ASNET::Event::EventMouseClickHanders operator+=(
			ASNET::Event::EventMouseClickHanders handers,
			ASNET::Event::EventMouseClickHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventMouseClickHanders(handers);
		}

		ASNET::Event::EventBoardClickHanders operator+=(
			ASNET::Event::EventBoardClickHanders handers, 
			ASNET::Event::EventBoardClickHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventBoardClickHanders(handers);
		}

		ASNET::Event::EventSizeChangeHanders operator+=(
			ASNET::Event::EventSizeChangeHanders handers, 
			ASNET::Event::EventSizeChangeHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventSizeChangeHanders(handers);
		}


	}
}
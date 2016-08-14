#include"Window.EventHander.h"

namespace ASNET {
	namespace Event {


		//need finish
		ASNET::Event::EventType ToEventType(int message){
			switch (message)
			{
				//put your code
			default:
				break;
			}
			return ASNET::Event::EventType(1);
		}

		ASNET::Event::EventBaseHanders operator+=(
			ASNET::Event::EventBaseHanders handers, 
			ASNET::Event::EventBaseHander hander){
			handers.push_back(hander);
			return ASNET::Event::EventBaseHanders(handers);
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

		ASNET::Event::EventMouseWheelHanders operator +=(
			ASNET::Event::EventMouseWheelHanders handers,
			ASNET::Event::EventMouseWheelHander hander
			) {
			handers.push_back(hander);
			return ASNET::Event::EventMouseWheelHanders(handers);
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

		template<typename Handers, typename EventArg>
		inline void ASNET::Event::EventHander::DoEventHanders(Handers handers, void * sender, EventArg eventarg) {
			int size = handers.size();
			for (int i = 0; i < size; i++)
				handers[i](sender, eventarg);
		}


	}
}
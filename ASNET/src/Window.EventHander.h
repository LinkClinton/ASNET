#pragma once
#include"Window.Event.h"
#include"Window.Graph.h"

#include<vector>

namespace ASNET {

	namespace Event {

	


		typedef std::vector<ASNET::Event::EventBaseHander>			EventBaseHanders;
		typedef std::vector<ASNET::Graph::EventGraphDrawHander>		EventGraphDrawHanders;
		typedef std::vector<ASNET::Event::EventMouseMoveHander>		EventMouseMoveHanders;
		typedef std::vector<ASNET::Event::EventMouseWheelHander>    EventMouseWheelHanders;
		typedef std::vector<ASNET::Event::EventMouseClickHander>	EventMouseClickHanders;
		typedef std::vector<ASNET::Event::EventBoardClickHander>	EventBoardClickHanders;
		typedef std::vector<ASNET::Event::EventSizeChangeHander>	EventSizeChangeHanders;
		
		class EventHander {
		public:
			friend ASNET::Event::EventBaseHanders operator +=(
				ASNET::Event::EventBaseHanders handers,
				ASNET::Event::EventBaseHander hander
				);
		
			friend ASNET::Event::EventGraphDrawHanders operator +=(
				ASNET::Event::EventGraphDrawHanders handers,
				ASNET::Graph::EventGraphDrawHander hander
				);

			friend ASNET::Event::EventMouseMoveHanders operator +=(
				ASNET::Event::EventMouseMoveHanders handers,
				ASNET::Event::EventMouseMoveHander hander
				);

			friend ASNET::Event::EventMouseWheelHanders operator +=(
				ASNET::Event::EventMouseWheelHanders handers,
				ASNET::Event::EventMouseWheelHander hander
				);

			friend ASNET::Event::EventMouseClickHanders operator +=(
				ASNET::Event::EventMouseClickHanders handers,
				ASNET::Event::EventMouseClickHander hander
				);

			friend ASNET::Event::EventBoardClickHanders operator +=(
				ASNET::Event::EventBoardClickHanders handers,
				ASNET::Event::EventBoardClickHander hander
				);

			friend ASNET::Event::EventSizeChangeHanders operator +=(
				ASNET::Event::EventSizeChangeHanders handers,
				ASNET::Event::EventSizeChangeHander hander
				);
		
			

			
		};
		
		template<typename Handers, typename EventArg>
		static void DoEventHanders(Handers handers, void * sender, EventArg eventarg) {
			int size = handers.size();
			for (int i = 0; i < size; i++)
				handers[i](sender, eventarg);
		}

	}

}
#pragma once
#include"Window.Event.h"
#include"Window.Graph.h"

#include<vector>

namespace ASNET {

	namespace Event {

		typedef std::vector<ASNET::Event::EventBaseHander>			EventBaseHanders;
		typedef std::vector<ASNET::Event::EventMouseHander>			EventMouseHanders;
		typedef std::vector<ASNET::Event::EventBoardHander>			EventBoardHanders;
		typedef std::vector<ASNET::Graph::EventGraphDrawHander>		EventGraphDrawHanders;
		typedef std::vector<ASNET::Event::EventMouseMoveHander>		EventMouseMoveHanders;
		typedef std::vector<ASNET::Event::EventMouseClickHander>	EventMouseClickHanders;
		typedef std::vector<ASNET::Event::EventBoardClickHander>	EventBoardClickHanders;
		typedef std::vector<ASNET::Event::EventSizeChangeHander>	EventSizeChangeHanders;
		
		class EventHander {
		public:
			friend ASNET::Event::EventBaseHanders operator +=(
				ASNET::Event::EventBaseHanders handers,
				ASNET::Event::EventBaseHander hander
				);
			
			friend ASNET::Event::EventMouseHanders operator +=(
				ASNET::Event::EventMouseHanders handers,
				ASNET::Event::EventMouseHander hander
				);

			friend ASNET::Event::EventBoardHanders operator +=(
				ASNET::Event::EventBoardHanders handers,
				ASNET::Event::EventBoardHander hander
				);

			friend ASNET::Event::EventGraphDrawHanders operator +=(
				ASNET::Event::EventGraphDrawHanders handers,
				ASNET::Graph::EventGraphDrawHander hander
				);

			friend ASNET::Event::EventMouseMoveHanders operator +=(
				ASNET::Event::EventMouseMoveHanders handers,
				ASNET::Event::EventMouseMoveHander hander
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
		
	}

}
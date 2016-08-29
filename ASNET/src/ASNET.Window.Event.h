#pragma once
#include<vector>
#include<functional>


#include"ASNET.Window.Keycode.h"
#include"ASNET.Graph.h"

//简单的事件类
//在所有的虚函数中其sender参数传递的是窗口的指针
//在所有的被加载的函数里，就是通过handler加入的函数中其sender的参数是其自己的指针
//因为所有被加载进去的函数要求是静态的，因此其sender参数的指针就是其自己

namespace ASNET {
	class Window;
	namespace Event {

		enum class EventType :int {
			EventOther,
			EventMouseMove,
			EventMouseClick,
			EventMouseWheel,
			EventBoardClick
		};


		//Base Event
		struct EventBase {

		};


		//MouseMove Event
		struct EventMouseMove :EventBase {
			int x, y;
		};

		//enum of mouse button
		enum MouseButton {
			Left, Middle, Right
		};

		//MouseClick Event
		struct EventMouseClick :EventBase {
			int x, y;
			bool IsDown;
			MouseButton button;
		};

		//MouseWheel Event
		struct EventMouseWheel :EventBase {
			int x, y;
			int offest; //the mouse wheel move + is up,- is down
		};




		//BoardClick Event
		struct EventBoardClick :EventBase {
			Keycode keycode;
			bool IsDown;
		};

		//SizeChange Event
		struct EventSizeChange :EventBase {
			int last_width, last_height;
			int now_width, now_height;
		};



		typedef std::function<void(void*, EventBase*)>			EventBaseHandler;
		typedef std::function<void(void*, EventMouseMove*)>		EventMouseMoveHandler;
		typedef std::function<void(void*, EventMouseWheel*)>	EventMouseWheelHandler;
		typedef std::function<void(void*, EventMouseClick*)>	EventMouseClickHandler;
		typedef	std::function<void(void*, EventBoardClick*)>	EventBoardClickHandler;
		typedef std::function<void(void*, EventSizeChange*)>	EventSizeChangeHandler;


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
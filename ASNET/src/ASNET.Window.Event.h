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

		//事件类型
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


		
		typedef std::function<void(void*, EventBase*)>			EventBaseHandler; //基础事件
		typedef std::function<void(void*, EventMouseMove*)>		EventMouseMoveHandler; //鼠标移动事件
		typedef std::function<void(void*, EventMouseWheel*)>	EventMouseWheelHandler; //鼠标滑轮滚动事件
		typedef std::function<void(void*, EventMouseClick*)>	EventMouseClickHandler; //鼠标点击事件
		typedef	std::function<void(void*, EventBoardClick*)>	EventBoardClickHandler; //键盘按键事件
		typedef std::function<void(void*, EventSizeChange*)>	EventSizeChangeHandler; //窗口大小事件

		typedef std::function<void(void*)>				        EventGetFocusHandler; //得到焦点事件
		typedef std::function<void(void*)>                      EventLostFocusHandler; //失去焦点事件



		typedef std::vector<ASNET::Event::EventBaseHandler>				EventBaseHandlers; //基础事件集合
		typedef std::vector<ASNET::Graph::EventGraphDrawHandler>		EventGraphDrawHandlers; //绘制事件集合
		typedef std::vector<ASNET::Event::EventMouseMoveHandler>		EventMouseMoveHandlers; //鼠标移动事件集合
		typedef std::vector<ASNET::Event::EventMouseWheelHandler>		EventMouseWheelHandlers; //鼠标滑轮滚动事件集合 
		typedef std::vector<ASNET::Event::EventMouseClickHandler>		EventMouseClickHandlers; //鼠标点击事件集合 
		typedef std::vector<ASNET::Event::EventBoardClickHandler>		EventBoardClickHandlers; //键盘按键事件集合
		typedef std::vector<ASNET::Event::EventSizeChangeHandler>		EventSizeChangeHandlers; //窗口大小事件集合

		typedef std::vector<ASNET::Event::EventGetFocusHandler>	        EventGetFocusHandlers; //获取焦点事件集合
		typedef std::vector<ASNET::Event::EventLostFocusHandler>	    EventLostFocusHandlers; //失去焦点事件集合


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

			friend ASNET::Event::EventGetFocusHandlers operator+=(
				ASNET::Event::EventGetFocusHandlers &handlers,
				ASNET::Event::EventGetFocusHandler handler
				);

		


			static auto GetSenderMessage(void* sender)->ASNET::Window*;

		};

		//将一个事件集合里面的事件处理
		template<typename Handlers, typename EventArg>
		static void DoEventHandlers(Handlers handlers, void * sender, EventArg eventarg) {
			for (size_t i = 0; i < handlers.size(); i++)
				handlers[i](sender, eventarg);
		}

		template<typename Handlers>
		static void DoEventHandlers(Handlers handlers, void* sender) {
			for (size_t i = 0; i < handlers.size(); i++)
				handlers[i](sender);
		}

	}

}
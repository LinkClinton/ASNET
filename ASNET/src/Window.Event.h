#pragma once
#include<vector>
#include<functional>


#include"Window.Keycode.h"



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
		enum MouseButton{
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

		

		typedef std::function<void(void*, EventBase*)>			EventBaseHander;
		typedef std::function<void(void*, EventMouseMove*)>		EventMouseMoveHander;
		typedef std::function<void(void*, EventMouseWheel*)>	EventMouseWheelHander;
		typedef std::function<void(void*, EventMouseClick*)>	EventMouseClickHander;
		typedef	std::function<void(void*, EventBoardClick*)>	EventBoardClickHander;
		typedef std::function<void(void*, EventSizeChange*)>	EventSizeChangeHander;

		
	}
}
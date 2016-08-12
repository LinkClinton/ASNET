#pragma once
#include<functional>

#include"Window.Keycode.h"

namespace ASNET {
	namespace Event {
		//Base Event
		struct EventBase {

		};

		//Base Mouse Event
		struct EventMouse :EventBase {
			int x, y;
		};

		//MouseMove Event
		struct EventMouseMove :EventMouse {

		};

		//enum of mouse button
		enum MouseButton{
			Left, Middle, Right
		};

		//MouseClick Event
		struct EventMouseClick :EventMouse {
			MouseButton button;
		};

		//MouseWheel Event
		struct EventMouseWheel :EventMouse {
			int offest; //the mouse wheel move + is up,- is down
		};

		

		//BoardEvent
		struct EventBoard :EventBase {
			Keycode keycode;
		};

		//BoardClick Event
		struct EventBoardClick :EventBoard {
			bool IsDown;
		};

		//SizeChange Event
		struct EventSizeChange :EventBase {
			int last_width, last_height;
			int now_width, now_height;
		};

		typedef std::function<void(void*, EventBase*)> EventBaseHander;
		typedef std::function<void(void*, EventMouse*)> EventMouseHander;
		typedef std::function<void(void*, EventMouseMove)> EventMouseMoveHander;
		typedef std::function<void(void*, EventMouseClick*)> EventMouseClickHander;
		typedef std::function<void(void*, EventBoard*)> EventBoardHander;
		typedef std::function<void(void*, EventBoardClick*)> EventBoardClickHander;
		typedef std::function<void(void*, EventSizeChange*)> EventSizeChangeHander;

	}
}
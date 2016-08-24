```cpp
enum class EventType :int {
			EventOther, //其他事件，大概就是未知事件
			EventMouseMove, //鼠标移动事件
			EventMouseClick, //鼠标点击事件
			EventMouseWheel, //鼠标滑轮移动事件
			EventBoardClick //键盘按键事件
		};


		//Base Event
		struct EventBase {

		};


		//MouseMove Event
		struct EventMouseMove :EventBase {
			int x, y; //鼠标移动，x和y是移动后的坐标
		};

		//enum of mouse button
		enum MouseButton {
			Left, Middle, Right //鼠标按键的枚举
		};

		//MouseClick Event
		struct EventMouseClick :EventBase {
			int x, y; //鼠标点击
			bool IsDown; //是否按下
			MouseButton button; //哪个键
		};

		//MouseWheel Event
		struct EventMouseWheel :EventBase {
			int x, y; //鼠标滑轮移动的时候x,y坐标
			int offest; //the mouse wheel move + is up,- is down
			滑轮移动的指，120为基本单位
		};




		//BoardClick Event
		struct EventBoardClick :EventBase {
			Keycode keycode; //按键的枚举
			bool IsDown;  //按键是否被按下
		}; 

		//SizeChange Event
		struct EventSizeChange :EventBase {
			int last_width, last_height; //目前没有使用
			int now_width, now_height;
		};

```

概述：
>主要用于的在发生事件的时候传递事件的参数信息

```cpp
class EventHandler {
		public:
		    //重载运算符，对应事件的函数可以通过这样的代码加载进去
		    //Eventhandlers+=FunctionName;
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
            //通过事件函数中的sender指针获取发送消息的窗口

		};
```

```cpp
class Page {
		private:
			friend class Window; 
		protected:
			ASNET::Graph::Graph*       graph; 
			//在这个页面被加载的时候，这个graph就指向
			//Window类里面的GraphRender了
		protected:
		    //和Window类一样，但是这些函数只会在这个页面被使用的时候触发
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
			virtual void OnDraw(void* sender, ASNET::Graph::Graph* render); 
			virtual void OnLoading(void* sender, void* any);
			//在被加载的时候会触发
		protected:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
			ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler;
			ASNET::Event::EventGraphDrawHandlers		GraphDrawHandler;
			
		public:
			Page();
		};
```

概述：
>思路是这样的，对于一个窗口放入这些页面，我们可以通过跳转不同的页面 
实现程序的内容的跳转，便于代码。
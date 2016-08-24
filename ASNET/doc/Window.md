```cpp
class Window {
	protected:
		HWND								Hwnd; //窗口句柄
		MSG									Message; //窗口消息类型
		HINSTANCE							Hinstance; //程序实例句柄
		
		ASNET::Page::Page*                  UsedPage; //使用到的页面
		std::vector<ASNET::Page::Page*>     Pages; //页面集合
	private:

	protected:
		int									Width; //宽度
		int									Height; //高度
		LPCWSTR								IcoName; //图标文件名
		LPCWSTR								Title; //窗口标题
	
		ASNET::Graph::Graph*                GraphRender; //2D渲染
		int									NowPage; 
		//现在使用的页面在Pages中的索引
	private:
		ASNET::Event::EventType CoreGetEventArgs(
			int message, ASNET::Event::EventBase* &e);
		void CoreComputeEvents(int message);
	protected: //继承的时候可以重载的函数，作用看函数名
		virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
		virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
		virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
		virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
		virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
		virtual void OnLoading(); //Load the Window,after window create
        //在创建窗口后这个函数被运行
		void		 Initalize();//use it before use any function
	    //在继承的类的构造函数里面使用他对窗口初始化
		void         InitalizeGraphUI(); //use it before the GraphRender 
		如果要使用GraphRender这个成员，请在Initalize后使用他
	protected:
		ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
		ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
		ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
		ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
		ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
		ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
		ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler;
		//各种事件的handles，可以将事件函数放入里面
	public:
		Window();
		void AddPage(ASNET::Page::Page* page);
        //加入一个页面
		void DeletePage(int index);
        //删除一个页面，index是Pages里面对应索引
		void ShowPage(int index);
        //将某个页面设为使用
		void NextPage();
        //到下一个页面
		auto NowUsedPage()->ASNET::Page::Page*;
        //返回现在使用的页面
		auto NowPageNum()->int;
        //返回现在的页面的个数
		void Run();
        //主程序，运行
		void Show();
        //显示窗口
		void Hide();
        //隐藏窗口
		void Release();
		//释放资源
	};
```

概述：  
>本质上是这个只是一个基类，需要对其进行继承然后再使用  
考虑到如果熟悉这部分概念的话应该没什么好解释的怎么用.  

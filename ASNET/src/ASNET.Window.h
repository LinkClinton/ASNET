#pragma once
#include<vector>
#include<Windows.h>

#include"ASNET.Graph.h"
#include"ASNET.Graph.Direct3D.h"

#include"ASNET.Window.Keycode.h"
#include"ASNET.Window.Event.h"
#include"ASNET.Window.Page.h"

/*
* 窗口类，简单的来说可以支持创建窗口
* 然后其内容并不是有窗口类决定，而是Page类
* 同样这只是一个基类而已
* 直接用Direct3DGraph代替了Graph，那么就代表我们需要在使用到着色器的时候使用函数SetShader
* 窗口使用的时候大小改变的时候任然将其缩放，这代表这无论窗口多大都认为其大小是创建的时候的大小
*/


namespace ASNET {
	
	//窗口基类
	class Window {
	protected:
		HWND								Hwnd; //句柄
		MSG									Message; //窗口消息
		HINSTANCE							Hinstance; //实例句柄
		
		ASNET::Page::Page*                  UsedPage; //使用的Page
		std::vector<ASNET::Page::Page*>     Pages; //Page集合
	protected:
		Graph::Direct3D::GraphDirect3D*     Graph; //使用的渲染接口
	protected:
		int									Width; //宽度
		int									Height; //高度
		LPCWSTR								IcoName; //Ico图标文件名
		LPCWSTR								Title; //窗口标题
	
		int									NowPage; //现在使用的Page在集合里面的索引
	protected:
		float                               WidthScale; //最开始的窗口宽度和现在窗口宽度的比值
		float                               HeightScale; //最开始的窗口高度和现在窗口高度的比值
		int									MousePosx; //鼠标位置
		int									MousePosy; //鼠标位置
	private:
		//获取事件
		ASNET::Event::EventType CoreGetEventArgs(
			int message, ASNET::Event::EventBase* &e);
		//处理事件
		void CoreComputeEvents(int message);
	protected:
		//当鼠标移动的时候触发
		virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
		//当鼠标滑轮滚动的时候触发
		virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
		//当鼠标按键弹起的时候触发
		virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
		//当鼠标按键按下的时候触发
		virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		//当键盘按键按下的时候触发
		virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
		//当键盘按键弹起的时候触发
		virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		//当窗口大小改变的时候触发
		virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
		//在窗口加载的时候触发，将会在Initllize里面
		virtual void OnLoading(); //Load the Window,after window create
		//当得到焦点的时候触发
		virtual void OnGetFocus(void* sender);
		//当失去焦点的时候触发
		virtual void OnLostFocus(void* sender);
		//当鼠标离开窗口的时候触发
		virtual void OnMouseLeave(void* sender);
		//在构造函数里面使用
		void		 Initalize();//use it before use any function
	protected:
		ASNET::Event::EventGetFocusHandlers         GetFocusHandler; //获取焦点事件集合
		ASNET::Event::EventLostFocusHandlers        LostFocusHandler; //失去焦点事件集合
		ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler; //鼠标移动事件集合
		ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler; //鼠标滑轮滚动事件集合
		ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler; //鼠标按键弹起事件集合
		ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler; //鼠标按键按下事件集合
		ASNET::Event::EventBoardClickHandlers		BoardUpHandler; //键盘按键弹起事件集合
		ASNET::Event::EventBoardClickHandlers		BoardDownHandler; //键盘按键按下事件集合
		ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler; //窗口大小事件集合
		ASNET::Event::EventMouseLeaveHandlers       MouseLeaveHandler; //鼠标离开窗口事件
		
	public:
		//默认构造函数
		Window();
		//添加一个Page
		void AddPage(ASNET::Page::Page* page);
		//删除一个Page
		void DeletePage(int index);
		//显示某个Page
		void ShowPage(int index, void* any = nullptr);
		//跳转到下一个Page
		void NextPage(void* any = nullptr);
		//返回现在使用的Page的指针
		auto NowUsedPage()->ASNET::Page::Page*;
		//返回现在有多少个Page在集合里面
		auto NowPageNum()->int;
		//运行
		void Run();
		//显示窗口
		void Show();
		//隐藏窗口
		void Hide();
		//释放资源
		void Release();


		//返回某个按键信息,true表示按下false表示弹起
		bool GetKeyState(ASNET::Keycode keycode); //true is down ,false is up
		//返回鼠标位置
		auto GetMousePosx()->int;
		//返回鼠标位置
		auto GetMousePosy()->int;
		//返回窗口宽度
		auto GetWidth()->int;
		//返回窗口高度
		auto GetHeight()->int;
	};
}


#include"ASNET.Window.Keycode.h"
#include"ASNET.Window.Event.h"
#include"ASNET.Window.Page.h"



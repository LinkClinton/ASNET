#pragma once
#include"ASNET.Window.Event.h"
#include"ASNET.Control.h"
#include"ASNET.Graph.h"


#include<vector>

/*
* 用于加载控件和绘制内容的
* 当一个页面被使用的时候，其所有的函数或者什么才属于有效的
* 一个控件如果要加载必须用Page注册
* 如果要废除一个控件可以用Page卸载
* 当然这是一个基类
*/

namespace ASNET {
	class Window;
	namespace Page {

		//事件优先级，窗口最优先，然后界面然后控件
		//Page类
		class Page {
		protected:
			void*                                  Parent; //父亲一级的指针
		private:
			ASNET::Control::Control*               ControlsFocus; //得到焦点的控件
			std::vector<ASNET::Control::Control*>  Controls; //控件集合
			//处理关于控件的鼠标移动事件
			void OnControlMouseMove(void* sender, ASNET::Event::EventMouseMove* e); 
			//处理关于控件的鼠标滚轮滑动事件
			void OnControlMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			//处理关于控件的鼠标按键弹起事件
			void OnControlMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//处理关于控件的鼠标按键按下事件
			void OnControlMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			//处理关于控件的按键按下事件
			void OnControlKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//处理关于控件的按键弹起事件
			void OnControlKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			//处理关于控件绘制事件
			void OnControlDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		protected:
			//处理鼠标移动事件
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			//处理鼠标滑轮滚动事件
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			//处理鼠标按键弹起事件
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//处理鼠标按键按下事件
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			//处理键盘按键按下事件
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//处理键盘按键弹起事件
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			//处理窗口大小事件
			virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
			//处理鼠标离开窗口事件
			virtual void OnMouseLeave(void* sender);
			//处理绘制事件，将描述这个类怎么绘制出来
			virtual void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render); 
			//初始化页面，在页面被AddPage的时候触发
			virtual void OnInitalize(void* sender);
			//加载页面事件，当页面被ShowPage的时候触发
			virtual void OnLoading(void* sender, void* any);
			//卸载页面事件，当页面被其他页面替换的时候触发
			virtual void OnUnLoading(void* sender);
			//在控件取消被使用的时候触发
			void		 OnStoping();
		protected:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler; //鼠标移动事件集合
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler; //鼠标滑轮滚动事件集合
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler; //鼠标按键弹起事件集合
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler; //鼠标按键按下事件集合
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler; //键盘按键弹起事件集合
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler; //键盘按键按下事件集合
			ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler; //窗口大小事件集合
			ASNET::Event::EventMouseLeaveHandlers       MouseLeaveHandler; //鼠标离开窗口事件集合

			ASNET::Graph::Direct3D::GraphDirect3D*		ParentGraph; //渲染的指针接口
			friend class Window; 
			friend class ASNET::Event::EventHandler;
		public:
			//构造函数
			Page();

			//注册控件
			void RegisterControl(ASNET::Control::Control* control);
			//取消注册某个控件
			void UnRegisterControl(ASNET::Control::Control* control);
			//设置获取焦点的控件，之前获取焦点的控件将会失去焦点
			void SetFocus(ASNET::Control::Control* control);
		};
	}
}
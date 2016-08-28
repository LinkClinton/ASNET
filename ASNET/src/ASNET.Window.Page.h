#pragma once
#include"ASNET.Window.Event.h"
#include"ASNET.Control.Base.h"
#include"ASNET.Graph.h"


#include<vector>

//用于加载控件和绘制内容的
//当一个页面被使用的时候，其所有的函数或者什么才属于有效的
//一个控件如果要加载必须用Page注册
//如果要废除一个控件可以用Page卸载
//当然这是一个基类
namespace ASNET {
	class Window;
	namespace Page {

		//事件优先级，窗口最优先，然后界面然后控件

		class Page {
		private:
			std::vector<ASNET::Control::Control*>  Controls;
			void OnControlMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			void OnControlMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			void OnControlMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			void OnControlMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			void OnControlKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			void OnControlKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		protected:
			ASNET::Graph::Graph*       graph;
		protected:
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
			virtual void OnDraw(void* sender, ASNET::Graph::Graph* render); 
			virtual void OnLoading(void* sender, void* any);
		protected:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
			ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler;
			
		
			friend class Window;
		public:
			Page();

			void RegisterControl(ASNET::Control::Control* control);

			void UnRegisterControl(ASNET::Control::Control* control);
		};
	}
}
#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"

#include"ASNET.Control.Animation.h"

/*
* 写下当时的想法，保证以后写的时候能够继续
* 作为控件的基类，所有的控件以此作为基础
* 并继承，具体的控件并不支持你去继承他，因此在具体的控件中虚函数基本上无用
* 控件基本的类中有描述这个类大小，以及其状态  
* 是否被激活或者得到焦点或者被显示
* 所有的控件会被认为是2D的，因此将会在OnDraw后再去画，他无法被非控件覆盖，所有的控件被认为是最顶层的
* 不保证控件的绘制顺序
*/

/*
* 控件的焦点仅仅只是表示在这个页面被显示的时候他是否获取了焦点
* 当窗口和或者页面没有使用的时候必然焦点也是无效的
* 一个控件只能属于一个页面，如果一个页面没有使用的话，控件将会保持其原本的状态，但是有些状态还是不会保持。
*/

namespace ASNET {
	namespace Page { class Page; }
	namespace Control {
		
		

		//简单的Control基类，所有的事件，只有在控件范围内才会被使用
		class Control {
		protected:
			bool		 MouseIn; //鼠标是否在控件范围内
			bool		 IsFocus; //控件是否获取了焦点，将会影响控件获取键盘按键信息

			friend class ASNET::Page::Page; 
			
			//标准控件绘制方案,大部分控件使用此绘制方案,集成了控件大致外观绘制
			virtual void OnStdDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		protected:
			
			//鼠标移开后的动画
			ASNET::Control::Animation LeaveAnimation;
			//初始化鼠标移开后的动画绘制方案
			void StartLeaveAnimation();
			//描述控件当鼠标移开后的动画绘制方案,图片作为背景的时候无效
			void OnLeaveAnimationDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);


			//初始化动画数据
			void InitalizeAnimation();

			ASNET::Graph::Graph*     ParentGraph; //渲染控件的接口指针
		protected:
			//当鼠标移动的时候触发
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e); 
			//当鼠标滚轮滑动的时候触发
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e); 
			//当鼠标按钮弹起的时候触发
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//当鼠标按钮按下的时候触发
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e); 
			//当键盘按键按下的时候触发
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//当键盘按键弹起的时候触发
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			//当获取焦点的时候触发
			virtual void OnGetFocus(void* sender);
			//当失去焦点的时候触发
			virtual void OnLostFocus(void* sender);
			//描述这个控件的绘制方法
			virtual void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
			//描述当父亲页面被切换的时候的事件
			virtual void OnStoping();
		public:
			ASNET::Event::EventGetFocusHandlers         GetFocusHandler; //获取焦点事件集合
			ASNET::Event::EventLostFocusHandlers        LostFocusHandler; //失去焦点事件集合
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler; //鼠标移动事件的集合
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler; //鼠标滑轮移动事件的集合
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler; //鼠标按钮弹起事件的集合
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler; //鼠标按钮按下事件的集合
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler; //键盘按键弹起事件的集合
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler; //键盘按键按下事件的集合

		public:
			void* Parent; //父亲一级的指针

			bool  IsActive; //控件是否被激活
			
			bool  Visibility; //控件是否可见 

			bool  Selectibility; //鼠标在其范围内的时候是否显示边框表示选中,使用图片背景时候无效

			ASNET::Graph::Color    BackColor; //背景颜色
			ASNET::Graph::Color    SelectBackColor; //被选中后的背景颜色,有默认值

			ASNET::Graph::Image*     BackImage; //背景图片，如果为空就用背景颜色代替

			float Left; //控件范围left
			float Right; //控件范围right
			float Top; //控件范围top
			float Bottom; //控件范围bottom

		public:
			//默认构造函数
			Control();
			//控件范围
			operator ASNET::Graph::Rect(); 
			

		};



		//默认的被选中后控件的背景颜色
		static ASNET::Graph::Color ControlBackGroundColor = D2D1::ColorF::Gray;
		static float ControlColorAlpha = 0.2f;

	}
}



#include"ASNET.Control.Label.h"
#include"ASNET.Control.Timer.h"
#include"ASNET.Control.Button.h"
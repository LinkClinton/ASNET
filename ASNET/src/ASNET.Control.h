#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"


//写下当时的想法，保证以后写的时候能够继续
//作为控件的基类，所有的控件以此作为基础
//并继承，具体的控件并不支持你去继承他，因此在具体的控件中虚函数基本上无用
//控件基本的类中有描述这个类大小，以及其状态
//是否被激活或者得到焦点或者被显示
//所有的控件会被认为是2D的，因此将会在OnDraw后再去画，他无法被非控件覆盖

//控件的焦点仅仅只是表示在这个页面被显示的时候他是否获取了焦点
//当窗口和或者页面没有使用的时候必然焦点也是无效的

namespace ASNET {
	namespace Page { class Page; }
	namespace Control {
		
		//简单的Color类，和D2D1::Color兼容
		class Color {
		public:
			float r, g, b, a;
			//默认构造函数
			Color();
			//D2D1::Color的赋值
			Color(ASNET::Graph::Color color);
			//D2D1::Color的枚举赋值
			Color(ASNET::Graph::Color::Enum color);
			//赋值
			Color(float _r, float _g, float _b, float _a);
			//赋值
			Color(ASNET::Graph::Color color, float _a);

			//返回D2D1::Color类型
			operator ASNET::Graph::Color();
		};

		//简单的Control基类，所有的事件，只有在控件范围内才会被使用
		class Control {
		private:
			const float  LeaveFrameTime = 0.13f; //鼠标移开动画持续时间
		protected:
			bool		 MouseIn; //鼠标是否在控件范围内
			bool         IsLeaveFrame; //是否处于类似动画渲染的状态
			bool		 IsFocus; //控件是否获取了焦点，将会影响控件获取键盘按键信息

			float        LeaveAlphaTime; //渐变的Alpha
			float        LeaveOldAlpha;  //原始的Alpha
			friend class ASNET::Page::Page;  

			//初始化鼠标移开后的动画绘制方案
			void         InitalizeLeaveFrame();
			//描述控件当鼠标移开后的动画绘制方案,图片作为背景的时候无效
			void         OnLeaveFrameDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);

			//标准控件绘制方案,大部分控件使用此绘制方案
			void         OnStdDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
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
			bool  IsActive; //控件是否被激活
			
			bool  Visibility; //控件是否可见 

			bool  Selectibility; //鼠标在其范围内的时候是否显示边框表示选中,使用图片背景时候无效

			ASNET::Control::Color    BackColor; //背景颜色
			ASNET::Control::Color    SelectBackColor; //被选中后的背景颜色,有默认值

			ASNET::Graph::Image*     BackImage; //背景图片，如果为空就用背景颜色代替

			float Left; //控件范围left
			float Right; //控件范围right
			float Top; //控件范围top
			float Bottom; //控件范围bottom

			ASNET::Graph::Graph*     ParentGraph; //渲染控件的接口指针
		public:
			//默认构造函数
			Control();
			//控件范围
			operator ASNET::Graph::Rect(); 
			

		};




		static Color ControlBackGroundColor = ASNET::Graph::Color::Gray;
		static float ControlColorAlpha = 0.2f;

	}
}



#include"ASNET.Control.Label.h"
#include"ASNET.Control.Timer.h"
#include"ASNET.Control.Button.h"
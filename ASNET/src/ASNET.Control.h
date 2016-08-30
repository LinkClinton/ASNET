#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"


//写下当时的想法，保证以后写的时候能够继续
//作为控件的基类，所有的控件以此作为基础
//并继承，具体的控件并不支持你去继承他，因此在具体的控件中虚函数基本上无用
//控件基本的类中有描述这个类大小，以及其状态
//是否被激活或者得到焦点或者被显示
//所有的控件会被认为是2D的，因此将会在OnDraw后再去画，他无法被任何覆盖
namespace ASNET {
	namespace Page { class Page; }
	namespace Control {

		class Color {
		public:
			float r, g, b, a;
			Color();
			Color(ASNET::Graph::Color color);
			Color(ASNET::Graph::Color::Enum color);
			Color(float _r, float _g, float _b, float _a);

			operator ASNET::Graph::Color();
		};

		//所有的事件，只有在控件范围内才会被使用
		class Control {
		protected:
			bool		 MouseIn;
			friend class ASNET::Page::Page;
		protected:
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			virtual void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		public:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
		public:
			bool  IsActive;
			bool  IsFocus;
			bool  IsShow;

			float Left;
			float Right;
			float Top;
			float Bottom;

			ASNET::Graph::Graph*     ParentGraph;
		public:
			Control();

			operator ASNET::Graph::Rect();

			void Show();

			void Hide();

			void GetFocus();

			void LostFocus();

			void Active();

			void UnActive();

		};


	}
}



#include"ASNET.Control.Label.h"
#include"ASNET.Control.Timer.h"

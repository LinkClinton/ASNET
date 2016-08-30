#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"


//д�µ�ʱ���뷨����֤�Ժ�д��ʱ���ܹ�����
//��Ϊ�ؼ��Ļ��࣬���еĿؼ��Դ���Ϊ����
//���̳У�����Ŀؼ�����֧����ȥ�̳���������ھ���Ŀؼ����麯������������
//�ؼ�����������������������С���Լ���״̬
//�Ƿ񱻼�����ߵõ�������߱���ʾ
//���еĿؼ��ᱻ��Ϊ��2D�ģ���˽�����OnDraw����ȥ�������޷����κθ���
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

		//���е��¼���ֻ���ڿؼ���Χ�ڲŻᱻʹ��
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

#pragma once
#include"ASNET.Window.Event.h"
#include"ASNET.Control.h"
#include"ASNET.Graph.h"


#include<vector>

//���ڼ��ؿؼ��ͻ������ݵ�
//��һ��ҳ�汻ʹ�õ�ʱ�������еĺ�������ʲô��������Ч��
//һ���ؼ����Ҫ���ر�����Pageע��
//���Ҫ�ϳ�һ���ؼ�������Pageж��
//��Ȼ����һ������
namespace ASNET {
	class Window;
	namespace Page {

		//�¼����ȼ������������ȣ�Ȼ�����Ȼ��ؼ�
		//Page��
		class Page {
		private:
			std::vector<ASNET::Control::Control*>  Controls; //�ؼ�����
			//������ڿؼ�������ƶ��¼�
			void OnControlMouseMove(void* sender, ASNET::Event::EventMouseMove* e); 
			//������ڿؼ��������ֻ����¼�
			void OnControlMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			//������ڿؼ�����갴�������¼�
			void OnControlMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//������ڿؼ�����갴�������¼�
			void OnControlMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			//������ڿؼ��İ��������¼�
			void OnControlKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//������ڿؼ��İ��������¼�
			void OnControlKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			//������ڿؼ������¼�
			void OnControlDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		protected:
			//��������ƶ��¼�
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
			//������껬�ֹ����¼�
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
			//������갴�������¼�
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//������갴�������¼�
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			//������̰��������¼�
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//������̰��������¼�
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			//�����ڴ�С�¼�
			virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
			//��������¼����������������ô���Ƴ���
			virtual void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render); 
			//���ؿؼ��¼������ؼ���AddPage��ʱ�򴥷�
			virtual void OnLoading(void* sender, void* any);
		protected:
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler; //����ƶ��¼�����
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler; //��껬�ֹ����¼�����
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler; //��갴�������¼�����
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler; //��갴�������¼�����
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler; //���̰��������¼�����
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler; //���̰��������¼�����
			ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler; //���ڴ�С�¼�����
			
			ASNET::Graph::Direct3D::GraphDirect3D*		ParentGraph; //��Ⱦ��ָ��ӿ�
			friend class Window; 
		public:
			//���캯��
			Page();

			//ע��ؼ�
			void RegisterControl(ASNET::Control::Control* control);
			//ȡ��ע��ĳ���ؼ�
			void UnRegisterControl(ASNET::Control::Control* control);
		};
	}
}
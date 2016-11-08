#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"

#include"ASNET.Control.Animation.h"

/*
* д�µ�ʱ���뷨����֤�Ժ�д��ʱ���ܹ�����
* ��Ϊ�ؼ��Ļ��࣬���еĿؼ��Դ���Ϊ����
* ���̳У�����Ŀؼ�����֧����ȥ�̳���������ھ���Ŀؼ����麯������������
* �ؼ�����������������������С���Լ���״̬  
* �Ƿ񱻼�����ߵõ�������߱���ʾ
* ���еĿؼ��ᱻ��Ϊ��2D�ģ���˽�����OnDraw����ȥ�������޷����ǿؼ����ǣ����еĿؼ�����Ϊ������
* ����֤�ؼ��Ļ���˳��
*/

/*
* �ؼ��Ľ������ֻ�Ǳ�ʾ�����ҳ�汻��ʾ��ʱ�����Ƿ��ȡ�˽���
* �����ںͻ���ҳ��û��ʹ�õ�ʱ���Ȼ����Ҳ����Ч��
* һ���ؼ�ֻ������һ��ҳ�棬���һ��ҳ��û��ʹ�õĻ����ؼ����ᱣ����ԭ����״̬��������Щ״̬���ǲ��ᱣ�֡�
*/

namespace ASNET {
	namespace Page { class Page; }
	namespace Control {
		
		

		//�򵥵�Control���࣬���е��¼���ֻ���ڿؼ���Χ�ڲŻᱻʹ��
		class Control {
		protected:
			bool		 MouseIn; //����Ƿ��ڿؼ���Χ��
			bool		 IsFocus; //�ؼ��Ƿ��ȡ�˽��㣬����Ӱ��ؼ���ȡ���̰�����Ϣ

			friend class ASNET::Page::Page; 
			
			//��׼�ؼ����Ʒ���,�󲿷ֿؼ�ʹ�ô˻��Ʒ���,�����˿ؼ�������ۻ���
			virtual void OnStdDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		protected:
			
			//����ƿ���Ķ���
			ASNET::Control::Animation LeaveAnimation;
			//��ʼ������ƿ���Ķ������Ʒ���
			void StartLeaveAnimation();
			//�����ؼ�������ƿ���Ķ������Ʒ���,ͼƬ��Ϊ������ʱ����Ч
			void OnLeaveAnimationDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);


			//��ʼ����������
			void InitalizeAnimation();

			ASNET::Graph::Graph*     ParentGraph; //��Ⱦ�ؼ��Ľӿ�ָ��
		protected:
			//������ƶ���ʱ�򴥷�
			virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e); 
			//�������ֻ�����ʱ�򴥷�
			virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e); 
			//����갴ť�����ʱ�򴥷�
			virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//����갴ť���µ�ʱ�򴥷�
			virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e); 
			//�����̰������µ�ʱ�򴥷�
			virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//�����̰��������ʱ�򴥷�
			virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
			//����ȡ�����ʱ�򴥷�
			virtual void OnGetFocus(void* sender);
			//��ʧȥ�����ʱ�򴥷�
			virtual void OnLostFocus(void* sender);
			//��������ؼ��Ļ��Ʒ���
			virtual void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
			//����������ҳ�汻�л���ʱ����¼�
			virtual void OnStoping();
		public:
			ASNET::Event::EventGetFocusHandlers         GetFocusHandler; //��ȡ�����¼�����
			ASNET::Event::EventLostFocusHandlers        LostFocusHandler; //ʧȥ�����¼�����
			ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler; //����ƶ��¼��ļ���
			ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler; //��껬���ƶ��¼��ļ���
			ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler; //��갴ť�����¼��ļ���
			ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler; //��갴ť�����¼��ļ���
			ASNET::Event::EventBoardClickHandlers		BoardUpHandler; //���̰��������¼��ļ���
			ASNET::Event::EventBoardClickHandlers		BoardDownHandler; //���̰��������¼��ļ���

		public:
			void* Parent; //����һ����ָ��

			bool  IsActive; //�ؼ��Ƿ񱻼���
			
			bool  Visibility; //�ؼ��Ƿ�ɼ� 

			bool  Selectibility; //������䷶Χ�ڵ�ʱ���Ƿ���ʾ�߿��ʾѡ��,ʹ��ͼƬ����ʱ����Ч

			ASNET::Graph::Color    BackColor; //������ɫ
			ASNET::Graph::Color    SelectBackColor; //��ѡ�к�ı�����ɫ,��Ĭ��ֵ

			ASNET::Graph::Image*     BackImage; //����ͼƬ�����Ϊ�վ��ñ�����ɫ����

			float Left; //�ؼ���Χleft
			float Right; //�ؼ���Χright
			float Top; //�ؼ���Χtop
			float Bottom; //�ؼ���Χbottom

		public:
			//Ĭ�Ϲ��캯��
			Control();
			//�ؼ���Χ
			operator ASNET::Graph::Rect(); 
			

		};



		//Ĭ�ϵı�ѡ�к�ؼ��ı�����ɫ
		static ASNET::Graph::Color ControlBackGroundColor = D2D1::ColorF::Gray;
		static float ControlColorAlpha = 0.2f;

	}
}



#include"ASNET.Control.Label.h"
#include"ASNET.Control.Timer.h"
#include"ASNET.Control.Button.h"
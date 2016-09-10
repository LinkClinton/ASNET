#pragma once
#include"ASNET.Graph.h"
#include"ASNET.Window.Event.h"


//д�µ�ʱ���뷨����֤�Ժ�д��ʱ���ܹ�����
//��Ϊ�ؼ��Ļ��࣬���еĿؼ��Դ���Ϊ����
//���̳У�����Ŀؼ�����֧����ȥ�̳���������ھ���Ŀؼ����麯������������
//�ؼ�����������������������С���Լ���״̬
//�Ƿ񱻼�����ߵõ�������߱���ʾ
//���еĿؼ��ᱻ��Ϊ��2D�ģ���˽�����OnDraw����ȥ�������޷����ǿؼ�����

//�ؼ��Ľ������ֻ�Ǳ�ʾ�����ҳ�汻��ʾ��ʱ�����Ƿ��ȡ�˽���
//�����ںͻ���ҳ��û��ʹ�õ�ʱ���Ȼ����Ҳ����Ч��

namespace ASNET {
	namespace Page { class Page; }
	namespace Control {
		
		//�򵥵�Color�࣬��D2D1::Color����
		class Color {
		public:
			float r, g, b, a;
			//Ĭ�Ϲ��캯��
			Color();
			//D2D1::Color�ĸ�ֵ
			Color(ASNET::Graph::Color color);
			//D2D1::Color��ö�ٸ�ֵ
			Color(ASNET::Graph::Color::Enum color);
			//��ֵ
			Color(float _r, float _g, float _b, float _a);
			//��ֵ
			Color(ASNET::Graph::Color color, float _a);

			//����D2D1::Color����
			operator ASNET::Graph::Color();
		};

		//�򵥵�Control���࣬���е��¼���ֻ���ڿؼ���Χ�ڲŻᱻʹ��
		class Control {
		private:
			const float  LeaveFrameTime = 0.13f; //����ƿ���������ʱ��
		protected:
			bool		 MouseIn; //����Ƿ��ڿؼ���Χ��
			bool         IsLeaveFrame; //�Ƿ������ƶ�����Ⱦ��״̬
			bool		 IsFocus; //�ؼ��Ƿ��ȡ�˽��㣬����Ӱ��ؼ���ȡ���̰�����Ϣ

			float        LeaveAlphaTime; //�����Alpha
			float        LeaveOldAlpha;  //ԭʼ��Alpha
			friend class ASNET::Page::Page;  

			//��ʼ������ƿ���Ķ������Ʒ���
			void         InitalizeLeaveFrame();
			//�����ؼ�������ƿ���Ķ������Ʒ���,ͼƬ��Ϊ������ʱ����Ч
			void         OnLeaveFrameDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);

			//��׼�ؼ����Ʒ���,�󲿷ֿؼ�ʹ�ô˻��Ʒ���
			void         OnStdDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
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
			bool  IsActive; //�ؼ��Ƿ񱻼���
			
			bool  Visibility; //�ؼ��Ƿ�ɼ� 

			bool  Selectibility; //������䷶Χ�ڵ�ʱ���Ƿ���ʾ�߿��ʾѡ��,ʹ��ͼƬ����ʱ����Ч

			ASNET::Control::Color    BackColor; //������ɫ
			ASNET::Control::Color    SelectBackColor; //��ѡ�к�ı�����ɫ,��Ĭ��ֵ

			ASNET::Graph::Image*     BackImage; //����ͼƬ�����Ϊ�վ��ñ�����ɫ����

			float Left; //�ؼ���Χleft
			float Right; //�ؼ���Χright
			float Top; //�ؼ���Χtop
			float Bottom; //�ؼ���Χbottom

			ASNET::Graph::Graph*     ParentGraph; //��Ⱦ�ؼ��Ľӿ�ָ��
		public:
			//Ĭ�Ϲ��캯��
			Control();
			//�ؼ���Χ
			operator ASNET::Graph::Rect(); 
			

		};




		static Color ControlBackGroundColor = ASNET::Graph::Color::Gray;
		static float ControlColorAlpha = 0.2f;

	}
}



#include"ASNET.Control.Label.h"
#include"ASNET.Control.Timer.h"
#include"ASNET.Control.Button.h"
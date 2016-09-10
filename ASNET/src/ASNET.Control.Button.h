#pragma once
#include"ASNET.Control.h"


//�򵥵İ�ť��
namespace ASNET {
	namespace Control {

		//��ť���
		enum class ButtonStyle {
			Simple
		};


		//�򵥵İ�ť��
		class Button :public Control {
		private:
			//Simple���͵İ�ť���Ʒ���
			void SimpleDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render);
		protected:
			bool					 IsKeyDown; //�Ƿ񱻰���
		protected:
			//������λ���
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
			//����갴ť�����ʱ�򴥷�
			void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
			//����갴ť���µ�ʱ�򴥷�
			void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
			//�����̰������µ�ʱ�򴥷�
			void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
			//�����̰��������ʱ�򴥷�
			void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		public:
			wchar_t*				 Name;//��ť������
			wchar_t*				 Text;//��ť���ı�����


			ButtonStyle              Style; //��ť�ķ��

			
			ASNET::Control::Color    TextColor; //�ı���ɫ

			ASNET::Graph::Font*      TextFont;  //ʹ�õ�����


			ASNET::Graph::TextAlign  Horizontal; //�ı���ƽ�з�����Ű�
			ASNET::Graph::TextAlign  Vertical; //�ı�����ֱ������Ű�

		public:
			//���캯��
			Button(ASNET::Graph::Graph* graph,
				float left, float right, float top,
				float bottom, wchar_t* name, wchar_t* text, ASNET::Graph::Font* font,
				ASNET::Control::ButtonStyle style = ASNET::Control::ButtonStyle::Simple,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Center,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Center);
			//�ǵ�delete
			~Button(); 



			
		};


	}
}
#pragma once

#include"ASNET.Control.h"

namespace ASNET {

	namespace Control {

	
		//�ı��ؼ���һ����Ϊһ���ؼ������ݣ������ǵ����Ŀؼ�
		class Text {
		private:
			ASNET::Graph::Graph*    ParentGraph; //��Ⱦ����
			ASNET::Graph::Interface ParentInterface; //��Ⱦ�ӿ�

			IDWriteTextLayout*    g_text; //�ı�����
			ID2D1SolidColorBrush* g_brush; //��ˢ

			ASNET::Graph::Word    g_word; //�ı�����
			ASNET::Graph::Size    g_size; //�ı����С
			ASNET::Graph::Color   g_color; //�ı���ɫ

			int				      g_cursor_pos; //���λ��
			bool                  g_cursor_show; //�ı��Ƿ���ʾ
			bool				  g_cursor_direct;//�ı�����true�����ڵ�ǰ�ַ������


			int					  g_text_left_pos; //�����ı��ü����������ı��������ʾ��λ��
			int                   g_text_right_pos; //�����ı��ü����������ı����ұߵ���ʾ��λ��
			bool                  g_text_clip; //�Ƿ�ʹ���ı��ü�
		protected:
			void InitalizeCursorAnimation(); //��ʼ����궯��

			ASNET::Control::Animation CursorAnimation; //��궯��
		private:
			void UpdateText(); //�����ı�����
			void UpdateColor(); //�����ı���ˢ
			void DrawCursor(ASNET::Graph::Point origin); //���ƹ��
		public:
			//���캯��
			Text(ASNET::Graph::Graph* graph, ASNET::Graph::Word word,
				ASNET::Graph::Size size, ASNET::Graph::Font* fontface,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			//�����ı�����
			void SetWord(ASNET::Graph::Word word);

			//�����ı���ɫ
			void SetColor(ASNET::Graph::Color color);
			
			//�Ƿ������ı��ü�
			void SetClip(bool is);

			//������߲��ֵ��ı��ü�
			void SetLeftClip(int left);

			//�����ұ߲��ֵ��ı��ü�
			void SetRightClip(int right);
			
			//�����ı�����
			auto GetWord()->ASNET::Graph::Word;
			
			//�����ı���ɫ
			auto GetColor()->ASNET::Graph::Color;

			//����ĳ���ַ�������λ��
			auto GetRealX(int textposition = 0)->float;
			
			//����ĳ���ַ�������λ��
			auto GetRealY(int textposition = 0)->float;
			
			//����ĳ���ַ�������λ��
			auto GetRealPosition(int textposition = 0, bool isleft = false)->ASNET::Graph::Point;

			//�����ı��ĸ߶�
			auto GetHeight()->float;
			
			//���ؾ���������ص�������ַ���λ�ã�����ϵ������ı�
			auto GetTextPosition(ASNET::Graph::Point point)->int;

			//�����Լ�
			void OnDraw(ASNET::Graph::Point origin);

			ASNET::Graph::TextAlign Horizontal; //����
			ASNET::Graph::TextAlign Vertical; //����

			ASNET::Graph::Font* FontFace; //����
			
			//����һ���ַ�
			void Insert(wchar_t buff);

			//ɾ��һ���ַ�
			void Delete();

			//��ʾ���
			void CursorShow(); 

			//���ع��
			void CursorHide();

			//��������ƶ�
			void CursorUp();

			//��������ƶ�
			void CursorLeft();

			//��������ƶ�
			void CursorDown();

			//��������ƶ�
			void CuesorRight();
			
			//���ù���λ��
			void SetCursorPosition(int textposition = 0 , bool IsLeft = false);

			//���ù���λ�ã������õ�����point������ַ���λ��,����ϵ������ı�
			void SetCursorPosition(ASNET::Graph::Point point);



			static auto KeycodeToWideChar(void* sender, ASNET::Keycode keycode)->wchar_t;
		};

	}

}
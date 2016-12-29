#pragma once

#include<map>
#include<vector>
#include<functional>
#ifdef _WINDOWS7
#include<d2d1.h>
#else 
#include<d2d1_1.h>
#endif // _WINDOWS7


#include<d3d11.h>
#include<dwrite.h>
#include<wincodec.h>

#include"ASNET.Control.Timer.h"

#include"ASNET.Physics.h"

namespace ASNET {

	namespace Graph {

		class Graph;


		typedef D2D_RECT_F		 Rect; //Դ��D2D_RECT_F
		typedef D2D_SIZE_F       Size; //Դ��D2D_SIZE_F
		typedef D2D_POINT_2F     Point; //Դ��D2D_POINT_2F
		typedef std::wstring     Word; //Դ��wstring


		class Color :public ASNET::Physics::Vector4 {
		public:
			Color();

			Color(Color color, float a);

			Color(D2D1::ColorF::Enum color);

			Color(ASNET::Physics::Vector4 vector4);

			Color(float r, float g, float b, float a);

			operator D2D1::ColorF();

		};


		//����
		class Font {
		private:
			ASNET::Graph::Graph* ParentGraph; //��Ⱦ�õ�ָ��ӿ�

			IDWriteTextFormat*	 textformat; //textformat
			friend class Graph;
		public:
			//���캯��
			Font(ASNET::Graph::Graph* Graph);
			
			//�����������ǵ�delete
			~Font();
			
			//���������С
			auto FontSize()->float;
			
			//���¼�������
			void reset(ASNET::Graph::Word fontname, float fontsize);

			operator IDWriteTextFormat*();
		};


		//ͼƬ
		class Image {
		protected:
			ASNET::Graph::Graph* ParentGraph; //��Ⱦ�õ�ָ��ӿ�
			ID2D1Bitmap* bitmap; //λͼ����

			friend class Graph;

			Image() = default;
		public:
			//���캯��
			Image(ASNET::Graph::Graph* Graph);
			
			//��������
			~Image();
			
			//����ͼƬ���
			auto GetWidth()->float;
			
			//����ͼƬ�߶�
			auto GetHieght()->float;
			
			//���¼���ͼƬ
			void reset(ASNET::Graph::Word filename);
		};


		//���岼��
		enum class TextAlign {
			Left, Center, Right, Top, Bottom
		};

		//�ṩһ���棬������Ϊһ������
		class Surface {
		private:
			ASNET::Graph::Graph* ParentGraph; //��Ⱦ�ӿ�
		protected:
			float g_width; //���
			float g_height; //�߶�
			float x; //λ��x
			float y; //λ��y

			void BeginDraw(); //��ʼ����
			void EndDraw(); //��������
		public:
			//���캯��
			Surface(ASNET::Graph::Graph* graph); 

			//������
			virtual void DrawLine(ASNET::Graph::Point p1, ASNET::Graph::Point p2,
				ASNET::Graph::Color color, float width = 1.0f);

			//���ƾ���
			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = D2D1::ColorF::White);

			//����ͼƬ
			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);

			//��������
			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			//���ؿ��
			auto Width()->float;

			//���ظ߶�
			auto Height()->float;

			//����λ��x
			auto PositionX()->float;

			//����λ��y
			auto PositionY()->float;

			//���ÿ��
			void SetWidth(float width);

			//���ø߶�
			void SetHeight(float height);

			//����λ��x
			void SetPositionX(float posx);

			//����λ��Y
			void SetPositionY(float posy);

		};

		//�ӿڣ����ڻ�ȡGraph�ڲ��Ľӿ�
		class Interface {
		public:
			ID2D1RenderTarget*   DeviceContext2D;
			ID3D11DeviceContext* DeviceContext3D;
			IDWriteFactory*      DeviceContextWrite;
		};
		

	}

}
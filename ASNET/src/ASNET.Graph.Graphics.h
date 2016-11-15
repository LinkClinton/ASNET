#pragma once

#include<map>
#include<vector>
#include<functional>

#include<d2d1.h>
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
			ASNET::Graph::Graph* ParentGraph;
		protected:
			float g_width;
			float g_height;
			float x;
			float y;

			void BeginDraw();
			void EndDraw();
		public:
			Surface(ASNET::Graph::Graph* graph);

			virtual void DrawLine(ASNET::Graph::Point p1, ASNET::Graph::Point p2,
				ASNET::Graph::Color color, float width = 1.0f);

			virtual void DrawRectangle(ASNET::Graph::Rect rect,
				ASNET::Graph::Color color, float width = 1.0f, bool IsFill = false,
				ASNET::Graph::Color FillColor = D2D1::ColorF::White);

			virtual void DrawImage(ASNET::Graph::Image* image,
				ASNET::Graph::Rect rect);

			virtual void DrawWord(ASNET::Graph::Word word,
				ASNET::Graph::Rect rect, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			auto Width()->float;
			auto Height()->float;
			auto PositionX()->float;
			auto PositionY()->float;

			void SetWidth(float width);
			void SetHeight(float height);
			void SetPositionX(float posx);
			void SetPositionY(float posy);

		};

		class Interface {
		public:
			ID2D1RenderTarget*   DeviceContext2D;
			ID3D11DeviceContext* DeviceContext3D;
			IDWriteFactory*      DeviceContextWrite;
		};
		

	}

}
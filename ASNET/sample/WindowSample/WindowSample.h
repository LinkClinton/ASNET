#pragma once
#include<Window.h>
namespace ASNET {
	namespace Sample {

		

		//�̳�ԭ���Ĵ�����
		class WindowSample :public ASNET::Window {
		private:
			int MousePosX; //���λ��
			int MousePosY; //���λ��

		
			friend class PageSample; //���������Է�����˽�г�Ա
		protected:
			void OnLoading()override;
			//�麯���Լ�����д������ǹ�������ƶ���,�������������ƶ���ʱ��ᱻ����
			//sender ͨ��������Ƿ�����Ϣ�Ĵ��ڵ�ָ�룬����һ������������������Ϣ
			void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e)override;
			//�����Լ�дһ���������ؽ�ȥ,����Ҫ�ͺ���Ҫ��һ��,Ҫǰ���static
			static void MyMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
		public:
			WindowSample(); //����д���캯��
		};

		//�̳�ԭ����ҳ�棬ҳ����ʵ����һ�����ڵ�����
		//һ�����ڵ�ҳ������л�
		class PageSample :public ASNET::Page::Page {
		protected:
			//�����ҳ�汻����ΪҪ�õ�ҳ���ʱ������
			void OnLoading(void* sender, void* any)override;
			//�������ҳ��
			void OnDraw(void* sender, ASNET::Graph::Graph* render)override;
		public:
			PageSample(); //���캯������д
		};

	}
}
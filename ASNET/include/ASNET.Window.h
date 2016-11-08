#pragma once
#include<vector>
#include<Windows.h>

#include"ASNET.Graph.h"
#include"ASNET.Graph.Direct3D.h"

#include"ASNET.Window.Keycode.h"
#include"ASNET.Window.Event.h"
#include"ASNET.Window.Page.h"

/*
* �����࣬�򵥵���˵����֧�ִ�������
* Ȼ�������ݲ������д��������������Page��
* ͬ����ֻ��һ���������
* ֱ����Direct3DGraph������Graph����ô�ʹ���������Ҫ��ʹ�õ���ɫ����ʱ��ʹ�ú���SetShader
* ����ʹ�õ�ʱ���С�ı��ʱ����Ȼ�������ţ�����������۴��ڶ����Ϊ���С�Ǵ�����ʱ��Ĵ�С
*/


namespace ASNET {
	
	//���ڻ���
	class Window {
	protected:
		HWND								Hwnd; //���
		MSG									Message; //������Ϣ
		HINSTANCE							Hinstance; //ʵ�����
		
		ASNET::Page::Page*                  UsedPage; //ʹ�õ�Page
		std::vector<ASNET::Page::Page*>     Pages; //Page����
	protected:
		Graph::Direct3D::GraphDirect3D*     Graph; //ʹ�õ���Ⱦ�ӿ�
	protected:
		int									Width; //���
		int									Height; //�߶�
		LPCWSTR								IcoName; //Icoͼ���ļ���
		LPCWSTR								Title; //���ڱ���
	
		int									NowPage; //����ʹ�õ�Page�ڼ������������
	protected:
		float                               WidthScale; //�ʼ�Ĵ��ڿ�Ⱥ����ڴ��ڿ�ȵı�ֵ
		float                               HeightScale; //�ʼ�Ĵ��ڸ߶Ⱥ����ڴ��ڸ߶ȵı�ֵ
		int									MousePosx; //���λ��
		int									MousePosy; //���λ��
	private:
		//��ȡ�¼�
		ASNET::Event::EventType CoreGetEventArgs(
			int message, ASNET::Event::EventBase* &e);
		//�����¼�
		void CoreComputeEvents(int message);
	protected:
		//������ƶ���ʱ�򴥷�
		virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
		//����껬�ֹ�����ʱ�򴥷�
		virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
		//����갴�������ʱ�򴥷�
		virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
		//����갴�����µ�ʱ�򴥷�
		virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		//�����̰������µ�ʱ�򴥷�
		virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
		//�����̰��������ʱ�򴥷�
		virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		//�����ڴ�С�ı��ʱ�򴥷�
		virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
		//�ڴ��ڼ��ص�ʱ�򴥷���������Initllize����
		virtual void OnLoading(); //Load the Window,after window create
		//���õ������ʱ�򴥷�
		virtual void OnGetFocus(void* sender);
		//��ʧȥ�����ʱ�򴥷�
		virtual void OnLostFocus(void* sender);
		//������뿪���ڵ�ʱ�򴥷�
		virtual void OnMouseLeave(void* sender);
		//�ڹ��캯������ʹ��
		void		 Initalize();//use it before use any function
	protected:
		ASNET::Event::EventGetFocusHandlers         GetFocusHandler; //��ȡ�����¼�����
		ASNET::Event::EventLostFocusHandlers        LostFocusHandler; //ʧȥ�����¼�����
		ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler; //����ƶ��¼�����
		ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler; //��껬�ֹ����¼�����
		ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler; //��갴�������¼�����
		ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler; //��갴�������¼�����
		ASNET::Event::EventBoardClickHandlers		BoardUpHandler; //���̰��������¼�����
		ASNET::Event::EventBoardClickHandlers		BoardDownHandler; //���̰��������¼�����
		ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler; //���ڴ�С�¼�����
		ASNET::Event::EventMouseLeaveHandlers       MouseLeaveHandler; //����뿪�����¼�
		
	public:
		//Ĭ�Ϲ��캯��
		Window();
		//���һ��Page
		void AddPage(ASNET::Page::Page* page);
		//ɾ��һ��Page
		void DeletePage(int index);
		//��ʾĳ��Page
		void ShowPage(int index, void* any = nullptr);
		//��ת����һ��Page
		void NextPage(void* any = nullptr);
		//��������ʹ�õ�Page��ָ��
		auto NowUsedPage()->ASNET::Page::Page*;
		//���������ж��ٸ�Page�ڼ�������
		auto NowPageNum()->int;
		//����
		void Run();
		//��ʾ����
		void Show();
		//���ش���
		void Hide();
		//�ͷ���Դ
		void Release();


		//����ĳ��������Ϣ,true��ʾ����false��ʾ����
		bool GetKeyState(ASNET::Keycode keycode); //true is down ,false is up
		//�������λ��
		auto GetMousePosx()->int;
		//�������λ��
		auto GetMousePosy()->int;
		//���ش��ڿ��
		auto GetWidth()->int;
		//���ش��ڸ߶�
		auto GetHeight()->int;
	};
}


#include"ASNET.Window.Keycode.h"
#include"ASNET.Window.Event.h"
#include"ASNET.Window.Page.h"



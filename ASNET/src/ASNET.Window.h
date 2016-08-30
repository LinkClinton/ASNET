#pragma once
#include<vector>
#include<Windows.h>

#include"ASNET.Graph.h"
#include"ASNET.Graph.Direct3D.h"

#include"ASNET.Window.Keycode.h"
#include"ASNET.Window.Event.h"
#include"ASNET.Window.Page.h"

//�����࣬�򵥵���˵����֧�ִ�������
//Ȼ�������ݲ������д��������������Page��
//ͬ����ֻ��һ���������
//ֱ����Direct3DGraph������Graph����ô�ʹ���������Ҫ��ʹ�õ���ɫ����ʱ��ʹ�ú���SetShader

namespace ASNET {
	
	class Window {
	protected:
		HWND								Hwnd;
		MSG									Message;
		HINSTANCE							Hinstance;
		
		ASNET::Page::Page*                  UsedPage;
		std::vector<ASNET::Page::Page*>     Pages;
	protected:
		Graph::Direct3D::GraphDirect3D*     Graph;
	protected:
		int									Width;
		int									Height;
		LPCWSTR								IcoName;
		LPCWSTR								Title;
	
		int									NowPage;
	protected:
		int									MousePosx;
		int									MousePosy;
	private:
		ASNET::Event::EventType CoreGetEventArgs(
			int message, ASNET::Event::EventBase* &e);
		void CoreComputeEvents(int message);
	protected:
		virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
		virtual void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e);
		virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
		virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
		virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
		virtual void OnLoading(); //Load the Window,after window create

		void		 Initalize();//use it before use any function
	protected:
		ASNET::Event::EventMouseMoveHandlers		MouseMoveHandler;
		ASNET::Event::EventMouseWheelHandlers		MouseWheelHandler;
		ASNET::Event::EventMouseClickHandlers		MouseButtonUpHandler;
		ASNET::Event::EventMouseClickHandlers		MouseButtonDownHandler;
		ASNET::Event::EventBoardClickHandlers		BoardUpHandler;
		ASNET::Event::EventBoardClickHandlers		BoardDownHandler;
		ASNET::Event::EventSizeChangeHandlers		SizeChangeHandler;
	public:
		Window();
		void AddPage(ASNET::Page::Page* page);

		void DeletePage(int index);

		void ShowPage(int index, void* any = nullptr);

		void NextPage(void* any = nullptr);

		auto NowUsedPage()->ASNET::Page::Page*;

		auto NowPageNum()->int;

		void Run();

		void Show();

		void Hide();

		void Release();



		bool GetKeyState(ASNET::Keycode keycode); //true is down ,false is up

		auto GetMousePosx()->int;

		auto GetMousePosy()->int;
	};
}


#include"ASNET.Window.Keycode.h"
#include"ASNET.Window.Event.h"
#include"ASNET.Window.Page.h"



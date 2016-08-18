#pragma once
#include<vector>
#include<Windows.h>


#include"Window.Keycode.h"
#include"Window.Event.h"
#include"Window.Graph.h"
#include"Window.Page.h"

namespace ASNET {
	
	class Window {
	protected:
		HWND								Hwnd;
		MSG									Message;
		HINSTANCE							Hinstance;
		
		ASNET::Page::Page*                  UsedPage;
		std::vector<ASNET::Page::Page*>     Pages;
	private:

	protected:
		int									Width;
		int									Height;
		LPCWSTR								IcoName;
		LPCWSTR								Title;
	
		ASNET::Graph::Graph*                GraphRender;//this render for ui
		int									NowPage;
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

		void ShowPage(int index);

		void NextPage();

		auto NowUsedPage()->ASNET::Page::Page*;

		auto NowPageNum()->int;

		void Run();

		void Show();

		void Hide();

		void Release();
	};
}
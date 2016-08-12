#pragma once
#include<vector>
#include<Windows.h>


#include"Window.Keycode.h"
#include"Window.Event.h"
#include"Window.Graph.h"
#include"Window.Page.h"
namespace ASNET {


	class Window {
	private:
		HWND								Hwnd;
		int									Width;
		int									Height;
		HINSTANCE							Hinstance;
		ASNET::Graph::Graph                 GraphRender;
		std::vector<ASNET::Page::Page*>     Pages;
		int									NowPage;
	protected:
		virtual void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e);
		virtual void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e);
		virtual void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e);
		virtual void OnKeyDown(void* sender, ASNET::Event::EventBoardClick* e);
		virtual void OnKeyUp(void* sender, ASNET::Event::EventBoardClick* e);
		virtual void OnSizeChanged(void* sender, ASNET::Event::EventSizeChange* e);
		virtual void Initalize(); //Load the Window
	protected:
		ASNET::Event::EventMouseMoveHander		MouseMoveHander;
		ASNET::Event::EventMouseClickHander		MouseButtonUpHander;
		ASNET::Event::EventMouseClickHander		MouseButtonDownHander;
		ASNET::Event::EventBoardClickHander		BoardUpHander;
		ASNET::Event::EventBoardClickHander		BoardDownHander;
		ASNET::Event::EventSizeChangeHander		SizeChangeHander;
	public:
		void AddPage(ASNET::Page::Page* page);

		void NextPage();

		void ShowPage(ASNET::Page::Page* page);

		void Run();

		void Show();

		void Hide();
	};
}
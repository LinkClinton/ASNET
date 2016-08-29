#include "ASNET.Window.h"
#define DEBUG

#ifdef DEBUG
#include<iostream>
#endif // DEBUG


#include<windowsx.h>

namespace ASNET {

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

	static LRESULT CALLBACK DefaultWindowProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam) {
		switch (message)
		{
		case WM_DESTROY: {
			PostQuitMessage(0);
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}


	static HWND CreateWindows(int width, int height, LPCWSTR ico, LPCWSTR title) {
		HINSTANCE Hinstance = ::GetModuleHandle(NULL);
		WNDCLASS WindowClass;
		HWND Hwnd;

		WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc = DefaultWindowProc;
		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hInstance = Hinstance;
		WindowClass.hIcon = (HICON)LoadImageW(0, ico, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WindowClass.lpszMenuName = NULL;
		WindowClass.lpszClassName = title;

		RegisterClass(&WindowClass);

		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = width;
		rc.bottom = height;

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		Hwnd = CreateWindow(title, title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, Hinstance, nullptr);

		ShowWindow(Hwnd, SW_SHOWNORMAL);

		return Hwnd;
	}



	ASNET::Event::EventType Window::CoreGetEventArgs(
		int message,
		ASNET::Event::EventBase *& e) {
		if (message == WM_MBUTTONUP || message == WM_MBUTTONDOWN) {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			eventarg->button = ASNET::Event::MouseButton::Middle;
			eventarg->x = GET_X_LPARAM(Message.lParam);
			eventarg->y = GET_Y_LPARAM(Message.lParam);
			if (message == WM_MBUTTONDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseClick;
		}
		if (message == WM_LBUTTONUP || message == WM_LBUTTONDOWN) {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			eventarg->button = ASNET::Event::MouseButton::Left;
			eventarg->x = GET_X_LPARAM(Message.lParam);
			eventarg->y = GET_Y_LPARAM(Message.lParam);
			if (message == WM_LBUTTONDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseClick;
		}
		if (message == WM_RBUTTONUP || message == WM_RBUTTONDOWN) {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			eventarg->button = ASNET::Event::MouseButton::Right;
			eventarg->x = GET_X_LPARAM(Message.lParam);
			eventarg->y = GET_Y_LPARAM(Message.lParam);
			if (message == WM_RBUTTONDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseClick;
		}
		if (message == WM_MOUSEMOVE) {
			ASNET::Event::EventMouseMove* eventarg = new ASNET::Event::EventMouseMove();
			eventarg->x = GET_X_LPARAM(Message.lParam);
			eventarg->y = GET_Y_LPARAM(Message.lParam);
			e = eventarg;
			return ASNET::Event::EventType::EventMouseMove;
		}
		if (message == WM_MOUSEWHEEL) {
			ASNET::Event::EventMouseWheel* eventarg = new ASNET::Event::EventMouseWheel();
			eventarg->x = GET_X_LPARAM(Message.lParam);
			eventarg->y = GET_Y_LPARAM(Message.lParam);
			eventarg->offest = GET_WHEEL_DELTA_WPARAM(Message.wParam);
			e = eventarg;
			return ASNET::Event::EventType::EventMouseWheel;
		}
		if (message == WM_KEYDOWN || WM_KEYUP) {
			ASNET::Event::EventBoardClick* eventarg = new ASNET::Event::EventBoardClick();
			eventarg->keycode = (ASNET::Keycode)Message.wParam;
			if (message == WM_KEYDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventBoardClick;
		}
		return ASNET::Event::EventType::EventOther;
	}

	void Window::CoreComputeEvents(int message){
		ASNET::Event::EventBase* BaseEvent = NULL;
		ASNET::Event::EventType type = CoreGetEventArgs(message, BaseEvent);
		//std::cout << (int)type << std::endl;
		switch (type)
		{
		case ASNET::Event::EventType::EventOther: {
			break;
		}
		case ASNET::Event::EventType::EventMouseMove: {
			ASNET::Event::EventMouseMove* e = (ASNET::Event::EventMouseMove*)BaseEvent;
			OnMouseMove(this, e);
			ASNET::Event::DoEventHandlers(
				MouseMoveHandler, this, e);
			if (UsedPage) {
				UsedPage->OnMouseMove(this, e);
				ASNET::Event::DoEventHandlers(
					UsedPage->MouseMoveHandler, UsedPage, e);
				UsedPage->OnControlMouseMove(this, e);
			}
			break;
		}
		case ASNET::Event::EventType::EventMouseClick: {
			ASNET::Event::EventMouseClick* e = (ASNET::Event::EventMouseClick*)BaseEvent;
			if (e->IsDown) {
				OnMouseDown(this, e);
				ASNET::Event::DoEventHandlers(
					MouseButtonDownHandler, this, e);
				if (UsedPage) {
					UsedPage->OnMouseDown(this, e);
					ASNET::Event::DoEventHandlers(
						UsedPage->MouseButtonDownHandler, UsedPage, e);
					UsedPage->OnControlMouseDown(this, e);
				}
			}
			else {
				OnMouseUp(this, e);
				ASNET::Event::DoEventHandlers(
					MouseButtonUpHandler, this, e);
				if (UsedPage) {
					UsedPage->OnMouseUp(this, e);
					ASNET::Event::DoEventHandlers(
						UsedPage->MouseButtonUpHandler, UsedPage, e);
					UsedPage->OnControlMouseUp(this, e);
				}
			}
			break;
		}
		case ASNET::Event::EventType::EventMouseWheel: {
			ASNET::Event::EventMouseWheel* e = (ASNET::Event::EventMouseWheel*)BaseEvent;
			OnMouseWheel(this, e);
			ASNET::Event::DoEventHandlers(MouseWheelHandler, this, e);
			if (UsedPage) {
				UsedPage->OnMouseWheel(this, e);
				ASNET::Event::DoEventHandlers(
					UsedPage->MouseWheelHandler, UsedPage, e);
				UsedPage->OnControlMouseWheel(this, e);
			}
			break;
		}
		case ASNET::Event::EventType::EventBoardClick: {
			ASNET::Event::EventBoardClick* e = (ASNET::Event::EventBoardClick*)BaseEvent;
			if (e->IsDown) {
				OnKeyDown(this, e);
				ASNET::Event::DoEventHandlers(BoardDownHandler, this, e);
				if (UsedPage) {
					UsedPage->OnKeyDown(this, e);
					ASNET::Event::DoEventHandlers(
						UsedPage->BoardDownHandler, UsedPage, e);
					UsedPage->OnControlKeyDown(this, e);
				}
			}
			else {
				OnKeyUp(this, e);
				ASNET::Event::DoEventHandlers(BoardUpHandler, this, e);
				if (UsedPage) {
					UsedPage->OnKeyUp(this, e);
					ASNET::Event::DoEventHandlers(
						UsedPage->BoardUpHandler, UsedPage, e);
					UsedPage->OnControlKeyUp(this, e);
				}
			}
			break;
		}
		default:
			break;
		}
		if (BaseEvent)
			delete BaseEvent;
	}

	void ASNET::Window::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
	{
	}

	void ASNET::Window::OnMouseWheel(void * sender, ASNET::Event::EventMouseWheel* e)
	{
	}

	void ASNET::Window::OnMouseUp(void * sender, ASNET::Event::EventMouseClick * e)
	{
	}

	void ASNET::Window::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e)
	{
	}

	void ASNET::Window::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
	{
	}

	void ASNET::Window::OnKeyUp(void * sender, ASNET::Event::EventBoardClick * e)
	{
	}

	void ASNET::Window::OnSizeChanged(void * sender, ASNET::Event::EventSizeChange * e)
	{
	}

	void ASNET::Window::OnLoading()
	{
	}

	void Window::Initalize(){
		Hwnd = CreateWindows(Width, Height, IcoName, Title);
		Graph = new ASNET::Graph::Direct3D::GraphDirect3D(Hwnd);
		OnLoading();
		
	}

	




	ASNET::Window::Window(){
		Hwnd = Hwnd;
		Message = { 0 };
		Hinstance = NULL;
		UsedPage = NULL;
		NowPage = 0;
		Width = 0;
		Height = 0;
		IcoName = NULL;
		Title = NULL;
		Graph = NULL;
	}

	void ASNET::Window::AddPage(ASNET::Page::Page * page){
		Pages.push_back(page);
	}

	void Window::DeletePage(int index)
	{
		Pages.erase(Pages.begin() + index);
	}

	void ASNET::Window::NextPage(void* any){
		NowPage++;
		UsedPage = Pages[NowPage];
		UsedPage->ParentGraph = Graph;
		UsedPage->OnLoading(this, any);
		
	}

	void Window::ShowPage(int index, void* any) {
		UsedPage = Pages[index];
		UsedPage->ParentGraph = Graph;
		UsedPage->OnLoading(this, any);

	}

	auto Window::NowUsedPage() -> ASNET::Page::Page *
	{
		return UsedPage;
	}

	auto Window::NowPageNum() -> int
	{
		return Pages.size();
	}

	void ASNET::Window::Run(){
		Message = { 0 };
		Message.hwnd = Hwnd;
		while (Message.message != WM_QUIT) {
			if (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE)) {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
				CoreComputeEvents(Message.message);
			}
			if (UsedPage) {
				UsedPage->OnDraw(this, Graph);
				UsedPage->OnControlDraw(this, Graph);
				Graph->Present();
			}
		}
	}

	void ASNET::Window::Show()
	{
		ShowWindow(Hwnd, SW_SHOW);
	}

	void ASNET::Window::Hide()
	{
		ShowWindow(Hwnd, SW_HIDE); 
	}

	void Window::Release()
	{
		int size = Pages.size();
		for (int i = 0; i < size; i++)
			if (Pages[i])
				delete Pages[i];
		Pages.clear();
		delete Graph;
	}

}
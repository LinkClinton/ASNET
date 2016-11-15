#include "ASNET.Window.h"

#ifdef _DEBUG
#include<iostream>
#endif // DEBUG


#include<windowsx.h>


namespace ASNET {

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

	static bool SizeChanged = false;
	static int  BackEndWidth = 0;
	static int  BACKEndHeight = 0;

	static LRESULT CALLBACK DefaultWindowProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam) {
		switch (message)
		{
		case WM_SIZE: {
			SizeChanged = true;
			BackEndWidth = LOWORD(lParam);
			BACKEndHeight = HIWORD(lParam);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
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

		FLOAT dpiX;
		FLOAT dpiY;

		ID2D1Factory* g_factory;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, (ID2D1Factory**)&g_factory);
		g_factory->ReloadSystemMetrics();
		g_factory->GetDesktopDpi(&dpiX, &dpiY);

		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = (LONG)ceil(width*dpiX / 96.f);
		rc.bottom = (LONG)ceil(height*dpiY / 96.f);

		

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		Hwnd = CreateWindow(title, title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left,
			rc.bottom - rc.top, nullptr, nullptr, Hinstance, nullptr);

		ShowWindow(Hwnd, SW_SHOWNORMAL);

		g_factory->Release();

		return Hwnd;
	}


	//没有消息的话参数是-1
	ASNET::Event::EventType Window::CoreGetEventArgs(
		int message,
		ASNET::Event::EventBase *& e) {
		if (message == WM_MBUTTONUP || message == WM_MBUTTONDOWN) {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			eventarg->button = ASNET::Event::MouseButton::Middle;
			MousePosx = (int)(GET_X_LPARAM(Message.lParam)*WidthScale);
			MousePosy = (int)(GET_Y_LPARAM(Message.lParam)*HeightScale);
			eventarg->x = MousePosx;
			eventarg->y = MousePosy;
			if (message == WM_MBUTTONDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseClick;
		}
		if (message == WM_LBUTTONUP || message == WM_LBUTTONDOWN) {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			eventarg->button = ASNET::Event::MouseButton::Left;
			MousePosx = (int)(GET_X_LPARAM(Message.lParam)*WidthScale);
			MousePosy = (int)(GET_Y_LPARAM(Message.lParam)*HeightScale);
			eventarg->x = MousePosx;
			eventarg->y = MousePosy;
			if (message == WM_LBUTTONDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseClick;
		}
		if (message == WM_RBUTTONUP || message == WM_RBUTTONDOWN) {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			eventarg->button = ASNET::Event::MouseButton::Right;
			MousePosx = (int)(GET_X_LPARAM(Message.lParam)*WidthScale);
			MousePosy = (int)(GET_Y_LPARAM(Message.lParam)*HeightScale);
			eventarg->x = MousePosx;
			eventarg->y = MousePosy;
			if (message == WM_RBUTTONDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseClick;
		}
		if (message == WM_MOUSEMOVE) {
			ASNET::Event::EventMouseMove* eventarg = new ASNET::Event::EventMouseMove();
			MousePosx = (int)(GET_X_LPARAM(Message.lParam)*WidthScale);
			MousePosy = (int)(GET_Y_LPARAM(Message.lParam)*HeightScale);
			eventarg->x = MousePosx;
			eventarg->y = MousePosy;
			e = eventarg;
			return ASNET::Event::EventType::EventMouseMove;
		}
		if (message == WM_MOUSEWHEEL) {
			ASNET::Event::EventMouseWheel* eventarg = new ASNET::Event::EventMouseWheel();
			MousePosx = (int)(GET_X_LPARAM(Message.lParam)*WidthScale);
			MousePosy = (int)(GET_Y_LPARAM(Message.lParam)*HeightScale);
			eventarg->x = MousePosx;
			eventarg->y = MousePosy;
			eventarg->offest = GET_WHEEL_DELTA_WPARAM(Message.wParam);
			e = eventarg;
			return ASNET::Event::EventType::EventMouseWheel;
		}
		if (message == WM_KEYDOWN || message == WM_KEYUP) {
			ASNET::Event::EventBoardClick* eventarg = new ASNET::Event::EventBoardClick();
			eventarg->keycode = (ASNET::Keycode)Message.wParam;
			if (message == WM_KEYDOWN)
				eventarg->IsDown = true;
			else eventarg->IsDown = false;
			e = eventarg;
			return ASNET::Event::EventType::EventBoardClick;
		}
		if (message == WM_SETFOCUS) {
			return ASNET::Event::EventType::EventGetFocus;
		}
		if (message == WM_KILLFOCUS) {
			return ASNET::Event::EventType::EventLostFocus;
		}
		if (SizeChanged) {
			SizeChanged = false;
			ASNET::Event::EventSizeChange* eventarg = new ASNET::Event::EventSizeChange();
			eventarg->last_height = Height;
			eventarg->last_width = Width;
			eventarg->now_width = BackEndWidth;
			eventarg->now_height = BACKEndHeight;
			WidthScale *= (float)Width / (float)BackEndWidth;	
			HeightScale *= (float)Height / (float)BACKEndHeight;
			e = eventarg;
			return ASNET::Event::EventType::EventSizeChanged;
		}
		//后面的处理消息的语句代表着这些语句的触发在触发无用消息的时候才会考虑触发
		//鼠标离开的事件
		{
			POINT MousePos;
			GetCursorPos(&MousePos);
			MousePos.x = (long)(MousePos.x*WidthScale);
			MousePos.y = (long)(MousePos.y*HeightScale);
			if (MousePos.x < 0 || MousePos.x > Width || MousePos.y < 0 || MousePos.y > Height)
				return ASNET::Event::EventType::EventMouseLeave;
		}
		return ASNET::Event::EventType::EventOther;
	}

	void Window::CoreComputeEvents(int message){
		ASNET::Event::EventBase* BaseEvent = NULL;
		ASNET::Event::EventType type = CoreGetEventArgs(message, BaseEvent);
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
		case ASNET::Event::EventType::EventGetFocus: {
			OnGetFocus(this);
			ASNET::Event::DoEventHandlers(GetFocusHandler, this);
			break;
		}
		case ASNET::Event::EventType::EventLostFocus: {
			OnLostFocus(this);
			ASNET::Event::DoEventHandlers(LostFocusHandler, this);
			break;
		}
		case ASNET::Event::EventType::EventMouseLeave: {
			OnMouseLeave(this);
			ASNET::Event::DoEventHandlers(MouseLeaveHandler, this);
			if (UsedPage) {
				UsedPage->OnMouseLeave(this);
				ASNET::Event::DoEventHandlers(UsedPage->MouseLeaveHandler, UsedPage);
			}
			break;
		}
		case ASNET::Event::EventType::EventSizeChanged: {
			ASNET::Event::EventSizeChange* e = (ASNET::Event::EventSizeChange*)BaseEvent;
			Width = e->now_width;
			Height = e->now_height;
			
			OnSizeChanged(this, e);
			ASNET::Event::DoEventHandlers(SizeChangeHandler, this, e);
			
			if (UsedPage) {
				UsedPage->OnSizeChanged(this, e);
				ASNET::Event::DoEventHandlers(UsedPage->SizeChangeHandler, UsedPage, e);
				
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

	void Window::OnGetFocus(void * sender)
	{
	}

	void Window::OnLostFocus(void * sender)
	{
	}


	void Window::OnMouseLeave(void * sender)
	{
	}	
	void Window::Initalize(){
		Hwnd = CreateWindows(Width, Height, IcoName, Title);
		WidthScale = 1.0f;
		HeightScale = 1.0f;
		Graph = new ASNET::Graph::Direct3D::GraphDirect3D(Hwnd);
		OnLoading();
		
	}

	




	ASNET::Window::Window(){
		Hwnd = Hwnd;
		Message = { 0 };
		Hinstance = nullptr;
		UsedPage = nullptr;
		NowPage = 0;
		Width = 0;
		Height = 0;
		IcoName = nullptr;
		Title = nullptr;
		Graph = nullptr;
	}

	void ASNET::Window::AddPage(ASNET::Page::Page * page){
		Pages.push_back(page);
		page->Parent = (void*)this;
		page->ParentGraph = Graph;
		page->OnInitalize(this);
	}

	void Window::DeletePage(int index)
	{
		Pages.erase(Pages.begin() + index);
	}

	void ASNET::Window::NextPage(void* any){
		ShowPage(++NowPage, any);
	}

	void Window::ShowPage(int index, void* any) {
		if (UsedPage) {
			UsedPage->OnStoping();
			UsedPage->OnUnLoading(this);
		}
		UsedPage = Pages[index];
		NowPage = index;
		UsedPage->ParentGraph = Graph;
		UsedPage->Parent = (void*)this;
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
			else { CoreComputeEvents(NO_MESSAGE); }
			if (UsedPage) {
				Graph->g_devicecontext2d->BeginDraw();
				Graph->Clear();
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

	bool Window::GetKeyState(ASNET::Keycode keycode){ 
		if (keycode == Keycode::CapsLock || 
			keycode == Keycode::NumLock || 
			keycode == Keycode::ScrollLock) {
			short state = ::GetKeyState((int)keycode);
			if (state == 1) return true;
			return false;
		}
		return KEYDOWN((int)keycode);
	}

	auto Window::GetMousePosx() -> int{
		return MousePosx;
	}

	auto Window::GetMousePosy() -> int{
		return MousePosy;
	}

	auto Window::GetWidth() -> int{
		return Width;
	}

	auto Window::GetHeight() -> int{
		return Height;
	}

}
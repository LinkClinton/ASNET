#include "Window.h"
namespace ASNET {

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
	 




	void Window::CoreGetEventArgs(
		ASNET::Event::EventType type,
		ASNET::Event::EventBase *& e) {
		switch (type)
		{
		case ASNET::Event::EventType::EventOther: {
			e = NULL;
			break;
		}
		case ASNET::Event::EventType::EventMouseMove: {
			ASNET::Event::EventMouseMove* eventarg = new ASNET::Event::EventMouseMove();
			//put your code
			e = eventarg;
			break;
		}
		case ASNET::Event::EventType::EventMouseClick: {
			ASNET::Event::EventMouseClick* eventarg = new ASNET::Event::EventMouseClick();
			//put your code
			e = eventarg;
			break;
		}
		case ASNET::Event::EventType::EventMouseWheel: {
			ASNET::Event::EventMouseWheel* eventarg = new ASNET::Event::EventMouseWheel();
			//put your code
			e = eventarg;
			break;
		}
		case ASNET::Event::EventType::EventBoardClick: {
			ASNET::Event::EventBoardClick* eventarg = new ASNET::Event::EventBoardClick();
			//put your code
			e = eventarg;
			break;
		}
		default:
			e = NULL;
			break;
		}
	}

	void Window::CoreComputeEvents(ASNET::Event::EventType type){
		ASNET::Event::EventBase* BaseEvent = NULL;
		CoreGetEventArgs(type, BaseEvent);
		switch (type)
		{
		case ASNET::Event::EventType::EventOther: {
			break;
		}
		case ASNET::Event::EventType::EventMouseMove: {
			ASNET::Event::EventMouseMove* e = (ASNET::Event::EventMouseMove*)BaseEvent;
			OnMouseMove(this, e);
			if (UsedPage)
				UsedPage->OnMouseMove(this, e),
				ASNET::Event::EventHander::DoEventHanders(
					UsedPage->MouseMoveHander, this, e);
			break;
		}
		case ASNET::Event::EventType::EventMouseClick: {
			ASNET::Event::EventMouseClick* e = (ASNET::Event::EventMouseClick*)BaseEvent;
			if (e->IsDown) {
				OnMouseDown(this, e);
				if (UsedPage)
					UsedPage->OnMouseDown(this, e),
					ASNET::Event::EventHander::DoEventHanders(
						UsedPage->MouseButtonDownHander, this, e);
			}
			else {
				OnMouseUp(this, e);
				if (UsedPage)
					UsedPage->OnMouseUp(this, e);
				ASNET::Event::EventHander::DoEventHanders(
					UsedPage->MouseButtonUpHander, this, e
				);
			}
			break;
		}
		case ASNET::Event::EventType::EventMouseWheel: {
			ASNET::Event::EventMouseWheel* e = (ASNET::Event::EventMouseWheel*)BaseEvent;
			OnMouseWheel(this, e);
			if (UsedPage)
				UsedPage->OnMouseWheel(this, e),
				ASNET::Event::EventHander::DoEventHanders(
					UsedPage->MouseWheelHander, this, e
				);
			break;
		}
		case ASNET::Event::EventType::EventBoardClick: {
			ASNET::Event::EventBoardClick* e = (ASNET::Event::EventBoardClick*)BaseEvent;
			if (e->IsDown) {
				OnKeyDown(this, e);
				if (UsedPage)
					UsedPage->OnKeyDown(this, e),
					ASNET::Event::EventHander::DoEventHanders(
						UsedPage->BoardDownHander, this, e
					);
			}
			else {
				OnKeyUp(this, e);
				if (UsedPage)
					UsedPage->OnKeyUp(this, e),
					ASNET::Event::EventHander::DoEventHanders(
						UsedPage->BoardUpHander, this, e
					);
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





	void ASNET::Window::AddPage(ASNET::Page::Page * page){
		Pages.push_back(page);
	}

	void ASNET::Window::NextPage(){
		NowPage++;
		UsedPage = Pages[NowPage];
	}

	void ASNET::Window::ShowPage(ASNET::Page::Page * page){
		UsedPage = page;
	}

	void Window::ShowPage(int index){
		UsedPage = Pages[index];
	}

	void ASNET::Window::Run(){
		Message = { 0 };
		Message.hwnd = Hwnd;
		while (Message.message != WM_QUIT) {
			if (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE)) {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
				CoreComputeEvents(ASNET::Event::ToEventType(Message.message));
			}
			if (UsedPage) {
				UsedPage->OnDraw(this, &GraphRender);
				ASNET::Event::EventHander::DoEventHanders(
					UsedPage->GraphDrawHander, this, &GraphRender);
			}
		}
	}

	void ASNET::Window::Show()
	{
	}

	void ASNET::Window::Hide()
	{
	}

}
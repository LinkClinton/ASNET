#include"ASNET.Window.Page.h"


namespace ASNET {
	namespace Page {
		

		void ASNET::Page::Page::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
		{	
		}

		void ASNET::Page::Page::OnMouseWheel(void * sender, ASNET::Event::EventMouseWheel* e) 
		{
		}

		void ASNET::Page::Page::OnMouseUp(void * sender, ASNET::Event::EventMouseClick * e)
		{
		}

		void ASNET::Page::Page::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e)
		{
		}

		void ASNET::Page::Page::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
		{
		}

		void ASNET::Page::Page::OnKeyUp(void * sender, ASNET::Event::EventBoardClick * e)
		{
		}

		void ASNET::Page::Page::OnSizeChanged(void * sender, ASNET::Event::EventSizeChange * e)
		{
		}

		void Page::OnMouseLeave(void * sender)
		{
		}

		void ASNET::Page::Page::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * render)
		{
		}

		void ASNET::Page::Page::OnLoading(void * sender, void * any)
		{
		}

		ASNET::Page::Page::Page()
		{
		}

		void ASNET::Page::Page::RegisterControl(ASNET::Control::Control * control){
			Controls.push_back(control);
			control->ParentGraph = ParentGraph;
		}

		void ASNET::Page::Page::UnRegisterControl(ASNET::Control::Control * control){
			for (UINT i = 0; i < Controls.size(); i++)
				if (Controls[i] == control) {
					Controls.erase(Controls.begin() + i);
					break;
				}
		}

		void Page::SetFocus(ASNET::Control::Control * control){
			if (ControlsFocus)
				ControlsFocus->IsFocus = false,
				ControlsFocus->OnLostFocus(ControlsFocus),
				ASNET::Event::DoEventHandlers(ControlsFocus->LostFocusHandler, ControlsFocus);

			ControlsFocus = control;
			ControlsFocus->IsFocus = true;

			ControlsFocus->OnGetFocus(ControlsFocus);
			ASNET::Event::DoEventHandlers(ControlsFocus->GetFocusHandler, ControlsFocus);

		}

		
		//==要判断事件是否引发，只有在这个控件的范围内才会
		static bool PosInRect(int x, int y, ASNET::Graph::Rect rect) {
			if (x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom) return true;
			return false;
		}
		

		void Page::OnControlMouseMove(void * sender, ASNET::Event::EventMouseMove * e){
			for (UINT i = 0;i<Controls.size();i++)
				if (Controls[i]->IsActive && PosInRect(e->x,e->y,*Controls[i])) {
					Controls[i]->MouseIn = true;
					Controls[i]->OnMouseMove(sender, e);
					ASNET::Event::DoEventHandlers(Controls[i]->MouseMoveHandler, &Controls[i], e);
				}
				else { 
					if (Controls[i]->MouseIn)
						Controls[i]->InitalizeLeaveFrame();
					Controls[i]->MouseIn = false; 
				}
		}

		void Page::OnControlMouseWheel(void * sender, ASNET::Event::EventMouseWheel * e){
			for (UINT i = 0; i < Controls.size(); i++) 
				if (Controls[i]->IsActive && PosInRect(e->x, e->y, *Controls[i])) {
					Controls[i]->OnMouseWheel(sender, e);
					ASNET::Event::DoEventHandlers(Controls[i]->MouseWheelHandler, &Controls[i], e);
				}
		}

		void Page::OnControlMouseUp(void * sender, ASNET::Event::EventMouseClick * e){
			for (UINT i = 0; i < Controls.size(); i++)
				if (Controls[i]->IsActive && PosInRect(e->x, e->y, *Controls[i])) {
					Controls[i]->OnMouseUp(sender, e);
					ASNET::Event::DoEventHandlers(Controls[i]->MouseButtonUpHandler, &Controls[i], e);
				}
		}

		void Page::OnControlMouseDown(void * sender, ASNET::Event::EventMouseClick * e){
			for (UINT i = 0; i < Controls.size(); i++)
				if (Controls[i]->IsActive && PosInRect(e->x, e->y, *Controls[i])) {
					
					SetFocus(Controls[i]);

					Controls[i]->OnMouseDown(sender, e);
					ASNET::Event::DoEventHandlers(Controls[i]->MouseButtonDownHandler, &Controls[i], e);
				}
		}

		void Page::OnControlKeyDown(void * sender, ASNET::Event::EventBoardClick * e){
			for (UINT i = 0; i < Controls.size(); i++)
				if (Controls[i]->IsActive && Controls[i]->IsFocus) {
					Controls[i]->OnKeyDown(sender, e);
					ASNET::Event::DoEventHandlers(Controls[i]->BoardDownHandler, &Controls[i], e);
				}
		}

		void Page::OnControlKeyUp(void * sender, ASNET::Event::EventBoardClick * e){
			for (UINT i = 0; i < Controls.size(); i++)
				if (Controls[i]->IsActive && Controls[i]->IsFocus) {
					Controls[i]->OnKeyUp(sender, e);
					ASNET::Event::DoEventHandlers(Controls[i]->BoardUpHandler, &Controls[i], e);
				}
		}

		

		void Page::OnControlDraw(void * sender, 
			ASNET::Graph::Direct3D::GraphDirect3D * render){
			for (UINT i = 0; i < Controls.size(); i++)
				if (Controls[i]->IsActive && Controls[i]->Visibility) 
					Controls[i]->OnDraw(sender, render);
		}

		

	}
}
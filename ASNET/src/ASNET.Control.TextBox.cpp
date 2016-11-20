#include "ASNET.Control.TextBox.h"

#include"ASNET.Window.h"
const float edge = 3.f;

void ASNET::Control::TextBox::OnDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	ParentGraph->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom), D2D1::ColorF::Black);

	if (IsFocus) {
		g_text->OnDraw(D2D1::Point2F(Left + edge, Top + edge));
	}
}

void ASNET::Control::TextBox::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
{
	wchar_t input = ASNET::Control::Text::KeycodeToWideChar(sender, e->keycode);
	if (input != '\0') {
		g_text->Insert(input);
	}
	if (e->keycode == ASNET::Keycode::Left) 
		g_text->CursorLeft();
	if (e->keycode == ASNET::Keycode::Right)
		g_text->CuesorRight();
	if (e->keycode == ASNET::Keycode::Up)
		g_text->CursorUp();
	if (e->keycode == ASNET::Keycode::Down)
		g_text->CursorDown();
	if (e->keycode == ASNET::Keycode::Backspace)
		g_text->Delete();
	
}

ASNET::Control::TextBox::TextBox(ASNET::Graph::Graph * graph,
	float left, float right, float top, float bottom, 
	wchar_t * name,ASNET::Graph::Font* fontface)
{
	ParentGraph = graph;

	Left = left;
	Right = right;
	Top = top;
	Bottom = bottom;

	Name = name;

	g_text = new Text(graph, L"", D2D1::SizeF(right - left - edge * 2, bottom - top - edge * 2), 
		fontface);
	g_text->CursorShow();

	
}

#include "ASNET.Control.Button.h"



void ASNET::Control::Button::SimpleDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * render){

	if (IsKeyDown || IsMouseDown)
		render->DrawWord(Text,
			D2D1::RectF(Left, Top, Right, Bottom),
			TextFont, Color(TextColor, TextColor.a*ControlColorAlpha), Horizontal, Vertical);
	else
		render->DrawWord(Text,
			D2D1::RectF(Left, Top, Right, Bottom),
			TextFont, TextColor, Horizontal, Vertical);

}

void ASNET::Control::Button::OnDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * render){
	if (!Visibility) return;

	OnStdDraw(sender, render);

	switch (Style)
	{
	case ASNET::Control::ButtonStyle::Simple:
		SimpleDraw(sender, render);
		break;
	default:
		break;
	}
	
}

void ASNET::Control::Button::OnMouseUp(void * sender, ASNET::Event::EventMouseClick * e)
{
	IsMouseDown = false;
}

void ASNET::Control::Button::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e)
{
	IsMouseDown = true;
}

void ASNET::Control::Button::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
{
	if (e->keycode == ASNET::Keycode::Return && e->IsDown) {
		IsKeyDown = true;
	}

}

void ASNET::Control::Button::OnKeyUp(void * sender, ASNET::Event::EventBoardClick * e)
{
	if (e->keycode == ASNET::Keycode::Return && !e->IsDown) {
		IsKeyDown = false;
	}
}

void ASNET::Control::Button::OnStoping()
{
	IsKeyDown = false;
	IsMouseDown = false;
	MouseIn = false;
}

ASNET::Control::Button::Button(
	ASNET::Graph::Graph * graph,
	float left, float right,
	float top, float bottom,
	wchar_t * name, wchar_t * text,
	ASNET::Graph::Font* font,
	ASNET::Control::ButtonStyle style,
	ASNET::Graph::TextAlign horizontal,
	ASNET::Graph::TextAlign vertical)
{
	ParentGraph = graph;

	Left = left;
	Right = right;
	Top = top;
	Bottom = bottom;

	Name = name;
	Text = text;

	Horizontal = horizontal;
	Vertical = vertical;

	BackColor = ASNET::Graph::Color(1, 1, 1, 0);
	TextColor = ASNET::Graph::Color::Black;

	BackImage = nullptr;

	Selectibility = true;

	Visibility = true;

	Style = style;

	SelectBackColor = ControlBackGroundColor;

	IsKeyDown = false;
	IsMouseDown = false;

	TextFont = font;
}

ASNET::Control::Button::~Button(){
	
}

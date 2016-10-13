#include "ASNET.Control.Label.h"

void ASNET::Control::Label::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * render){
	if (!Visibility) return; 

	OnStdDraw(sender, render);

	render->DrawWord(Text,
		D2D1::RectF(Left, Top, Right, Bottom),
		TextFont, TextColor, Horizontal, Vertical);
		
}

void ASNET::Control::Label::OnStoping()
{
	MouseIn = false;
}




ASNET::Control::Label::Label(
	ASNET::Graph::Graph * graph,
	float left, float right, float top,
	float bottom, wchar_t * name, wchar_t * text, ASNET::Graph::Font* font,
	ASNET::Graph::TextAlign horizontal, ASNET::Graph::TextAlign vertical) {
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
	SelectBackColor = ControlBackGroundColor;
	TextColor = ASNET::Graph::Color::Black;

	BackImage = nullptr;

	Selectibility = true;

	Visibility = true;

	TextFont = font;

}

ASNET::Control::Label::~Label(){
	
}




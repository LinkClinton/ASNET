#include "ASNET.Control.Label.h"

void ASNET::Control::Label::OnDraw(void * sender, ASNET::Graph::Graph * graph){
	if (!IsShow) return; 
	graph->DrawRectangle(
		D2D1::RectF(Left, Top, Right, Bottom),
		ASNET::Graph::Color(0, 0, 0, 0), 0.0f, true,
		BackColor
	);

	graph->DrawWord(Text,
		D2D1::RectF(Left, Top, Right, Bottom),
		TextFont, TextColor, Horizontal, Vertical);
		
}




ASNET::Control::Label::Label(
	ASNET::Graph::Graph * graph,
	float left, float right, float top, float bottom,
	wchar_t * name, wchar_t * text,wchar_t* fontface,float fontsize,
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
	TextColor = ASNET::Graph::Color::Black;

	ParentGraph->LoadFont(TextFont, fontface, fontsize);

}

ASNET::Control::Label::~Label(){
	delete TextFont;
}

void ASNET::Control::Label::reset(wchar_t * fontface, 
	float fontsize){
	
	TextFont->reset(fontface, fontsize);

}


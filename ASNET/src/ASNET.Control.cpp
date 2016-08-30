#include "ASNET.Control.h"

ASNET::Control::Color::Color(){
	r = 0;
	g = 0;
	b = 0;
	a = 1;
}

ASNET::Control::Color::Color(ASNET::Graph::Color color){
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

ASNET::Control::Color::Color(ASNET::Graph::Color::Enum color){
	ASNET::Graph::Color _color = color;
	r = _color.r;
	g = _color.g;
	b = _color.b;
	a = _color.a;
}

ASNET::Control::Color::Color(float _r, float _g, float _b, float _a){
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

ASNET::Control::Color::operator ASNET::Graph::Color(){
	return ASNET::Graph::Color(r, g, b, a);
}

void ASNET::Control::Control::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
{
}

void ASNET::Control::Control::OnMouseWheel(void * sender, ASNET::Event::EventMouseWheel * e)
{
}

void ASNET::Control::Control::OnMouseUp(void * sender, ASNET::Event::EventMouseClick * e)
{
}

void ASNET::Control::Control::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e)
{
}

void ASNET::Control::Control::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
{
}

void ASNET::Control::Control::OnKeyUp(void * sender, ASNET::Event::EventBoardClick * e)
{
}

void ASNET::Control::Control::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * render)
{
}



ASNET::Control::Control::Control(){
	IsActive = true;
	IsFocus = false;
	IsShow = true;
	MouseIn = false;
}

ASNET::Control::Control::operator ASNET::Graph::Rect(){
	return D2D1::RectF(Left, Top, Right, Bottom);
}

void ASNET::Control::Control::Show(){
	IsShow = true;
}

void ASNET::Control::Control::Hide(){
	IsShow = false;
}

void ASNET::Control::Control::GetFocus(){
	IsFocus = true;
}

void ASNET::Control::Control::LostFocus(){
	IsFocus = false;
}

void ASNET::Control::Control::Active(){
	IsActive = true;
}

void ASNET::Control::Control::UnActive(){
	IsActive = false;
}

#include "ASNET.Control.h"

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG


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

ASNET::Control::Color::Color(ASNET::Graph::Color color, float _a) {
	r = color.r;
	g = color.g;
	b = color.b;
	a = _a;
}

ASNET::Control::Color::operator ASNET::Graph::Color(){
	return ASNET::Graph::Color(r, g, b, a);
}

ASNET::Control::Color ASNET::Control::Color::operator-(ASNET::Control::Color color)
{
	Color out;
	out.r = r - color.r;
	out.g = g - color.g;
	out.b = b - color.b;
	out.a = a - color.a;
	return out;
}

ASNET::Control::Color ASNET::Control::Color::operator+(ASNET::Control::Color color)
{
	Color out;
	out.r = r + color.r;
	out.g = g + color.g;
	out.b = b + color.b;
	out.a = a + color.a;
	return out;
}

ASNET::Control::Color ASNET::Control::Color::operator*(float scale)
{
	Color out;
	out.r = r*scale;
	out.g = g*scale;
	out.b = b*scale;
	out.a = a*scale;
	return out;
}

void ASNET::Control::Control::StartLeaveAnimation(){
	if (!Selectibility) return;
	LeaveAnimation.Start();
}

void ASNET::Control::Control::OnLeaveAnimationDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * render){

	KeyFrame keyframe = LeaveAnimation.GetKeyFrame(); 
	render->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom),
		Color(0, 0, 0, 0), 1.0f, true, keyframe.BackGroundColor);

}



void ASNET::Control::Control::OnStdDraw(void * sender, 
	ASNET::Graph::Direct3D::GraphDirect3D * render){

	if (!BackImage) {
		if (!LeaveAnimation.End())
			OnLeaveAnimationDraw(sender, render);
		else {
			if (Selectibility && MouseIn)
				render->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom),
					Color(0, 0, 0, 0), 1.0f, true, SelectBackColor);
			else
				render->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom),
					Color(0, 0, 0, 0), 1.0f, true, BackColor);
		}
	}
	else
		render->DrawImage(BackImage,
			D2D1::RectF(Left, Top, Right, Bottom));

	LeaveAnimation.Pass(render->RenderTime());
}

void ASNET::Control::Control::InitalizeAnimation()
{
	//leave animation
	{
		KeyFrame keyframe;
		//1st frame
		keyframe.TimePos = 0.00f;
		keyframe.BackGroundColor = Color(ControlBackGroundColor, 1.0f);
		LeaveAnimation.AddFrame(keyframe);

		//2nd frame 
		keyframe.TimePos = 0.05f;
		keyframe.BackGroundColor = Color(ControlBackGroundColor, 0.75f);
		LeaveAnimation.AddFrame(keyframe);

		//3rd frame
		keyframe.TimePos = 0.10f;
		keyframe.BackGroundColor = Color(ControlBackGroundColor, 0.5f);
		LeaveAnimation.AddFrame(keyframe);

		//4th frame
		keyframe.TimePos = 0.15f;
		keyframe.BackGroundColor = Color(ControlBackGroundColor, 0.25f);
		LeaveAnimation.AddFrame(keyframe);

		//5th frame
		keyframe.TimePos = 0.2f;
		keyframe.BackGroundColor = Color(ControlBackGroundColor, 0.0f);
		LeaveAnimation.AddFrame(keyframe);
	}

	
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

void ASNET::Control::Control::OnGetFocus(void * sender)
{
}

void ASNET::Control::Control::OnLostFocus(void * sender)
{
}

void ASNET::Control::Control::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * render)
{
}

void ASNET::Control::Control::OnStoping()
{
}



ASNET::Control::Control::Control(){
	IsActive = true;
	IsFocus = false;
	Visibility = true;
	Selectibility = true;
	MouseIn = false;

	BackColor = Color(1, 1, 1, 1);
	SelectBackColor = ControlBackGroundColor;

	InitalizeAnimation();

	BackImage = nullptr;
}

ASNET::Control::Control::operator ASNET::Graph::Rect(){
	return D2D1::RectF(Left, Top, Right, Bottom);
}


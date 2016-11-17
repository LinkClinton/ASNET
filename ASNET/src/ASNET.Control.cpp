#include "ASNET.Control.h"

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG




void ASNET::Control::Control::StartLeaveAnimation(){
	if (!Selectibility) return;
	LeaveAnimation.Start();
}

void ASNET::Control::Control::OnLeaveAnimationDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * render){

	KeyFrame keyframe = LeaveAnimation.GetKeyFrame(); 
	render->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom),
		ASNET::Graph::Color(0, 0, 0, 0), 1.0f, true, keyframe.BackGroundColor);

}



void ASNET::Control::Control::OnStdDraw(void * sender, 
	ASNET::Graph::Direct3D::GraphDirect3D * render){

	if (!BackImage) {
		if (!LeaveAnimation.End())
			OnLeaveAnimationDraw(sender, render);
		else {
			if (Selectibility && MouseIn)
				render->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom),
					ASNET::Graph::Color(0, 0, 0, 0), 1.0f, true, SelectBackColor);
			else
				render->DrawRectangle(D2D1::RectF(Left, Top, Right, Bottom),
					ASNET::Graph::Color(0, 0, 0, 0), 1.0f, true, BackColor);
		}
	}
	else
		render->DrawImage(BackImage,
			D2D1::RectF(Left, Top, Right, Bottom));

	LeaveAnimation.Pass(render->RenderTime());
}

void ASNET::Control::Control::InitalizeAnimation()
{
	LeaveAnimation.SetType(ASNET::Control::AnimationType::Linear);
	//leave animation
	{
		KeyFrame keyframe;
		//1st frame
		keyframe.TimePos = 0.00f;
		keyframe.BackGroundColor = ASNET::Graph::Color(ControlBackGroundColor, 1.0f);
		LeaveAnimation.AddFrame(keyframe);

		//2nd frame 
		keyframe.TimePos = 0.05f;
		keyframe.BackGroundColor = ASNET::Graph::Color(ControlBackGroundColor, 0.75f);
		LeaveAnimation.AddFrame(keyframe);

		//3rd frame
		keyframe.TimePos = 0.10f;
		keyframe.BackGroundColor = ASNET::Graph::Color(ControlBackGroundColor, 0.5f);
		LeaveAnimation.AddFrame(keyframe);

		//4th frame
		keyframe.TimePos = 0.15f;
		keyframe.BackGroundColor = ASNET::Graph::Color(ControlBackGroundColor, 0.25f);
		LeaveAnimation.AddFrame(keyframe);

		//5th frame
		keyframe.TimePos = 0.2f;
		keyframe.BackGroundColor = ASNET::Graph::Color(ControlBackGroundColor, 0.0f);
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

	BackColor = ASNET::Graph::Color(1, 1, 1, 1);
	SelectBackColor = ControlBackGroundColor;

	InitalizeAnimation();

	BackImage = nullptr;
}

ASNET::Control::Control::operator ASNET::Graph::Rect(){
	return D2D1::RectF(Left, Top, Right, Bottom);
}


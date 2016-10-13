#include "ASNET.Control.Animation.h"

auto ASNET::Control::Animation::LinearComputeColor(ASNET::Control::Color front,
	ASNET::Control::Color back, float scale) -> Color
{
	Color out = back - front;
	out = out*scale;
	out = out + front;
	return out;
}

ASNET::Control::Animation::Animation()
{
	Time = 0;
	IsEnd = true;
}

auto ASNET::Control::Animation::GetStartTime()->float
{
	return KeyFrames.begin()->second.TimePos;
}

auto ASNET::Control::Animation::GetEndTime() -> float
{
	Frames::iterator it = KeyFrames.end();
	it--;
	return it->second.TimePos;
}

auto ASNET::Control::Animation::GetKeyFrame() -> ASNET::Control::KeyFrame
{
	return GetKeyFrame(Time);
}

auto ASNET::Control::Animation::GetKeyFrame(float TimePos) -> ASNET::Control::KeyFrame
{
	ASNET::Control::KeyFrame frame;
	
	Frames::iterator it = KeyFrames.end();
	it--;
	if (TimePos >= it->first)
		frame = it->second;
	else if (TimePos <= KeyFrames.begin()->first)
		frame = it->second;
	else {
		Frames::iterator front;
		Frames::iterator back;
		for (Frames::iterator it = KeyFrames.begin(); it != KeyFrames.end(); it++)
			if (it->first >= TimePos) {
				back = it;
				front = --it;
				break;
			}
		float scale = (TimePos - front->first) / (back->first - front->first);
		frame.BackGroundColor = LinearComputeColor(front->second.BackGroundColor, back->second.BackGroundColor, scale);
		frame.TextColor = LinearComputeColor(front->second.TextColor, back->second.BackGroundColor, scale);
		frame.TimePos = TimePos;
	}

	return frame;
}

void ASNET::Control::Animation::AddFrame(ASNET::Control::KeyFrame Frame)
{
	KeyFrames.insert(std::pair<float, KeyFrame>(Frame.TimePos, Frame));
}

void ASNET::Control::Animation::Start()
{
	IsEnd = false;
	Time = 0;
}

void ASNET::Control::Animation::Pass(float PassTime)
{
	if (Time >= GetEndTime()) {
		IsEnd = true;
		Time = 0;
		return;
	}
	Time += PassTime;
}

void ASNET::Control::Animation::Stop()
{
	IsEnd = true;
	Time = 0;
}

auto ASNET::Control::Animation::GetTime() -> float
{
	return Time;
}

bool ASNET::Control::Animation::End()
{
	return IsEnd;
}







ASNET::Control::KeyFrame::KeyFrame()
{
	TextColor = D2D1::ColorF::Azure;
	BackGroundColor = D2D1::ColorF::Azure;
}

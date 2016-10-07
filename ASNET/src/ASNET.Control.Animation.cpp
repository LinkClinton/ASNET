#include "ASNET.Control.Animation.h"

auto ASNET::Control::Animation::GetStartTime()->float
{
	return Frames.front().TimePos;
}

auto ASNET::Control::Animation::GetEndTime() -> float
{
	return Frames.back().TimePos;
}



ASNET::Control::KeyFrame::KeyFrame()
{
	TextColor = D2D1::ColorF::Azure;
	BackGroundColor = D2D1::ColorF::Azure;
}

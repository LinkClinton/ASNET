#include "ASNET.Control.Timer.h"

ASNET::Control::Timer::Timer(){
	Started = false;
}


void ASNET::Control::Timer::Start() {
	LastTime = Time::now();
	Started = true;
}

void ASNET::Control::Timer::End() {
	Started = false;
}


bool ASNET::Control::Timer::GetState() {
	return Started;
}


float ASNET::Control::Timer::GetTime() {
	NowTime = Time::now();
	Time = std::chrono::duration_cast<std::chrono::duration<float>>(NowTime - LastTime);
	return Time.count();
}

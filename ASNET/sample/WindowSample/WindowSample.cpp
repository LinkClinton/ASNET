#include"WindowSample.h"
#include<iostream>
int main() {

}

void ASNET::Sample::WindowSample::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
{
	//鼠标移动的时候的代码
	//sender是发送的窗口的指针
	//e是数据信息
	//这里我们输出鼠标的位置，用控制台输出
	std::cout << "MousePosx=" << e->x << std::endl;
	std::cout << "MousePosy=" << e->y << std::endl;
	std::cout << std::endl;
}

void ASNET::Sample::WindowSample::MyMouseWheel(void * sender, ASNET::Event::EventMouseWheel * e)
{
	//鼠标移动的时候的代码
	//sender是发送的窗口的指针
	//e是数据信息
	//这里我们输出滑轮滚动一次的偏移值
	std::cout << "MouseWheelOffest=" << e->offest << std::endl;
	std::cout << std::endl;
}

 


ASNET::Sample::WindowSample::WindowSample()
{
	//可以在构造函数里面设置好窗口的属性，以此来创建他，Run函数是正在的创建
	Width = 800;
	Height = 600;
	Title = L"ASNET.WindowSample";
	IcoName = NULL;
	using namespace ASNET::Event;
	//把自己写好的事件函数加载进去
	
	
}

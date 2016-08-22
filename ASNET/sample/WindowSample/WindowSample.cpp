#include"WindowSample.h"
#include<iostream>

ASNET::Sample::WindowSample MyWindow;
int main() {
	MyWindow.AddPage(new ASNET::Sample::PageSample());
	MyWindow.ShowPage(0);
	MyWindow.Run();
}

void ASNET::Sample::WindowSample::OnLoading(){
	
}

void ASNET::Sample::WindowSample::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
{
	//鼠标移动的时候的代码
	//sender是发送的窗口的指针,其实就是Window的指针
	ASNET::Sample::WindowSample* Window = (ASNET::Sample::WindowSample*)sender;
	//e是数据信息
	//这里我们记录鼠标的位置
	MousePosX = e->x;
	MousePosY = e->y;
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
	
	//把自己写好的事件函数加载进去
	MouseWheelHandler += ASNET::Sample::WindowSample::MyMouseWheel;
	Initalize();
	InitalizeGraphUI();
}

void ASNET::Sample::PageSample::OnLoading(void * sender, void * any)
{
	//sender 同样是Window的指针，这里我们可以通过这段代码获取现在的Page
	ASNET::Sample::PageSample* Page = (ASNET::Sample::PageSample*)
		ASNET::Event::EventHandler::GetSenderMessage(sender)->NowUsedPage();
	std::cout << "Page Loading" << std::endl;

}

void ASNET::Sample::PageSample::OnDraw(void * sender, ASNET::Graph::Graph * render)
{
	//graph这个变量在这个页面被使用的时候被创建了,当然也可以用render来
	ASNET::Sample::WindowSample* Window = (ASNET::Sample::WindowSample*)sender;
	//清理缓存
	render->Clear();
	//画矩形
	render->DrawRectangle(D2D1::RectF(Window->MousePosX - 10.0f, Window->MousePosY - 10.0f,
		Window->MousePosX + 10.0f, Window->MousePosY + 10.0f), ASNET::Graph::Color::LightSalmon);
	//输出文本
	ASNET::Graph::Font* font = nullptr;

	graph->LoadFont(font, L"Consolas", 20);
	graph->DrawWord(L"Hello,World", D2D1::RectF(0, 0, (float)Window->Width, (float)Window->Height), font,
		ASNET::Graph::Color::Black, ASNET::Graph::TextAlign::Center,
		ASNET::Graph::TextAlign::Center);
	
	delete font;

	//刷新
	render->Present();
	
}

ASNET::Sample::PageSample::PageSample()
{
	
}

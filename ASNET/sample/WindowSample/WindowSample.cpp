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
	//����ƶ���ʱ��Ĵ���
	//sender�Ƿ��͵Ĵ��ڵ�ָ��,��ʵ����Window��ָ��
	ASNET::Sample::WindowSample* Window = (ASNET::Sample::WindowSample*)sender;
	//e��������Ϣ
	//�������Ǽ�¼����λ��
	MousePosX = e->x;
	MousePosY = e->y;
}

void ASNET::Sample::WindowSample::MyMouseWheel(void * sender, ASNET::Event::EventMouseWheel * e)
{
	//����ƶ���ʱ��Ĵ���
	//sender�Ƿ��͵Ĵ��ڵ�ָ��
	//e��������Ϣ
	//��������������ֹ���һ�ε�ƫ��ֵ
	std::cout << "MouseWheelOffest=" << e->offest << std::endl;
	std::cout << std::endl;
}

 


ASNET::Sample::WindowSample::WindowSample()
{
	//�����ڹ��캯���������úô��ڵ����ԣ��Դ�����������Run���������ڵĴ���
	Width = 800;
	Height = 600;
	Title = L"ASNET.WindowSample";
	IcoName = NULL;
	
	//���Լ�д�õ��¼��������ؽ�ȥ
	MouseWheelHandler += ASNET::Sample::WindowSample::MyMouseWheel;
	Initalize();
	InitalizeGraphUI();
}

void ASNET::Sample::PageSample::OnLoading(void * sender, void * any)
{
	//sender ͬ����Window��ָ�룬�������ǿ���ͨ����δ����ȡ���ڵ�Page
	ASNET::Sample::PageSample* Page = (ASNET::Sample::PageSample*)
		ASNET::Event::EventHandler::GetSenderMessage(sender)->NowUsedPage();
	std::cout << "Page Loading" << std::endl;

}

void ASNET::Sample::PageSample::OnDraw(void * sender, ASNET::Graph::Graph * render)
{
	//graph������������ҳ�汻ʹ�õ�ʱ�򱻴�����,��ȻҲ������render��
	ASNET::Sample::WindowSample* Window = (ASNET::Sample::WindowSample*)sender;
	//������
	render->Clear();
	//������
	render->DrawRectangle(D2D1::RectF(Window->MousePosX - 10.0f, Window->MousePosY - 10.0f,
		Window->MousePosX + 10.0f, Window->MousePosY + 10.0f), ASNET::Graph::Color::LightSalmon);
	//����ı�
	ASNET::Graph::Font* font = nullptr;

	graph->LoadFont(font, L"Consolas", 20);
	graph->DrawWord(L"Hello,World", D2D1::RectF(0, 0, (float)Window->Width, (float)Window->Height), font,
		ASNET::Graph::Color::Black, ASNET::Graph::TextAlign::Center,
		ASNET::Graph::TextAlign::Center);
	
	delete font;

	//ˢ��
	render->Present();
	
}

ASNET::Sample::PageSample::PageSample()
{
	
}

#include"WindowSample.h"
#include<iostream>
int main() {

}

void ASNET::Sample::WindowSample::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
{
	//����ƶ���ʱ��Ĵ���
	//sender�Ƿ��͵Ĵ��ڵ�ָ��
	//e��������Ϣ
	//���������������λ�ã��ÿ���̨���
	std::cout << "MousePosx=" << e->x << std::endl;
	std::cout << "MousePosy=" << e->y << std::endl;
	std::cout << std::endl;
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
	using namespace ASNET::Event;
	//���Լ�д�õ��¼��������ؽ�ȥ
	
	
}

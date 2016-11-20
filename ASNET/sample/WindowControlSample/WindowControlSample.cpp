#include "WindowControlSample.h"

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG

ASNET::Sample::ControlWindow* Window;

int main() {
	Window = new ASNET::Sample::ControlWindow();
	Window->AddPage(new ASNET::Sample::ControlStartPage());
	Window->AddPage(new ASNET::Sample::ControlSecondPage());
	Window->ShowPage(0);
	Window->Run();
	Window->Release();
}

ASNET::Sample::ControlWindow::ControlWindow(){
	Height = 600;
	Width = 800;
	Title = L"WindowControlSample";
	IcoName = nullptr;
	Initalize();
}

ASNET::Sample::ControlWindow::~ControlWindow(){

}

void ASNET::Sample::ControlStartPage::OnButton1_MouseDown(void * sender, 
	ASNET::Event::EventMouseClick * e)
{
	ASNET::Control::Button* Button = (ASNET::Control::Button*)sender;
	ASNET::Sample::ControlStartPage* Page = (ASNET::Sample::ControlStartPage*)Button->Parent;
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)Page->Parent;
	if (e->IsDown) {
	//	MainWindow->NextPage();
	}
}

void ASNET::Sample::ControlStartPage::OnButton1_KeyDown(void * sender, ASNET::Event::EventBoardClick * e)
{
	ASNET::Control::Button* Button = (ASNET::Control::Button*)sender;
	ASNET::Sample::ControlStartPage* Page = (ASNET::Sample::ControlStartPage*)Button->Parent;

	
}

auto ASNET::Sample::ControlStartPage::Get(float _float) -> ASNET::Graph::Word
{
	int val = (int)_float;
	std::wstring tmp;
	std::wstring out;
	while (val) {
		tmp += (val % 10) + 48;
		val /= 10;
	}
	for (int i = tmp.size() - 1; i >= 0; i--) {
		out += tmp[i];
	}
	return out;

}

void ASNET::Sample::ControlStartPage::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e)
{

}

void ASNET::Sample::ControlStartPage::OnKeyDown(void * sender, ASNET::Event::EventBoardClick * e)
{
	ControlWindow* window = (ControlWindow*)sender;
	
}

void ASNET::Sample::ControlStartPage::OnDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	
	std::wstring FPSBox = L"FPS: " + Get(graph->FPS());
	graph->DrawWord(FPSBox, D2D1::RectF(0, (float)600 - 20, (float)FPSBox.length()*20.f, (float)800), Consolas12);
}

void ASNET::Sample::ControlStartPage::OnInitalize(void * sender)
{
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)sender;

	surface = new ASNET::Graph::Surface(ParentGraph);
	surface->SetWidth(100);
	surface->SetHeight(100);
	surface->SetPositionX(100);
	surface->SetPositionY(100);

	ParentGraph->LoadFont(Consolas20, L"Consolas", 20);
	ParentGraph->LoadFont(Consolas12, L"Consolas", 12);

	TextBox1 = new ASNET::Control::TextBox(ParentGraph, 20, 100, 20, 40, L"TextBox",Consolas12);

	Button1 = new ASNET::Control::Button(ParentGraph, (float)MainWindow->GetWidth() / 2 - Note1Size,
		(float)MainWindow->GetWidth() / 2 + Note1Size, (float)MainWindow->GetHeight() / 4 * 3 - Note1Size,
		(float)MainWindow->GetHeight() / 4 * 3 + Note1Size, L"Button1", L"...", Consolas20);

	
	Button1->MouseButtonDownHandler += OnButton1_MouseDown;
	Button1->BoardDownHandler += OnButton1_KeyDown;

	Button1->Selectibility = true;
	
	RegisterControl(Button1);
	RegisterControl(TextBox1);
}

void ASNET::Sample::ControlStartPage::OnLoading(void * sender, void * any)
{
	
}

void ASNET::Sample::ControlStartPage::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
{
	
}

ASNET::Sample::ControlStartPage::ControlStartPage()
{
}

ASNET::Sample::ControlStartPage::~ControlStartPage()
{
	delete TextBox1;
	delete Button1;
	delete Consolas20;
	delete Consolas12;
}

void ASNET::Sample::ControlSecondPage::OnDraw(void * sender, 
	ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	graph->Clear();
	
}

void ASNET::Sample::ControlSecondPage::OnInitalize(void * sender)
{
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)sender;

	ParentGraph->LoadFont(Consolas40, L"Consolas", 20);

	Button1 = new ASNET::Control::Button(ParentGraph, (float)MainWindow->GetWidth() / 2 - Button1Size,
		(float)MainWindow->GetWidth() / 2 + Button1Size, (float)MainWindow->GetHeight() / 4 - Button1Size,
		(float)MainWindow->GetHeight() / 4 + Button1Size, L"Button1", L"Back", Consolas40);

	Button1->Selectibility = true;
	Button1->Visibility = true;

	Button1->MouseButtonDownHandler += OnButton1_MouseDown;

	RegisterControl(Button1);

}

void ASNET::Sample::ControlSecondPage::OnLoading(void * sender, void * any)
{

}


void ASNET::Sample::ControlSecondPage::OnButton1_MouseDown(void * sender, 
	ASNET::Event::EventMouseClick * e)
{
	ASNET::Control::Button* Button = (ASNET::Control::Button*)sender;
	ASNET::Sample::ControlSecondPage* Page = (ASNET::Sample::ControlSecondPage*)Button->Parent;
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)Page->Parent;
	if (e->IsDown) {
		MainWindow->ShowPage(0);
	}
}

ASNET::Sample::ControlSecondPage::ControlSecondPage()
{
}

ASNET::Sample::ControlSecondPage::~ControlSecondPage()
{
}

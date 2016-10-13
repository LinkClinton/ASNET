#include "WindowControlSample.h"

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
		MainWindow->NextPage();
	}
}

void ASNET::Sample::ControlStartPage::OnDraw(void * sender,
	ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	graph->Clear();
}

void ASNET::Sample::ControlStartPage::OnInitalize(void * sender)
{
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)sender;

	ParentGraph->LoadFont(Consolas20, L"Consolas", 20);

	Note1 = new ASNET::Control::Label(ParentGraph, (float)MainWindow->GetWidth() / 2 - Note1Size,
		(float)MainWindow->GetWidth() / 2 + Note1Size, (float)MainWindow->GetHeight() / 4 - Note1Size,
		(float)MainWindow->GetHeight() / 4 + Note1Size, L"Note1", L"Hello,Join?", Consolas20);

	Button1 = new ASNET::Control::Button(ParentGraph, (float)MainWindow->GetWidth() / 2 - Note1Size,
		(float)MainWindow->GetWidth() / 2 + Note1Size, (float)MainWindow->GetHeight() / 4 * 3 - Note1Size,
		(float)MainWindow->GetHeight() / 4 * 3 + Note1Size, L"Button1", L"...", Consolas20);

	
	Button1->MouseButtonDownHandler += OnButton1_MouseDown;

	Button1->Selectibility = true;
	Note1->Selectibility = true;


	RegisterControl(Note1);
	RegisterControl(Button1);
}

void ASNET::Sample::ControlStartPage::OnLoading(void * sender, void * any)
{

}

ASNET::Sample::ControlStartPage::ControlStartPage()
{
}

ASNET::Sample::ControlStartPage::~ControlStartPage()
{
	delete Note1;
	delete Button1;
	delete Consolas20;
}

void ASNET::Sample::ControlSecondPage::OnDraw(void * sender, 
	ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	graph->Clear();

}

void ASNET::Sample::ControlSecondPage::OnInitalize(void * sender)
{
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)sender;

	ParentGraph->LoadFont(Consolas40, L"Consola", 40);

	Button1 = new ASNET::Control::Button(ParentGraph, (float)MainWindow->GetWidth() / 2 - Button1Size,
		(float)MainWindow->GetWidth() / 2 + Button1Size, (float)MainWindow->GetHeight() / 4 - Button1Size,
		(float)MainWindow->GetHeight() / 4 + Button1Size, L"Button1", L"Back", Consolas40);

	Button1->Selectibility = true;

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

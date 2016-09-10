#include "WindowControlSample.h"

ASNET::Sample::ControlWindow* Window;

int main() {
	Window = new ASNET::Sample::ControlWindow();
	Window->AddPage(new ASNET::Sample::ControlStartPage());
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

void ASNET::Sample::ControlStartPage::OnDraw(void * sender, 
	ASNET::Graph::Direct3D::GraphDirect3D * graph)
{
	graph->Clear();
}

void ASNET::Sample::ControlStartPage::OnLoading(void * sender, void * any)
{
	ASNET::Sample::ControlWindow* MainWindow = (ASNET::Sample::ControlWindow*)sender;

	ParentGraph->LoadFont(Consolas20, L"Consolas", 20);

	Note1 = new ASNET::Control::Label(ParentGraph, (float)MainWindow->GetWidth() / 2 - Note1Size,
		(float)MainWindow->GetWidth() / 2 + Note1Size, (float)MainWindow->GetHeight() / 4 - Note1Size,
		(float)MainWindow->GetHeight() / 4 + Note1Size, L"Note1", L"Hello,Join?", Consolas20);

	Button1 = new ASNET::Control::Button(ParentGraph, (float)MainWindow->GetWidth() / 2 - Note1Size,
		(float)MainWindow->GetWidth() / 2 + Note1Size, (float)MainWindow->GetHeight() / 4 * 3 - Note1Size,
		(float)MainWindow->GetHeight() / 4 * 3 + Note1Size, L"Button1", L"...", Consolas20);

	
	Button1->Selectibility = true;
	Note1->Selectibility = true;

	RegisterControl(Note1);
	RegisterControl(Button1);
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

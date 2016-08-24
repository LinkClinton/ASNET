#include"WindowDirect3DSample.h"
ASNET::Sample::Direct3DWindow MyWinodw;
DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 0, -15, 1),
	DirectX::XMVectorSet(0, 0, 0, 1),
	DirectX::XMVectorSet(0, 1, 0, 1)));
DirectX::XMMATRIX proj = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI*0.55f,
	800.f / 600.f, 1.0f, 1000.f));
int main() {
	MyWinodw.AddPage(new ASNET::Sample::Direct3DMainPage());
	MyWinodw.ShowPage(0);
	MyWinodw.Run();
	MyWinodw.Release();
}

ASNET::Sample::Direct3DWindow::Direct3DWindow(){
	Width = 800;
	Height = 600;
	Title = L"ASNET.Direct3DSample";
	IcoName = nullptr;

	Initalize();
	shader = new ASNET::Graph::Direct3D::Shader(L"vertexshader.hlsl",
		L"pixelshader.hlsl");
	graph =	new ASNET::Graph::Direct3D::GraphDirect3D(Hwnd, shader);
}

ASNET::Sample::Direct3DWindow::~Direct3DWindow(){
	delete graph;
	delete shader;
}


void ASNET::Sample::Direct3DMainPage::OnLoading(void * sender, void * any){
	ASNET::Sample::Direct3DWindow* Window = (ASNET::Sample::Direct3DWindow*)sender;
	Direct3DRender = Window->graph;
	Direct3DShader = Window->shader;

	Direct3DRender->LoadShaderDataBuffer(
		&world, sizeof(DirectX::XMMATRIX), Direct3DWorld);
	Direct3DRender->LoadShaderDataBuffer(
		&view, sizeof(DirectX::XMMATRIX), Direct3DView);
	Direct3DRender->LoadShaderDataBuffer(
		&proj, sizeof(DirectX::XMMATRIX), Direct3DProj);

	//Direct3DRender->LoadTexture(Direct3DTexture, L"Texture.png");

	Direct3DRender->SetCullMode(ASNET::Graph::Direct3D::CullMode::CullBack);

	Direct3DProj->UpDateBuffer();
	Direct3DView->UpDateBuffer();
	Direct3DWorld->UpDateBuffer();

	Direct3DShader->SendBufferToVertexShader(0, Direct3DProj);
	Direct3DShader->SendBufferToVertexShader(2, Direct3DView);
	Direct3DShader->SendBufferToVertexShader(1, Direct3DWorld);

//	Direct3DShader->SendTextureToShader(0, Direct3DTexture);

	//std::vector<ASNET::Graph::Direct3D::Vertex> vertex;
	//std::vector<ASNET::Graph::Direct3D::Index>  index;

	//CreateCubeVertex(vertex, index);

	//Direct3DRender->LoadBuffer(Direct3DCubeBuffer, vertex, index);

	ASNET::Graph::Direct3D::Direct3DModelLoader::LoadPMDModel(Direct3DRender, L"model/remu.pmd", Direct3DPMDModel);
	
}

void ASNET::Sample::Direct3DMainPage::OnDraw(void * sender, ASNET::Graph::Graph * render){
	Direct3DRender->Clear(D2D1::ColorF::Black);

	world = DirectX::XMMatrixIdentity();

	
	world = world*DirectX::XMMatrixRotationY(ModelAngleY);

	world = world*DirectX::XMMatrixRotationX(ModelAngleX);

	world = world*DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0, -10, 0));

	Direct3DRender->SetCullMode(ASNET::Graph::Direct3D::CullMode::CullNone);


	Direct3DProj->UpDateBuffer();
	Direct3DView->UpDateBuffer();
	Direct3DWorld->UpDateBuffer();

	
	
	//Direct3DRender->SetFillMode(ASNET::Graph::Direct3D::FillMode::FillWireFrame);

	//Direct3DShader->SendBufferToVertexShader(0, Direct3DProj);
	//Direct3DShader->SendBufferToVertexShader(2, Direct3DView);
	Direct3DShader->SendBufferToVertexShader(1, Direct3DWorld);
	
	//Direct3DRender->SetFillMode(ASNET::Graph::Direct3D::FillMode::FillWireFrame);

	Direct3DPMDModel->Draw();

	//Direct3DRender->DrawBuffer(Direct3DCubeBuffer);

	Direct3DRender->Present();
}

void ASNET::Sample::Direct3DMainPage::OnMouseUp(void * sender, ASNET::Event::EventMouseClick * e){
	if (e->button == ASNET::Event::MouseButton::Left) 
		IsMouseDown = false;
	
}

void ASNET::Sample::Direct3DMainPage::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e){
	if (IsMouseDown) {
		int offestx = e->x - LastMousePosx;
		int offesty = e->y - LastMousePosy;
		ModelAngleX += offesty*pixelangle;
		ModelAngleY += offestx*pixelangle;
	}
	LastMousePosx = e->x;
	LastMousePosy = e->y;
}

void ASNET::Sample::Direct3DMainPage::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e){
	if (e->button == ASNET::Event::MouseButton::Left)
		IsMouseDown = true;
}

void ASNET::Sample::Direct3DMainPage::OnMouseWheel(void * sender, ASNET::Event::EventMouseWheel * e){
}


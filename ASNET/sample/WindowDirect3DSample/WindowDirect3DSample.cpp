#include"WindowDirect3DSample.h"
ASNET::Sample::Direct3DWindow MyWinodw;
DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 10, 1, 1),
	DirectX::XMVectorSet(0, 0, 0, 1), DirectX::XMVectorSet(0, 1, 0, 1)));
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

void ASNET::Sample::Direct3DMainPage::CreateCubeVertex(
	std::vector<ASNET::Graph::Direct3D::Vertex>& vertex, 
	std::vector<ASNET::Graph::Direct3D::Index>& index){
	float HXSize = 3.f;
	float HYSize = 3.f;
	float HZSize = 3.f;
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, -HYSize, -HZSize, 0.0f, 1.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, HYSize, -HZSize, 0.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, HYSize, -HZSize, 1.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, -HYSize, -HZSize, 1.0f, 1.0f));

	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, -HYSize, HZSize, 0.0f, 1.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, HYSize, HZSize, 0.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, HYSize, -HZSize, 1.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, -HYSize, -HZSize, 1.0f, 1.0f));

	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, -HYSize, HZSize, 0.0f, 1.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, HYSize, HZSize, 0.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, HYSize, HZSize, 1.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, -HYSize, HZSize, 1.0f, 1.0f));


	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, -HYSize, -HZSize, 0.0f, 1.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, HYSize, -HZSize, 0.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, HYSize, HZSize, 1.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, -HYSize, HZSize, 1.0f, 1.0f));

	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, HYSize, -HZSize, 0.0f, 1.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, HYSize, HZSize, 0.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, HYSize, HZSize, 1.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, HYSize, -HZSize, 1.0f, 1.0f));

	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, -HYSize, HZSize, 0.0f, 1.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(-HXSize, -HYSize, -HZSize, 0.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, -HYSize, -HZSize, 1.0f, 0.0f));
	vertex.push_back(ASNET::Graph::Direct3D::Vertex(HXSize, -HYSize, HZSize, 1.0f, 1.0f));

	

	UINT Index[36] =
	{
		0,1,2, 0,2,3,
		4,5,6, 4,6,7,
		8,9,10, 8,10,11,
		12,13,14, 12,14,15,
		16,17,18, 16,18,19,
		20,21,22, 20,22,23
	};

	for (int i = 0; i <= 35; i++)
		index.push_back(Index[i]);
		
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

	Direct3DProj->UpDateBuffer();
	Direct3DView->UpDateBuffer();
	Direct3DWorld->UpDateBuffer();

	Direct3DShader->SendBufferToVertexShader(0, Direct3DProj);
	Direct3DShader->SendBufferToVertexShader(2, Direct3DView);
	Direct3DShader->SendBufferToVertexShader(1, Direct3DWorld);

	std::vector<ASNET::Graph::Direct3D::Vertex> vertex;
	std::vector<ASNET::Graph::Direct3D::Index>  index;

	CreateCubeVertex(vertex, index);

	Direct3DRender->LoadBuffer(Direct3DCubeBuffer, vertex, index);
}

void ASNET::Sample::Direct3DMainPage::OnDraw(void * sender, ASNET::Graph::Graph * render){
	Direct3DRender->Clear();

	world = world*DirectX::XMMatrixRotationZ(0.02f);

	Direct3DProj->UpDateBuffer();
	Direct3DView->UpDateBuffer();
	Direct3DWorld->UpDateBuffer();

	//Direct3DRender->SetFillMode(ASNET::Graph::Direct3D::FillMode::FillWireFrame);

	Direct3DShader->SendBufferToVertexShader(0, Direct3DProj);
	Direct3DShader->SendBufferToVertexShader(2, Direct3DView);
	Direct3DShader->SendBufferToVertexShader(1, Direct3DWorld);

	Direct3DRender->DrawBuffer(Direct3DCubeBuffer);

	Direct3DRender->Present();
}

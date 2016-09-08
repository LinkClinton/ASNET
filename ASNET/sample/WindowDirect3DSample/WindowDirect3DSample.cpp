#include"WindowDirect3DSample.h"
ASNET::Sample::Direct3DWindow MyWinodw;
DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 0, 15, 1),
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
	Graph->SetShader(shader);
}

ASNET::Sample::Direct3DWindow::~Direct3DWindow(){
	
	delete shader;
}


void ASNET::Sample::Direct3DMainPage::OnLoading(void * sender, void * any){
	ASNET::Sample::Direct3DWindow* Window = (ASNET::Sample::Direct3DWindow*)sender;
	Direct3DShader = Window->shader;
	
	ASNET::Graph::Direct3D::GeometryMaker::CreateGrid(Direct3DMesh, 100, 100, 200, 200);

	Direct3DLabel = new ASNET::Control::Label((ASNET::Graph::Graph*)ParentGraph, 100, 200, 100, 200, L"Lable",
		L"Hello", L"Consolas", 12);

	Direct3DLabel->Selectibility = true;

	Direct3DLabel->Show();

	ASNET::Graph::Direct3D::Direct3DModelLoader::LoadPMXModel(ParentGraph, L"model/Ysna.pmx",
		Direct3DModel);

	RegisterControl(Direct3DLabel);

	//Direct3DRender->LoadTexture(Direct3DTexture, L"model.te4.png");
	
	ParentGraph->LoadBuffer(Direct3DMesh, Direct3DMesh.vertices, Direct3DMesh.indices, true);

	Direct3DEffect = new ASNET::Graph::Direct3D::BasicEffect(ParentGraph);

	ParentGraph->SetCullMode(ASNET::Graph::Direct3D::CullMode::CullNone);

	//Direct3DRender->SetFillMode(ASNET::Graph::Direct3D::FillMode::FillWireFrame);
//	Direct3DShader->SendTextureToShader(0, Direct3DTexture);

	//std::vector<ASNET::Graph::Direct3D::Vertex> vertex;
	//std::vector<ASNET::Graph::Direct3D::Index>  index;

	//CreateCubeVertex(vertex, index);

	//Direct3DRender->LoadBuffer(Direct3DCubeBuffer, vertex, index);

	Direct3DDirLight.ambient = { 0.2f,0.2f,0.2f,0.2f };
	Direct3DDirLight.dir = { 0,0,15 };
	Direct3DDirLight.diffuse = { 0.05f,0.05f,0.05f,0.05f };

	
	//Direct3DModel->Draw(eff)
	Direct3DEffect->Enable(ASNET::Graph::Direct3D::Enable::DirLight);
	Direct3DEffect->Enable(ASNET::Graph::Direct3D::Enable::Texture);


	Direct3DEffect->DirLightOn(0, Direct3DDirLight);
	//Direct3DEffect->PointLightOn(0, Direct3DPointLight);



	//ASNET::Graph::Direct3D::Direct3DModelLoader::LoadPMDModel(Direct3DRender, L"model/remu.pmd", Direct3DPMDModel);
	
}

void ASNET::Sample::Direct3DMainPage::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * render){
	render->Clear(D2D1::ColorF::Black);

	world = DirectX::XMMatrixIdentity();

	
	world = world*DirectX::XMMatrixRotationY(ModelAngleY);

	world = world*DirectX::XMMatrixRotationX(ModelAngleX);

	world = world*DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0, -10, 0));

	Direct3DEffect->SetProjMatrix(proj);
	Direct3DEffect->SetViewMatrix(DirectX::XMVectorSet(0, 0, -15, 1),
		DirectX::XMVectorSet(0, 0, 0, 1));
	Direct3DEffect->SetWorldMatrix(world);
	
	
	

	

	Direct3DEffect->EffectBegin();
	//render->DrawBuffer(Direct3DMesh);
	Direct3DModel->Draw(Direct3DEffect);
	Direct3DEffect->EffectEnd();



	

	

	//Direct3DRender->DrawBuffer(Direct3DCubeBuffer);

	

	
	//std::cout << Direct3DRender->RenderTime() << std::endl;
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


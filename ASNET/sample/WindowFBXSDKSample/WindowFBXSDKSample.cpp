#include "WindowFBXSDKSample.h"


ASNET::Sample::FBXSDKWindow* Window;

DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
DirectX::XMMATRIX proj = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI*0.55f,
	800.f / 600.f, 1.0f, 1000.f));

int main() {
	Window = new ASNET::Sample::FBXSDKWindow();
	Window->AddPage(new ASNET::Sample::FBXSDKPage());
	Window->ShowPage(0);
	Window->Run();
	Window->Release();
}

namespace ASNET {
	namespace Sample {

		FBXSDKWindow::FBXSDKWindow() {
			Height = 600;
			Width = 800;
			Title = L"WindowFBXSDKSample";
			IcoName = nullptr;
			Initalize();
		}

		void FBXSDKPage::OnMouseMove(void * sender, ASNET::Event::EventMouseMove * e)
		{
			if (IsKeyDown) {
				int offestx = e->x - LastMousePosx;
				int offesty = e->y - LastMousePosy;
				ModelAngleX += offesty*pixelangle;
				ModelAngleY += offestx*pixelangle;
			}
			LastMousePosx = e->x;
			LastMousePosy = e->y;
		}

		void FBXSDKPage::OnMouseDown(void * sender, ASNET::Event::EventMouseClick * e)
		{
			if (e->button == ASNET::Event::MouseButton::Left)
				IsKeyDown = true;
		}

		void FBXSDKPage::OnMouseUp(void * sender, ASNET::Event::EventMouseClick * e)
		{
			if (e->button == ASNET::Event::MouseButton::Left)
				IsKeyDown = false;
		}

		void FBXSDKPage::OnMouseLeave(void * sender)
		{
			IsKeyDown = false;
		}

		void FBXSDKPage::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * graph) {
			graph->Clear(ASNET::Graph::Color::Black);

			//graph->SetFillMode(ASNET::Graph::Direct3D::FillMode::FillWireFrame);

			world = DirectX::XMMatrixIdentity();

			//world = world*DirectX::XMMatrixScaling(10, 10, 10);

			world = world*DirectX::XMMatrixRotationY(ModelAngleY);

		//	world = world*DirectX::XMMatrixRotationX(ModelAngleX);

			world = world*(Model->FromCenterToOrigin());

			effect->SetWorldMatrix(world);

			effect->Enable(ASNET::Graph::Direct3D::Enable::Texture);

			effect->EffectBegin();
			Model->Draw(effect);
			effect->EffectEnd();
		}

		void FBXSDKPage::OnLoading(void * sender, void * any) {
			Loader = new ASNET::Sample::FBXLoader();

			Loader->LoadFbxSence("Model/lich_King/lich_King.fbx", Model, ParentGraph);

			//Loader->LoadFbxSence("Model/pika.fbx", Model, ParentGraph);

			effect = new ASNET::Graph::Direct3D::BasicEffect(ParentGraph);

			effect->SetViewMatrix(DirectX::XMVectorSet(70, 0, -1, 1),
				DirectX::XMVectorSet(0, 0, 0, 1));

			effect->SetWorldMatrix(DirectX::XMMatrixIdentity());

			effect->SetProjMatrix(proj);


		}

		FBXSDKPage::FBXSDKPage()
		{
		}
		FBXSDKPage::~FBXSDKPage()
		{
			delete Loader;
			delete Model;
			delete effect;
		}
	}

}
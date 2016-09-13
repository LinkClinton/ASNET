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

		void FBXSDKPage::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * graph) {
			graph->Clear();
			//graph->SetFillMode(ASNET::Graph::Direct3D::FillMode::FillWireFrame);
			//graph->SetCullMode(ASNET::Graph::Direct3D::CullMode::CullNone);

			world = DirectX::XMMatrixIdentity();


			world = world*DirectX::XMMatrixRotationY(ModelAngleY);

			world = world*DirectX::XMMatrixRotationX(ModelAngleX);

			//world = world*DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0, -10, 0));

			effect->SetWorldMatrix(world);

			effect->EffectBegin();
			graph->DrawBuffer(Model->Buffer);
			effect->EffectEnd();
		}

		void FBXSDKPage::OnLoading(void * sender, void * any) {
			Loader = new ASNET::Sample::FBXLoader();

			Loader->LoadFbxSence("Cube.fbx", Model, ParentGraph);

			effect = new ASNET::Graph::Direct3D::BasicEffect(ParentGraph);

			effect->SetViewMatrix(DirectX::XMVectorSet(0, 50, -1, 1),
				DirectX::XMVectorSet(0, 0, 0, 1));

			effect->SetWorldMatrix(DirectX::XMMatrixIdentity());

			effect->SetProjMatrix(proj);


		}

		FBXSDKPage::FBXSDKPage()
		{
		}
	}

}
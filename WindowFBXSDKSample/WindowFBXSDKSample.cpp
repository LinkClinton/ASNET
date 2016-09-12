#include "WindowFBXSDKSample.h"


ASNET::Sample::FBXSDKWindow* Window;
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

		void FBXSDKPage::OnDraw(void * sender, ASNET::Graph::Direct3D::GraphDirect3D * graph) {
			graph->Clear();
			effect->EffectBegin();
			Model->Draw(effect);
			effect->EffectEnd();
		}

		void FBXSDKPage::OnLoading(void * sender, void * any) {
			Loader = new ASNET::Sample::FBXLoader();

			Loader->LoadFbxSence("Camera.fbx", Model, ParentGraph);

			effect = new ASNET::Graph::Direct3D::BasicEffect(ParentGraph);

			effect->SetViewMatrix(DirectX::XMVectorSet(0, -10, 1, 0), DirectX::XMVectorSet(0, 0, 0, 0));

			effect->SetWorldMatrix(DirectX::XMMatrixIdentity());

			DirectX::XMMATRIX proj = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI*0.55f,
				800.f / 600.f, 1.0f, 1000.f));

			effect->SetProjMatrix(proj);


		}

		FBXSDKPage::FBXSDKPage()
		{
		}
	}

}
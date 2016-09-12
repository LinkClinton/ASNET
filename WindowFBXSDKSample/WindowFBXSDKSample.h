#pragma once
#include<ASNET.h>

#include"FBXLoader.h"


namespace ASNET {
	namespace Sample {
		class FBXSDKWindow :public ASNET::Window {
		public:
			FBXSDKWindow();
		};

		class FBXSDKPage :public ASNET::Page::Page {
		private:
			ASNET::Sample::FBXLoader* Loader;

			ASNET::Sample::FBXModel*  Model;

			ASNET::Graph::Direct3D::BasicEffect* effect;

		protected:
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
			void OnLoading(void* sender, void* any)override;
		public:
			FBXSDKPage();

		};
	}
}
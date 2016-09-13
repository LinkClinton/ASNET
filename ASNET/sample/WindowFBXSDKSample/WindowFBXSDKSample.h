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

		private:
			float				  ModelAngleY = 0.0f;
			float                 ModelAngleX = 0.0f;
			const float			  pixelangle = 0.005f;
			bool                  IsKeyDown;
			int					  LastMousePosx;
			int				      LastMousePosy;
		protected:
			void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e)override;
			void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e)override;
			void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e)override;
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* graph)override;
			void OnLoading(void* sender, void* any)override;
		public:
			FBXSDKPage();

		};
	}
}
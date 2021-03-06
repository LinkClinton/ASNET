#include<ASNET.Window.h>
#include<ASNET.Graph.Direct3D.h>
#include<ASNET.Direct3D.Effect.h>
#include<ASNET.Direct3D.Geometry.h>
#include<ASNET.Direct3D.Model.h>
#include<DirectXMath.h>
#include<iostream>

namespace ASNET {
	namespace Sample {

		class Direct3DWindow :public ASNET::Window {
		private:
			ASNET::Graph::Direct3D::Shader*			shader;
			friend class Direct3DMainPage;
		protected:
		public:
			Direct3DWindow();
			~Direct3DWindow();
		};


		class Direct3DMainPage :public ASNET::Page::Page {
		private:
			ASNET::Graph::Direct3D::Model*			  Direct3DModel;
			ASNET::Graph::Direct3D::DirLight		  Direct3DDirLight;
			ASNET::Graph::Direct3D::PointLight        Direct3DPointLight;
			ASNET::Graph::Direct3D::BasicEffect*      Direct3DEffect;
			int										  LastMousePosx;
			int										  LastMousePosy;

			bool									  IsKeyDown;

			
			
			float									  ModelAngleY = 0.0f;
			float                                     ModelAngleX = 0.0f;
			const float								  pixelangle = 0.005f;
			friend class Direct3DWindow;
		protected:
			void OnLoading(void* sender, void* any)override;
			void OnDraw(void* sender, ASNET::Graph::Direct3D::GraphDirect3D* render)override;
			void OnMouseUp(void* sender, ASNET::Event::EventMouseClick* e)override;
			void OnMouseMove(void* sender, ASNET::Event::EventMouseMove* e)override;
			void OnMouseDown(void* sender, ASNET::Event::EventMouseClick* e)override;
			void OnMouseWheel(void* sender, ASNET::Event::EventMouseWheel* e)override;
		public:
			
		};
	}
}
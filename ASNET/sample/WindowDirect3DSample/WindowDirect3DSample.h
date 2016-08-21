#include<ASNET.Window.h>
#include<ASNET.Graph.Direct3D.h>
#include<ASNET.Direct3D.Model.h>
#include<DirectXMath.h>

namespace ASNET {
	namespace Sample {

		class Direct3DWindow :public ASNET::Window {
		private:
			ASNET::Graph::Direct3D::GraphDirect3D*  graph;
			ASNET::Graph::Direct3D::Shader*			shader;
			friend class Direct3DMainPage;
		protected:
		public:
			Direct3DWindow();
			~Direct3DWindow();
		};


		class Direct3DMainPage :public ASNET::Page::Page {
		private:
			ASNET::Graph::Direct3D::GraphDirect3D*    Direct3DRender;
			ASNET::Graph::Direct3D::Shader*			  Direct3DShader;
			ASNET::Graph::Direct3D::ShaderDataBuffer* Direct3DProj;
			ASNET::Graph::Direct3D::ShaderDataBuffer* Direct3DView;
			ASNET::Graph::Direct3D::ShaderDataBuffer* Direct3DWorld;
			ASNET::Graph::Direct3D::Texture*		  Direct3DTexture;
			
			ASNET::Graph::Direct3D::Buffer*			  Direct3DCubeBuffer;

			ASNET::Graph::Direct3D::PMDModel*         Direct3DPMDModel;
			
			friend class Direct3DWindow;
		protected:
			void OnLoading(void* sender, void* any)override;
			void OnDraw(void* sender, ASNET::Graph::Graph* render)override;
		public:
			
		};
	}
}
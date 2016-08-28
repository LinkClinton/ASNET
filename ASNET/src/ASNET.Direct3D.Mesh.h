#pragma once

#include"ASNET.Graph.Direct3D.h"
#include"ASNET.Direct3D.Effect.h"

#include<fstream>
#include<map>

//mesh格式，作为模型的基础类来用的
//存放模型的顶点信息材质贴图信息
//以及支持绘制模型

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			

			class MeshPart {
			public:
				Direct3D::Material Material;
				
				
				UINT TextureID;
				UINT StartFace;
				UINT EffectCount;
				
				Direct3D::Texture* Texture;

				std::wstring MeshPartName;

				friend class Mesh;
				friend class Model;
			public:
				MeshPart();
				~MeshPart();
			};

			class Mesh {
			protected:
				Direct3D::GraphDirect3D*				ParentGraph;

				Direct3D::Buffer*						Buffer;

				UINT VertexCount;
				UINT IndexCount;
				UINT TextureCount;
				UINT MeshPartCount;

				std::vector<Direct3D::Vertex>			vertices;
				std::vector<Direct3D::Index>			indices;
				std::vector<Direct3D::MeshPart>			MeshParts;

				std::vector<Direct3D::Texture*>		    Textures;

				friend class Direct3DModelLoader;
			public:
				Mesh();
				Mesh(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				~Mesh();
				void Draw(UINT texture_id = 0); //the used texture_id in the shader
				void Draw(ASNET::Graph::Direct3D::BasicEffect* effect);

				void PrepareDraw(); 
				void DrawPart(UINT index);

				auto Parts()->int;



				void Release();


			};



		}
	}
}
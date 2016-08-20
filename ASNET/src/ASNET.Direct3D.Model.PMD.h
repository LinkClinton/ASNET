#pragma once
#pragma once
//DirectX
#include<DirectXMath.h>

//ASNET
#include"ASNET.Graph.Direct3D.h"

//std
#include<fstream>

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			union PMDFloat{
				float _float;
				char  _char[4];
			};

			union PMDDword {
				DWORD _Dwrod;
				char  _char[4];
			};

			union PMDWord {
				WORD _Word;
				char _char[2];
			};

			union PMDShort {
				short _short;
				char  _char[2];
			};
		


			struct PMDMaterial {
				DirectX::XMFLOAT4  Ambient;
				DirectX::XMFLOAT4  Diffuse;
				DirectX::XMFLOAT4  Specular;

				float Alphadif;
				float Spemat;
				
				ASNET::Graph::Word TextureName;
				ASNET::Graph::Word SpaName;

				UINT StartFace;
				UINT EffectCount;
				UINT TextureID;

				ASNET::Graph::Direct3D::Texture* Texture;
			};

			class PMDModel {
			private:
				static const int PMDModelVertexLimit = 666233;
				static const int PMDModelIndexLimit = 666233;
				static const int PMDModelMaterialLimit = 233;
				static	const int PMDModelBitsLimit = 23333333;
			private:
				ASNET::Graph::Direct3D::GraphDirect3D* ParentGraph;

				ASNET::Graph::Direct3D::Buffer* VertexBuffer;
				ASNET::Graph::Direct3D::Buffer* IndexBUffer;

				
				UINT VertexNum;
				UINT IndexNum;
				UINT MaterialNum;


				std::vector<ASNET::Graph::Direct3D::Vertex>			vertices;
				std::vector<ASNET::Graph::Direct3D::Index>			indices;
				std::vector<ASNET::Graph::Direct3D::PMDMaterial>	materials;

				ASNET::Graph::Word ModelName;
				ASNET::Graph::Word ModelComment;


				
				friend class Direct3DModelLoader;
			private:
				static float PMDFloatRead(std::ifstream* file);
				static short PMDShortRead(std::ifstream* file);
				static DWORD PMDDwordRead(std::ifstream* file);
				static WORD  PMDWordRead(std::ifstream* file);
				static void  PMDRuleOut(std::ifstream* file, int num);
			public:

			};
		}
	}
}
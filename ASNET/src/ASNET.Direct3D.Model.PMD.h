#pragma once
#pragma once
//DirectX
#include<DirectXMath.h>

//ASNET
#include"ASNET.Graph.Direct3D.h"

//std
#include<fstream>
#include<cstring>
#include<memory>
#include<map>

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
		


			struct PMDModelPart {
				DirectX::XMFLOAT4  Ambient;
				DirectX::XMFLOAT4  Diffuse;
				DirectX::XMFLOAT4  Specular;

				float Alphadif;
				float Spemat;
				
				std::wstring	   TextureName;


				UINT StartFace;
				UINT EffectCount;
				UINT TextureID;

				ASNET::Graph::Direct3D::Texture* Texture;
				PMDModelPart();
				~PMDModelPart();
			};


			class PMDModel {
			private:
				static const int PMDModelVertexLimit = 666233;
				static const int PMDModelIndexLimit = 666233;
				static const int PMDModelMaterialLimit = 233;
				static const int PMDModelBitsLimit = 23333333;
			private:
				ASNET::Graph::Direct3D::GraphDirect3D* ParentGraph;

				ASNET::Graph::Direct3D::Buffer* Buffer;

				
				UINT VertexNum;
				UINT IndexNum;
				UINT ModelPartsNum;

				
				std::vector<ASNET::Graph::Direct3D::Vertex>			vertices;
				std::vector<ASNET::Graph::Direct3D::Index>			indices;
				std::vector<ASNET::Graph::Direct3D::PMDModelPart>	ModelParts;

				std::map<std::wstring,
					ASNET::Graph::Direct3D::Texture*>				Textures;

				std::wstring										FilePath;
				friend class Direct3DModelLoader;
			public:
				static float PMDFloatRead(std::ifstream* file);
				static short PMDShortRead(std::ifstream* file);
				static DWORD PMDDwordRead(std::ifstream* file);
				static WORD  PMDWordRead(std::ifstream* file);
				static void  PMDRuleOut(std::ifstream* file, int num);
			public:
				~PMDModel();
				void Draw(int texture_id = 0);// the id of texture in shader,最好别用,基本上代码是完全限制住了，且没有好的着色器代码对应
			
				void PrepareDraw(); //DrawPart之前的准备,把绘制过程分解可以使之能够对着色器的支持更加好
				void DrawPart(int index); //绘制模型部分
				
				auto ModelPatsNum()->int;
				void Release();
			};
		}
	}
}
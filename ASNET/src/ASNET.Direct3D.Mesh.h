#pragma once

#include"ASNET.Graph.Direct3D.h"
#include"ASNET.Direct3D.Effect.h"

#include<fstream>
#include<map>

/*
* mesh格式，作为模型的基础类来用的
* 存放模型的顶点信息材质贴图信息
* 以及支持绘制模型
*/

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			
			//MeshPart部分
			class MeshPart {
			public:
				Direct3D::Material Material; //材质信息
				
				
				UINT TextureID; //使用的贴图ID
				UINT StartFace; //索引开始的位置
				UINT EffectCount; //所用的索引个数
				
				Direct3D::Texture* Texture; //贴图

				std::wstring MeshPartName; //名字

				friend class Mesh;
				friend class Model;
			public:
				//构造函数
				MeshPart();
				//析构函数
				~MeshPart();
			};

			//Mesh类
			class Mesh {
			protected:
				Direct3D::GraphDirect3D*				ParentGraph; //渲染的指针接口

				Direct3D::Buffer*						Buffer; //缓存

				UINT VertexCount; //顶点个数
				UINT IndexCount; //索引个数
				UINT TextureCount; //贴图个数
				UINT MeshPartCount; //模型部分个数

				std::vector<Direct3D::Vertex>			vertices; //顶点
				std::vector<Direct3D::Index>			indices; //索引
				std::vector<Direct3D::MeshPart>			MeshParts; //MeshPart

				std::vector<Direct3D::Texture*>		    Textures; //贴图

				friend class Direct3DModelLoader;
			public:
				//构造函数，只是为了继承所用
				Mesh();
				//构造函数
				Mesh(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//析构函数
				~Mesh();
				//绘制这个模型
				void Draw(UINT texture_id = 0); //the used texture_id in the shader
				//通过使用Effect绘制这个模型
				void Draw(ASNET::Graph::Direct3D::BasicEffect* effect, bool TextureEnable = true);
				//绘制模型要做的准备
				void PrepareDraw(); 
				//绘制模型的某个部分
				void DrawPart(UINT index);

				//返回Part的个数
				auto Parts()->int; 


				//释放资源
				void Release();


			};



		}
	}
}
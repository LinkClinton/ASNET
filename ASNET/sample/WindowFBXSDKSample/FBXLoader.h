#pragma once

#include<fbxsdk.h>

#include<ASNET.Direct3D.Model.h>

namespace ASNET {
	namespace Sample {

		class FBXModel :public ASNET::Graph::Direct3D::Model {
			friend class FBXLoader;
			friend class FBXSDKPage;
		public:
			FBXModel(ASNET::Graph::Direct3D::GraphDirect3D* graph) {
				ParentGraph = graph;
			}
			
		};

		

		typedef ASNET::Graph::Direct3D::Vertex FbxVertex;

		


		class FBXLoader {
		private:
			FbxManager*     Manager; //内存管理
			FbxIOSettings*  Ios; //输入输出设置

			ASNET::Sample::FBXModel* Model;
		protected: 
		protected:
			void ReadVertex(FbxMesh* mesh, int index, FbxVertex* vertex);
			void ReadColor(FbxMesh* mesh, int index, int indexcount, FbxVertex* vertex);
			void ReadTextureUV(FbxMesh* mesh, int index, int textureindex, FbxVertex* vertex);
			void ReadNormal(FbxMesh* mesh, int index, int indexcount, FbxVertex* vertex);
			void ReadMaterial(FbxMesh* mesh, int materialindex, ASNET::Graph::Direct3D::MeshPart* part);
			void ReadTextureName(FbxMesh* mesh, int materialindex, ASNET::Graph::Direct3D::MeshPart* part);
			void LoadMaterial(FbxMesh* mesh, FBXModel* model);
			
			
			

			void ProcessNode(FbxNode* node); //处理节点
			void ProcessMesh(FbxNode* node); //处理Mesh节点
			void ProcessSkeleton(FbxNode* node); //处理Skeleton
		public:
			FBXLoader();
			~FBXLoader();
			//加载FBX文件，需要在导出FBX的时候设置为三角形算法
			void LoadFbxSence(char* filename, ASNET::Sample::FBXModel* &model, ASNET::Graph::Direct3D::GraphDirect3D* graph);



		};

	}
}
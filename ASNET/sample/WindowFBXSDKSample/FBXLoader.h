#pragma once

#include<fbxsdk.h>

#include<ASNET.Direct3D.Model.h>

namespace ASNET {
	namespace Sample {

		class FBXModel :public ASNET::Graph::Direct3D::Model {
			friend class FBXLoader;
			friend class FBXSDKPage;
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
			void ReadVertex(FbxMesh* mesh, int index, FbxVertex* vertex);
			void ReadColor(FbxMesh* mesh, int index, int vertexcount, FbxVertex* vertex);


			void ProcessNode(FbxNode* node); //处理节点
			void ProcessMesh(FbxNode* node); //处理Mesh节点
		public:
			FBXLoader();

			void LoadFbxSence(char* filename, ASNET::Sample::FBXModel* &model, ASNET::Graph::Direct3D::GraphDirect3D* graph);



		};

	}
}
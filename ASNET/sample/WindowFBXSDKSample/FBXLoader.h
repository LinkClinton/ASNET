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
			FbxManager*     Manager; //�ڴ����
			FbxIOSettings*  Ios; //�����������

			ASNET::Sample::FBXModel* Model;
		protected:
			void ReadVertex(FbxMesh* mesh, int index, FbxVertex* vertex);
			void ReadColor(FbxMesh* mesh, int index, int vertexcount, FbxVertex* vertex);


			void ProcessNode(FbxNode* node); //����ڵ�
			void ProcessMesh(FbxNode* node); //����Mesh�ڵ�
		public:
			FBXLoader();

			void LoadFbxSence(char* filename, ASNET::Sample::FBXModel* &model, ASNET::Graph::Direct3D::GraphDirect3D* graph);



		};

	}
}
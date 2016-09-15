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
			FbxManager*     Manager; //�ڴ����
			FbxIOSettings*  Ios; //�����������

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
			
			
			

			void ProcessNode(FbxNode* node); //����ڵ�
			void ProcessMesh(FbxNode* node); //����Mesh�ڵ�
			void ProcessSkeleton(FbxNode* node); //����Skeleton
		public:
			FBXLoader();
			~FBXLoader();
			//����FBX�ļ�����Ҫ�ڵ���FBX��ʱ������Ϊ�������㷨
			void LoadFbxSence(char* filename, ASNET::Sample::FBXModel* &model, ASNET::Graph::Direct3D::GraphDirect3D* graph);



		};

	}
}
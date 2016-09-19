#pragma once

#include<fbxsdk.h>

#include<ASNET.Direct3D.Model.h>


#ifdef _DEBUG
#include<iostream>
#include<string>
#endif // _DEBUG

namespace ASNET {
	namespace Sample {

		class FBXModel :public ASNET::Graph::Direct3D::Model {
			friend class FBXLoader;
			friend class FBXSDKPage;

			std::map<std::wstring, int> FileNameIndex;
					
		public:
			FBXModel(ASNET::Graph::Direct3D::GraphDirect3D* graph) {
				ParentGraph = graph;
			}
			
		};

		

		typedef ASNET::Graph::Direct3D::Vertex FbxVertex;

		static void ReadLine(std::string &String,std::ifstream* file) {
			char ch = file->get();
			while (ch != '\n') {
				String += ch;
				if (file->eof()) break;
				ch = file->get();
			}
		}

		static void ReadVertexPosition(ASNET::Graph::Word filename) {
			std::ifstream file_in;
			std::ofstream file_out;
			int cnt = 0;
			file_in.open(filename);
			file_out.open("result.out");
			std::string String;
			while (!file_in.eof()) {
				String.clear();
				ReadLine(String, &file_in);
				if (int pos = String.find("Coordinates:") != String.npos) {
					cnt++;
					if (cnt <= 2255)
						file_out << String.substr(pos + 24) << std::endl;
				}
			}
		}

		static void ReadTextureUVFromFile(ASNET::Graph::Word filename) {
			std::ifstream file_in;
			std::ofstream file_out;
			file_in.open(filename);
			file_out.open("result.out");
			std::string String;
			while (!file_in.eof()) {
				String.clear();
				ReadLine(String, &file_in);
				if (int pos = String.find("Texture UV:") != String.npos) {
					
					file_out << String.substr(pos + 23) << std::endl;
				}
			}
		}


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
			void ReadTextureName(FbxMesh* mesh, int materialindex, ASNET::Sample::FBXModel* model);

			void LoadMaterialAndTexture(FbxMesh* mesh, FBXModel* model);
			
			
			

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
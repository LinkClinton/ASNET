#pragma once

#include<fbxsdk.h>

#include<ASNET.Direct3D.Model.h>

#include"FBXAnimation.h"

#ifdef _DEBUG
#include<iostream>
#include<string>
#define out(x) std::cout<<x<<std::endl;
#endif // _DEBUG

#define INF 377777

namespace ASNET {
	namespace Sample {

		typedef ASNET::Graph::Direct3D::Vertex FbxVertex;

		class Bone {
		public:
			int   id;
			Bone* parent;
		public:
			Bone(int _id, Bone* _parent) {
				id = _id;
				parent = _parent;
			}
			operator int() {
				return id;
			}
		};

		class FBXModel :public ASNET::Graph::Direct3D::Model {
			friend class FBXLoader;
			friend class FBXSDKPage;

			std::map<std::wstring, int>      FileNameIndex;
			std::map<std::string, Bone*>     BoneNameIndex;
			std::vector<Bone*>				 Parent;
			int								 BoneCount;
			Bone*                            root;
			bool                             IsFrame;
			float                            Time;
			
			DirectX::XMFLOAT3 MaxPos;
			DirectX::XMFLOAT3 MinPos;
			DirectX::XMFLOAT3 CenterPos;

			std::vector<ASNET::Sample::BoneAnimationGroup> Animations;


			FbxScene*						 Scene;
			FbxPose*                         Pose;
			FbxMesh*                         Mesh;
			FbxAnimLayer*                    AnimLayer;
			FbxTime                          FrameStartTime;
			FbxTime                          FrameEndTime;
			FbxTime                          FrameTime;
			static DirectX::XMFLOAT4 Mul(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4X4 m) {
				DirectX::XMFLOAT4 out;
				out.x = a.x*m._11 + a.y*m._12 + a.z*m._13 + a.w*m._14;
				out.y = a.x*m._21 + a.y*m._22 + a.z*m._23 + a.w*m._24;
				out.z = a.x*m._31 + a.y*m._32 + a.z*m._33 + a.w*m._34;
				out.w = a.x*m._41 + a.y*m._42 + a.z*m._43 + a.w*m._44;
				return out;
			}
			static DirectX::XMFLOAT4 Mul(DirectX::XMFLOAT4 a, float m) {
				DirectX::XMFLOAT4 out;
				out.x = a.x*m;
				out.y = a.y*m;
				out.z = a.z*m;
				out.w = a.w*m;
				return out;
			}
			static DirectX::XMFLOAT4 Add(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 m) {
				DirectX::XMFLOAT4 out;
				out.x = a.x + m.x;
				out.y = a.y + m.y;
				out.z = a.z + m.z;
				out.w = a.w + m.w;
				return out;
			}


			void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);
			void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
			void MatrixScale(FbxAMatrix& pMatrix, double pValue);
			FbxAMatrix GetGeometry(FbxNode* pNode);
			FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex);
			FbxAMatrix GetGlobalPosition(FbxNode* pNode,
				const FbxTime& pTime,
				FbxPose* pPose, FbxAMatrix* pParentGlobalPosition = nullptr);
			void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition,
				FbxMesh* pMesh,
				FbxCluster* pCluster,
				FbxAMatrix& pVertexTransformMatrix,
				FbxTime pTime,
				FbxPose* pPose);
			void ComputeLinearDeformation(FbxAMatrix& pGlobalPosition,
				FbxMesh* pMesh,
				FbxTime& pTime,
				FbxVector4* pVertexArray,
				FbxPose* pPose);
		public:
			FBXModel(ASNET::Graph::Direct3D::GraphDirect3D* graph) {
				ParentGraph = graph;
				IsFrame = false;
				MaxPos = DirectX::XMFLOAT3(-INF, -INF, -INF);
				MinPos = DirectX::XMFLOAT3(INF, INF, INF);
			}
			void UpDataFrame(float time, int animation);
			void DrawAnimation(int animation);
			void UpDataCenterPos(ASNET::Sample::FbxVertex vertex);
			void GetFinalTransform(float time, int animation, std::vector<DirectX::XMFLOAT4X4> &matrix);
			

			void SetCurrentPose(int index);

			void SetCurrentAnimation(int index);
			
			void DrawAnimation();

			DirectX::XMMATRIX FromCenterToOrigin();

		};

		

		
		

		

#ifdef _DEBUG
		static void ReadLine(std::string &String, std::ifstream* file) {
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
#endif // _DEBUG


		

		


		class FBXLoader {
		private:
			FbxManager*     Manager; //内存管理
			FbxIOSettings*  Ios; //输入输出设置

			ASNET::Sample::FBXModel* Model;
			bool                     Once;
		protected: 
			void ProcessBoneName(FbxNode* pNode, ASNET::Sample::FBXModel* model, Bone* parent);
		protected:
			void HashBoneName(FbxScene* pScene, FbxNode* pNode, ASNET::Sample::FBXModel* model);
			void ReadVertex(FbxMesh* mesh, int index, FbxVertex* vertex);
			void ReadColor(FbxMesh* mesh, int index, int indexcount, FbxVertex* vertex);
			void ReadTextureUV(FbxMesh* mesh, int index, int textureindex, FbxVertex* vertex);
			void ReadNormal(FbxMesh* mesh, int index, int indexcount, FbxVertex* vertex);
			void ReadMaterial(FbxMesh* mesh, int materialindex, ASNET::Graph::Direct3D::MeshPart* part);
			void ReadTextureName(FbxMesh* mesh, int materialindex, ASNET::Sample::FBXModel* model);
			void ReadWeightsAndBoneIndex(FbxMesh* mesh, ASNET::Sample::FBXModel* model);

			void LoadMaterialAndTexture(FbxMesh* mesh, FBXModel* model);
			void LoadAnimationLayer(FbxAnimLayer* layer, FbxNode* pNode, int animation_id);
			void LoadAnimation(FbxScene* pScene);
			
			

			void ProcessNode(FbxNode* node); //处理节点
			void ProcessMesh(FbxNode* node); //处理Mesh节点
			void ProcessLight(FbxNode* node);
			void ProcessSkeleton(FbxNode* node); //处理Skeleton
		public:
			FBXLoader();
			~FBXLoader();
			//加载FBX文件，需要在导出FBX的时候设置为三角形算法
			void LoadFbxSence(char* filename, ASNET::Sample::FBXModel* &model, ASNET::Graph::Direct3D::GraphDirect3D* graph);



		};

	}
}
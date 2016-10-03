#pragma once
#include<ASNET.h>
#include<ASNET.Direct3D.Mesh.h>
namespace ASNET {
	namespace Sample {
		class KeyFrame {
		public:
			float TimePos;
			DirectX::XMFLOAT3 Translation;
			DirectX::XMFLOAT3 Scale;
			DirectX::XMFLOAT4 RotationQuat;

			KeyFrame();
		};

		class Animation {
		public:
			std::vector<KeyFrame> KeyFrames;
		public:
			float GetStartKeyFrame() { return KeyFrames.front().TimePos; };
			float GetEndKeyFrame() { return KeyFrames.back().TimePos; }

			DirectX::XMFLOAT4X4 KeyFrame(float TimePos);
		};

		class AnimationGroup {
		public:
			std::vector<Animation> BoneAnimations;
		public:
			float GetStartKeyFrame();
			float GetEndKeyFrame();
			void  GetKeyFrame(float TimePos, std::vector<DirectX::XMFLOAT4X4> &BonesTransforms);
		};


		class Bone {
		public:
			int   ID;
			Bone* Parent;
			
			std::string BoneName;

		public:
			Bone(int _ID, Bone* _Parent);
		};

		class Model :public ASNET::Graph::Direct3D::Mesh {
		private:
			typedef std::map<std::string, int>    Filemap;
			typedef std::map<std::string, Bone*>  Bonemap;
		private:
			Filemap	FileNameIndex;
			Bonemap	BoneNameIndex;
			std::vector<Bone*> Parent;

		
			
			bool    IsFrame;
			float   NowTime;
			float   StartTime;
			float   EndTime;

			AnimationGroup* CurrentAnimation;

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

			void   GetFinalTransform(float time, int animation, std::vector<DirectX::XMFLOAT4X4> &matrix);
		public:
			Model(ASNET::Graph::Direct3D::GraphDirect3D* graph);

			void   SetCurrentAnimation(AnimationGroup* Animation);

			void   DrawAnimation();

		};

	}
}
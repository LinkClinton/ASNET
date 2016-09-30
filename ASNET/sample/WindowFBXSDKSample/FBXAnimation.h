#pragma once
#include<ASNET.h>

namespace ASNET {
	namespace Sample {

		class FBXKeyFrame {
		public:
			float TimePos;
			DirectX::XMFLOAT3 Translation;
			DirectX::XMFLOAT3 Scale;
			DirectX::XMFLOAT4 RotationQuat;

			FBXKeyFrame() {
				TimePos = 0; 
				Translation = DirectX::XMFLOAT3(0, 0, 0);
				Scale = DirectX::XMFLOAT3(1, 1, 1);
				RotationQuat = DirectX::XMFLOAT4(0, 0, 0, 1);
			}
		};

		class BoneAnimation {
		public:
			std::vector<FBXKeyFrame> KeyFrames;
		public:
			float GetStartKeyFrame() { return KeyFrames.front().TimePos; };
			float GetEndKeyFrame() { return KeyFrames.back().TimePos; }
			DirectX::XMFLOAT4X4 KeyFrame(float TimePos) {
				if (TimePos <= KeyFrames.front().TimePos) {
					DirectX::XMVECTOR scale = XMLoadFloat3(&KeyFrames.front().Scale);
					DirectX::XMVECTOR translation = XMLoadFloat3(&KeyFrames.front().Translation);
					DirectX::XMVECTOR rotationquat = XMLoadFloat4(&KeyFrames.front().RotationQuat);
					DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
					DirectX::XMFLOAT4X4 out = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
					DirectX::XMStoreFloat4x4(&out, DirectX::XMMatrixAffineTransformation(scale, zero, rotationquat, translation));
					return out;
				}
				else if (TimePos >= KeyFrames.back().TimePos) {
					DirectX::XMVECTOR scale = XMLoadFloat3(&KeyFrames.back().Scale);
					DirectX::XMVECTOR translation = XMLoadFloat3(&KeyFrames.back().Translation);
					DirectX::XMVECTOR rotationquat = XMLoadFloat4(&KeyFrames.back().RotationQuat);
					DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
					DirectX::XMFLOAT4X4 out = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
					DirectX::XMStoreFloat4x4(&out, DirectX::XMMatrixAffineTransformation(scale, zero, rotationquat, translation));
					return out;
				}
				else {
					for (size_t i = 0; i < KeyFrames.size() - 1; i++) {
						if (TimePos >= KeyFrames[i].TimePos && TimePos <= KeyFrames[i].TimePos) {
							float lerpPercent = (TimePos - KeyFrames[i].TimePos / KeyFrames[i + 1].TimePos - KeyFrames[i].TimePos);
							DirectX::XMVECTOR scale0 = XMLoadFloat3(&KeyFrames[i].Scale);
							DirectX::XMVECTOR scale1 = XMLoadFloat3(&KeyFrames[i + 1].Scale);

							DirectX::XMVECTOR translation0 = XMLoadFloat3(&KeyFrames[i].Translation);
							DirectX::XMVECTOR translation1 = XMLoadFloat3(&KeyFrames[i + 1].Translation);

							DirectX::XMVECTOR rotationquat0 = XMLoadFloat4(&KeyFrames[i].RotationQuat);
							DirectX::XMVECTOR rotationquat1 = XMLoadFloat4(&KeyFrames[i + 1].RotationQuat);

							DirectX::XMVECTOR scale = DirectX::XMVectorLerp(scale0, scale1, lerpPercent);
							DirectX::XMVECTOR translation = DirectX::XMVectorLerp(translation0, translation1, lerpPercent);
							DirectX::XMVECTOR rotationquat = DirectX::XMQuaternionSlerp(rotationquat0, rotationquat1, lerpPercent);

							DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
							DirectX::XMFLOAT4X4 out = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
							DirectX::XMStoreFloat4x4(&out, DirectX::XMMatrixAffineTransformation(scale, zero, rotationquat, translation));
							return out;
						}
					}
				}
				DirectX::XMFLOAT4X4 out = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
				return out;
			}
		};

		class BoneAnimationGroup {
		public:
			std::vector<BoneAnimation> BoneAnimations;
		public:
			float GetStartKeyFrame() {
				float t = BoneAnimations.front().GetStartKeyFrame();
				for (auto bone : BoneAnimations) {
					t = min(t, bone.GetStartKeyFrame());
				}
				return t;
			};
			float GetEndKeyFrame() {
				float t = BoneAnimations.front().GetEndKeyFrame();
				for (auto bone : BoneAnimations) {
					t = fmax(t, bone.GetEndKeyFrame());
				}
				return t;
			};
			void  GetKeyFrame(float TimePos, std::vector<DirectX::XMFLOAT4X4> &BonesTransforms) {
				for (size_t i = 0; i < BoneAnimations.size(); i++)
					BonesTransforms.push_back(BoneAnimations[i].KeyFrame(TimePos));
			}
		};


	}
}
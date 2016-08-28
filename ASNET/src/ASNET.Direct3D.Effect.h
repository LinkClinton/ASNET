#pragma once

#include"ASNET.Graph.Direct3D.h"

//DirectX
#include<DirectXMath.h>

//std
#include<vector>

//Effect�࣬�����˲�����ɫ������
//����һЩ�򵥵���Ч��ʹ��
//Ŀǰ�����Ͼ��ǹ�����

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			static const int MaxLights = 16;


			//Dir Light 
			struct DirLight {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;

				DirectX::XMFLOAT3 dir;
				
				float			  unsed;
				typedef DirLight Collections[MaxLights];
			};

			struct PointLight {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;

				DirectX::XMFLOAT3 pos;
				float			  range;

				DirectX::XMFLOAT3 att;

				float			  unused;
				typedef PointLight Collections[MaxLights];
			};

			struct SpotLight {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;
				
				DirectX::XMFLOAT3 dir;
				float			  range;

				DirectX::XMFLOAT3 pos;
				float			  spot;

				DirectX::XMFLOAT3 att;
				float		      theta;
				typedef SpotLight Collections[MaxLights];
			};

			struct Material {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular; //���ĸ�Ԫ���ǲ��ʹ⻬
				typedef std::vector<Material> Collections;
			};

			
			enum class Enable {
				DirLight,
				SpotLight,
				PointLight,
				Texture
			};

			enum class UnEnable {
				DirLight,
				SpotLight,
				PointLight,
				Texture
			};


			class BasicEffect {
			private:
				struct StateEnable {
					int EnableDirLight;
					int EnableSpotLight;
					int EnablePointLight;
					int EnableTexture;
					
					StateEnable();
				};

				struct StateLights {
					int DirLightsState;
					int SpotLihtsState;
					int PointLightsState;
					int unused;
					typedef StateLights Collections[16];
					StateLights();
				};

			private:
				bool                        EffectIsBegin;
				StateEnable					EffectState;
				StateLights::Collections	LightsState;
				Direct3D::ShaderDataBuffer* EffectStateBuffer;
				Direct3D::ShaderDataBuffer* LightsStateBuffer;

				Direct3D::Shader*			EffectShader;
				Direct3D::GraphDirect3D*    ParentGraph;
				void UpdateBufferToShader();
			private:
				Direct3D::DirLight::Collections			DirLights;
				Direct3D::SpotLight::Collections		SpotLights;
				Direct3D::PointLight::Collections		PointLights;

				Direct3D::ShaderDataBuffer*				MaterialBuffer;
				Direct3D::ShaderDataBuffer*				DirLightsBuffer;
				Direct3D::ShaderDataBuffer*             SpotLightsBuffer;
				Direct3D::ShaderDataBuffer*             PointLightsBuffer;
			private:
				Direct3D::ShaderDataBuffer*				EyePosBuffer;
				Direct3D::ShaderDataBuffer*             ProjMatrixBuffer;
				Direct3D::ShaderDataBuffer*             ViewMatrixBuffer;
				Direct3D::ShaderDataBuffer*				WorldMatrixBuffer;
				Direct3D::ShaderDataBuffer*             NormalMatrixBuffer;
			
				static DirectX::XMMATRIX Transpose(DirectX::CXMMATRIX matrix);
				static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX matrix);
			public:
				BasicEffect(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				~BasicEffect();
				void Enable(ASNET::Graph::Direct3D::Enable thing);

				void UnEnable(ASNET::Graph::Direct3D::UnEnable thing);

				void DirLightOn(int which, 
					ASNET::Graph::Direct3D::DirLight dirlight);

				void DirLightOff(int which);

				void SpotLightOn(int which,
					ASNET::Graph::Direct3D::SpotLight spotlight);

				void SpotLightOff(int which);

				void PointLightOn(int which,
					ASNET::Graph::Direct3D::PointLight pointlight);

				void PointLightOff(int which);

				void SetMaterial(ASNET::Graph::Direct3D::Material material);

				void SetTexture(ASNET::Graph::Direct3D::Texture* texture);

				void SetProjMatrix(DirectX::CXMMATRIX matrix);

				void SetViewMatrix(DirectX::XMVECTOR eyepos, DirectX::XMVECTOR lookat);
				
				void SetWorldMatrix(DirectX::CXMMATRIX matrix);
				
				void EffectBegin(); //used the effect in this ,but the old shader can't be used

				void EffectEnd(); //the old shader will be reused
			};


		}
	}
}
#pragma once

#include"ASNET.Graph.Direct3D.h"

//DirectX
#include<DirectXMath.h>

//std
#include<vector>

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
				DirectX::XMFLOAT4 specular; //第四个元素是材质光滑
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
					bool EnableDirLight;
					bool EnableSpotLight;
					bool EnablePointLight;
					bool EnableTexture;

					DirectX::XMFLOAT3 unused0;
					StateEnable();
				};

				struct StateLights {
					bool DirLightsState[MaxLights];
					bool SpotLihtsState[MaxLights];
					bool PointLightsState[MaxLights];
					StateLights();
				};

			private:
				StateEnable					EffectState;
				StateLights					LightsState;
				Direct3D::ShaderDataBuffer* EffectStateBuffer;
				Direct3D::ShaderDataBuffer* LightsStateBuffer;

				Direct3D::Shader*			EffectShader;
				Direct3D::GraphDirect3D*    ParentGraph;
			private:
				Direct3D::DirLight::Collections			DirLights;
				Direct3D::SpotLight::Collections		SpotLights;
				Direct3D::PointLight::Collections		PointLights;

				Direct3D::ShaderDataBuffer*				DirLightsBuffer;
				Direct3D::ShaderDataBuffer*             SpotLightsBuffer;
				Direct3D::ShaderDataBuffer*             PointLightsBuffer;

			
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

				void SetTexture(ASNET::Graph::Direct3D::Texture* texture);

				
			};


		}
	}
}
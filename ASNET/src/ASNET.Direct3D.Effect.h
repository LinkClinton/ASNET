#pragma once

#include"ASNET.Graph.Direct3D.h"

//DirectX
#include<DirectXMath.h>

//std
#include<vector>

namespace ASNET {
	namespace Graph {
		namespace Direct3D {
			
			//Dir Light 
			struct DirLight {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;

				DirectX::XMFLOAT3 dir;
				
				float			  unsed;
				typedef std::vector<DirLight> Collections;
			};

			struct PointLight {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;

				DirectX::XMFLOAT3 pos;
				float			  range;

				DirectX::XMFLOAT3 att;

				float			  unused;
				typedef std::vector<PointLight> Collections;
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
				typedef SpotLight Collections[10];
			};

			struct Material {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular; //第四个元素是材质光滑
				typedef std::vector<Material> Collections;
			};

			class BasicEffect {
			private:
				bool EnableDirLight;
				bool EnableSpotLight;
				bool EnablePointLight;
				bool EnableTexture;

				static const int MaxLights = 10;
			private:
				Direct3D::DirLight::Collections			DirLights;
				Direct3D::SpotLight::Collections		SpotLights;
				Direct3D::PointLight::Collections		PointLights;

				Direct3D::ShaderDataBuffer*				DirLightBuffer;
			public:
				BasicEffect(ASNET::Graph::Direct3D::GraphDirect3D* graph);
			};


		}
	}
}
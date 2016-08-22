#pragma once

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
				
			};

			struct PointLight {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;

				DirectX::XMFLOAT3 pos;
				float			  range;

				DirectX::XMFLOAT3 att;

				float			  unused;
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
			};

			struct Material {
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular; //第四个元素是材质光滑
			};

			class BasicEffect {
				
			};


		}
	}
}
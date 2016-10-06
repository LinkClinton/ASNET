#pragma once

#include"ASNET.Graph.Direct3D.h"

//DirectX
#include<DirectXMath.h>

//std
#include<vector>

//Effect类，集成了部分着色器代码
//便于一些简单的特效的使用
//目前基本上就是光照了

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			//最大的光源数
			static const int MaxLights = 16;
			//最大的矩阵数量
			static const int MaxBoneAnimationMatrix = 200;


			//平行光
			struct DirLight {
				DirectX::XMFLOAT4 ambient; //环境光
				DirectX::XMFLOAT4 diffuse; //漫反射光
				DirectX::XMFLOAT4 specular; //镜面光

				DirectX::XMFLOAT3 dir; //方向
				
				float			  unsed; //用于内存对齐 
				typedef DirLight Collections[MaxLights];  //Collections
			};

			//点光源
			struct PointLight {
				DirectX::XMFLOAT4 ambient; //环境光
				DirectX::XMFLOAT4 diffuse; //漫反射光
				DirectX::XMFLOAT4 specular; //镜面光

				DirectX::XMFLOAT3 pos; //光源位置
				float			  range;  //光源范围

				DirectX::XMFLOAT3 att; //光源衰减系数

				float			  unused; //用于内存对齐
				typedef PointLight Collections[MaxLights]; //Collections
			};

			//
			struct SpotLight {
				DirectX::XMFLOAT4 ambient;  //环境光
				DirectX::XMFLOAT4 diffuse; //漫反射光
				DirectX::XMFLOAT4 specular; //镜面光
				
				DirectX::XMFLOAT3 dir; //方向
				float			  range; //范围

				DirectX::XMFLOAT3 pos; //位置
				float			  spot;

				DirectX::XMFLOAT3 att; //衰减
				float		      theta;
				typedef SpotLight Collections[MaxLights]; //Collections
			};

			struct Material {
				DirectX::XMFLOAT4 ambient; //对于环境光的反射 
				DirectX::XMFLOAT4 diffuse; //对于漫反射
				DirectX::XMFLOAT4 specular; //第四个元素是材质光滑
				Material() { 
					ambient = DirectX::XMFLOAT4(0, 0, 0, 1); 
					diffuse = DirectX::XMFLOAT4(0, 0, 0, 1);
					specular = DirectX::XMFLOAT4(0, 0, 0, 1);
				}
				typedef std::vector<Material> Collections; //Collections
			};

			//允许某种Effect使用
			enum class Enable {
				DirLight, 
				SpotLight,
				PointLight,
				Texture,
				Animation
			};

			//不允许某种Effect使用
			enum class UnEnable {
				DirLight,
				SpotLight,
				PointLight,
				Texture,
				Animaton
			};

			//简单的Effect类
			class BasicEffect {
			private:
				//某种特效状态
				struct StateEnable {
					int EnableDirLight; //平行光
					int EnableSpotLight; //聚光灯
					int EnablePointLight; //点光源
					int EnableTexture; //贴图
					int EnableAnimation; //是否支持动画
					int unused[3]; //内存对齐
					//构造函数
					StateEnable(); 
				};

				struct StateLights {
					int DirLightsState; //平行光使用状态
					int SpotLihtsState;  //聚光灯使用状态
					int PointLightsState;   //点光源使用状态
					int unused;   //内存对齐
					typedef StateLights Collections[16]; //Collections
					//构造函数
					StateLights();
				};

			private:
				bool                        EffectIsBegin; //Effect是否开启
				StateEnable					EffectState; //某种Effect是否开启
				StateLights::Collections	LightsState; //某个灯光是否开启
				Direct3D::ShaderDataBuffer* EffectStateBuffer; //EffectState缓存
				Direct3D::ShaderDataBuffer* LightsStateBuffer; //灯光状态缓存

				Direct3D::Shader*			EffectShader; //Effect自带的着色器
				Direct3D::GraphDirect3D*    ParentGraph; //渲染接口指针
				//将缓存更新给着色器
				void UpdateBufferToShader(); 
			private:
				Direct3D::DirLight::Collections			DirLights; //平行光
				Direct3D::SpotLight::Collections		SpotLights; //聚光灯
				Direct3D::PointLight::Collections		PointLights; //点光源

				Direct3D::ShaderDataBuffer*				MaterialBuffer; //设置的材质的缓存
				Direct3D::ShaderDataBuffer*				DirLightsBuffer; //平行光缓存
				Direct3D::ShaderDataBuffer*             SpotLightsBuffer; //聚光灯缓存
				Direct3D::ShaderDataBuffer*             PointLightsBuffer; //点光源缓存
			private:
				Direct3D::ShaderDataBuffer*				EyePosBuffer; //目前使用的摄像机的位置
				Direct3D::ShaderDataBuffer*             ProjMatrixBuffer; //投影矩阵缓存
				Direct3D::ShaderDataBuffer*             ViewMatrixBuffer; //视角矩阵缓存
				Direct3D::ShaderDataBuffer*				WorldMatrixBuffer; //世界矩阵缓存
				Direct3D::ShaderDataBuffer*             NormalMatrixBuffer; //法线变换矩阵缓存
				Direct3D::ShaderDataBuffer*             BoneAnimationMatrixBuffer; //骨骼动画变换矩阵缓存
				
				DirectX::XMFLOAT4X4                     BoneAnimationMatrix[MaxBoneAnimationMatrix]; //骨骼动画变换矩阵

				static DirectX::XMMATRIX Transpose(DirectX::CXMMATRIX matrix); //转置矩阵
				static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX matrix); //逆反矩阵
			public:
				//构造函数
				BasicEffect(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//析构函数
				~BasicEffect();
				//启用某种Effect
				void Enable(ASNET::Graph::Direct3D::Enable thing);
				//关闭某种Effect
				void UnEnable(ASNET::Graph::Direct3D::UnEnable thing);
				//开启某个平行光
				void DirLightOn(int which, 
					ASNET::Graph::Direct3D::DirLight dirlight);
				//关闭某个平行光
				void DirLightOff(int which);
				//开启某个聚光灯
				void SpotLightOn(int which,
					ASNET::Graph::Direct3D::SpotLight spotlight);
				//关闭某个聚光灯
				void SpotLightOff(int which);
				//开启某个点光源
				void PointLightOn(int which,
					ASNET::Graph::Direct3D::PointLight pointlight);
				//关闭某个点光源
				void PointLightOff(int which);
				//设置使用的材质
				void SetMaterial(ASNET::Graph::Direct3D::Material material);
				//设置使用的贴图
				void SetTexture(ASNET::Graph::Direct3D::Texture* texture);
				//设置投影矩阵
				void SetProjMatrix(DirectX::CXMMATRIX matrix);
				//设置视角矩阵
				void SetViewMatrix(DirectX::XMVECTOR eyepos, DirectX::XMVECTOR lookat);
				//设置世界变换矩阵
				void SetWorldMatrix(DirectX::CXMMATRIX matrix);
				//设置某个骨骼的动画矩阵
				void SetBoneAnimationMatrix(int which, DirectX::CXMMATRIX matrix);
				//设置所有的骨骼的动画矩阵
				void SetBoneAnimationMatrix(int start, std::vector<DirectX::XMFLOAT4X4> matrix);
				//开始使用，在使用之后着色器会被设置为Effect自带的着色器
				void EffectBegin(); //used the effect in this ,but the old shader can't be used
				//结束使用，在使用之后着色器会被设置为原本的着色器
				void EffectEnd(); //the old shader will be reused
			};
			
		


		}
	}
}
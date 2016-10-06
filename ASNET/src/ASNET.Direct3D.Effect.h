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

			//���Ĺ�Դ��
			static const int MaxLights = 16;
			//���ľ�������
			static const int MaxBoneAnimationMatrix = 200;


			//ƽ�й�
			struct DirLight {
				DirectX::XMFLOAT4 ambient; //������
				DirectX::XMFLOAT4 diffuse; //�������
				DirectX::XMFLOAT4 specular; //�����

				DirectX::XMFLOAT3 dir; //����
				
				float			  unsed; //�����ڴ���� 
				typedef DirLight Collections[MaxLights];  //Collections
			};

			//���Դ
			struct PointLight {
				DirectX::XMFLOAT4 ambient; //������
				DirectX::XMFLOAT4 diffuse; //�������
				DirectX::XMFLOAT4 specular; //�����

				DirectX::XMFLOAT3 pos; //��Դλ��
				float			  range;  //��Դ��Χ

				DirectX::XMFLOAT3 att; //��Դ˥��ϵ��

				float			  unused; //�����ڴ����
				typedef PointLight Collections[MaxLights]; //Collections
			};

			//
			struct SpotLight {
				DirectX::XMFLOAT4 ambient;  //������
				DirectX::XMFLOAT4 diffuse; //�������
				DirectX::XMFLOAT4 specular; //�����
				
				DirectX::XMFLOAT3 dir; //����
				float			  range; //��Χ

				DirectX::XMFLOAT3 pos; //λ��
				float			  spot;

				DirectX::XMFLOAT3 att; //˥��
				float		      theta;
				typedef SpotLight Collections[MaxLights]; //Collections
			};

			struct Material {
				DirectX::XMFLOAT4 ambient; //���ڻ�����ķ��� 
				DirectX::XMFLOAT4 diffuse; //����������
				DirectX::XMFLOAT4 specular; //���ĸ�Ԫ���ǲ��ʹ⻬
				Material() { 
					ambient = DirectX::XMFLOAT4(0, 0, 0, 1); 
					diffuse = DirectX::XMFLOAT4(0, 0, 0, 1);
					specular = DirectX::XMFLOAT4(0, 0, 0, 1);
				}
				typedef std::vector<Material> Collections; //Collections
			};

			//����ĳ��Effectʹ��
			enum class Enable {
				DirLight, 
				SpotLight,
				PointLight,
				Texture,
				Animation
			};

			//������ĳ��Effectʹ��
			enum class UnEnable {
				DirLight,
				SpotLight,
				PointLight,
				Texture,
				Animaton
			};

			//�򵥵�Effect��
			class BasicEffect {
			private:
				//ĳ����Ч״̬
				struct StateEnable {
					int EnableDirLight; //ƽ�й�
					int EnableSpotLight; //�۹��
					int EnablePointLight; //���Դ
					int EnableTexture; //��ͼ
					int EnableAnimation; //�Ƿ�֧�ֶ���
					int unused[3]; //�ڴ����
					//���캯��
					StateEnable(); 
				};

				struct StateLights {
					int DirLightsState; //ƽ�й�ʹ��״̬
					int SpotLihtsState;  //�۹��ʹ��״̬
					int PointLightsState;   //���Դʹ��״̬
					int unused;   //�ڴ����
					typedef StateLights Collections[16]; //Collections
					//���캯��
					StateLights();
				};

			private:
				bool                        EffectIsBegin; //Effect�Ƿ���
				StateEnable					EffectState; //ĳ��Effect�Ƿ���
				StateLights::Collections	LightsState; //ĳ���ƹ��Ƿ���
				Direct3D::ShaderDataBuffer* EffectStateBuffer; //EffectState����
				Direct3D::ShaderDataBuffer* LightsStateBuffer; //�ƹ�״̬����

				Direct3D::Shader*			EffectShader; //Effect�Դ�����ɫ��
				Direct3D::GraphDirect3D*    ParentGraph; //��Ⱦ�ӿ�ָ��
				//��������¸���ɫ��
				void UpdateBufferToShader(); 
			private:
				Direct3D::DirLight::Collections			DirLights; //ƽ�й�
				Direct3D::SpotLight::Collections		SpotLights; //�۹��
				Direct3D::PointLight::Collections		PointLights; //���Դ

				Direct3D::ShaderDataBuffer*				MaterialBuffer; //���õĲ��ʵĻ���
				Direct3D::ShaderDataBuffer*				DirLightsBuffer; //ƽ�й⻺��
				Direct3D::ShaderDataBuffer*             SpotLightsBuffer; //�۹�ƻ���
				Direct3D::ShaderDataBuffer*             PointLightsBuffer; //���Դ����
			private:
				Direct3D::ShaderDataBuffer*				EyePosBuffer; //Ŀǰʹ�õ��������λ��
				Direct3D::ShaderDataBuffer*             ProjMatrixBuffer; //ͶӰ���󻺴�
				Direct3D::ShaderDataBuffer*             ViewMatrixBuffer; //�ӽǾ��󻺴�
				Direct3D::ShaderDataBuffer*				WorldMatrixBuffer; //������󻺴�
				Direct3D::ShaderDataBuffer*             NormalMatrixBuffer; //���߱任���󻺴�
				Direct3D::ShaderDataBuffer*             BoneAnimationMatrixBuffer; //���������任���󻺴�
				
				DirectX::XMFLOAT4X4                     BoneAnimationMatrix[MaxBoneAnimationMatrix]; //���������任����

				static DirectX::XMMATRIX Transpose(DirectX::CXMMATRIX matrix); //ת�þ���
				static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX matrix); //�淴����
			public:
				//���캯��
				BasicEffect(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//��������
				~BasicEffect();
				//����ĳ��Effect
				void Enable(ASNET::Graph::Direct3D::Enable thing);
				//�ر�ĳ��Effect
				void UnEnable(ASNET::Graph::Direct3D::UnEnable thing);
				//����ĳ��ƽ�й�
				void DirLightOn(int which, 
					ASNET::Graph::Direct3D::DirLight dirlight);
				//�ر�ĳ��ƽ�й�
				void DirLightOff(int which);
				//����ĳ���۹��
				void SpotLightOn(int which,
					ASNET::Graph::Direct3D::SpotLight spotlight);
				//�ر�ĳ���۹��
				void SpotLightOff(int which);
				//����ĳ�����Դ
				void PointLightOn(int which,
					ASNET::Graph::Direct3D::PointLight pointlight);
				//�ر�ĳ�����Դ
				void PointLightOff(int which);
				//����ʹ�õĲ���
				void SetMaterial(ASNET::Graph::Direct3D::Material material);
				//����ʹ�õ���ͼ
				void SetTexture(ASNET::Graph::Direct3D::Texture* texture);
				//����ͶӰ����
				void SetProjMatrix(DirectX::CXMMATRIX matrix);
				//�����ӽǾ���
				void SetViewMatrix(DirectX::XMVECTOR eyepos, DirectX::XMVECTOR lookat);
				//��������任����
				void SetWorldMatrix(DirectX::CXMMATRIX matrix);
				//����ĳ�������Ķ�������
				void SetBoneAnimationMatrix(int which, DirectX::CXMMATRIX matrix);
				//�������еĹ����Ķ�������
				void SetBoneAnimationMatrix(int start, std::vector<DirectX::XMFLOAT4X4> matrix);
				//��ʼʹ�ã���ʹ��֮����ɫ���ᱻ����ΪEffect�Դ�����ɫ��
				void EffectBegin(); //used the effect in this ,but the old shader can't be used
				//����ʹ�ã���ʹ��֮����ɫ���ᱻ����Ϊԭ������ɫ��
				void EffectEnd(); //the old shader will be reused
			};
			
		


		}
	}
}
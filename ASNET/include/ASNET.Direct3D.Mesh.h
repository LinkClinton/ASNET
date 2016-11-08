#pragma once

#include"ASNET.Graph.Direct3D.h"
#include"ASNET.Direct3D.Effect.h"

#include<fstream>
#include<map>

/*
* mesh��ʽ����Ϊģ�͵Ļ��������õ�
* ���ģ�͵Ķ�����Ϣ������ͼ��Ϣ
* �Լ�֧�ֻ���ģ��
*/

namespace ASNET {
	namespace Graph {
		namespace Direct3D {

			
			//MeshPart����
			class MeshPart {
			public:
				Direct3D::Material Material; //������Ϣ
				
				
				UINT TextureID; //ʹ�õ���ͼID
				UINT StartFace; //������ʼ��λ��
				UINT EffectCount; //���õ���������
				
				Direct3D::Texture* Texture; //��ͼ

				std::wstring MeshPartName; //����

				friend class Mesh;
				friend class Model;
			public:
				//���캯��
				MeshPart();
				//��������
				~MeshPart();
			};

			//Mesh��
			class Mesh {
			protected:
				Direct3D::GraphDirect3D*				ParentGraph; //��Ⱦ��ָ��ӿ�

				Direct3D::Buffer*						Buffer; //����

				UINT VertexCount; //�������
				UINT IndexCount; //��������
				UINT TextureCount; //��ͼ����
				UINT MeshPartCount; //ģ�Ͳ��ָ���

				std::vector<Direct3D::Vertex>			vertices; //����
				std::vector<Direct3D::Index>			indices; //����
				std::vector<Direct3D::MeshPart>			MeshParts; //MeshPart

				std::vector<Direct3D::Texture*>		    Textures; //��ͼ

				friend class Direct3DModelLoader;
			public:
				//���캯����ֻ��Ϊ�˼̳�����
				Mesh();
				//���캯��
				Mesh(ASNET::Graph::Direct3D::GraphDirect3D* graph);
				//��������
				~Mesh();
				//�������ģ��
				void Draw(UINT texture_id = 0); //the used texture_id in the shader
				//ͨ��ʹ��Effect�������ģ��
				void Draw(ASNET::Graph::Direct3D::BasicEffect* effect, bool TextureEnable = true);
				//����ģ��Ҫ����׼��
				void PrepareDraw(); 
				//����ģ�͵�ĳ������
				void DrawPart(UINT index);

				//����Part�ĸ���
				auto Parts()->int; 


				//�ͷ���Դ
				void Release();


			};



		}
	}
}
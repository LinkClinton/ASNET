#pragma once
#include"ASNET.Graph.Direct3D.h"

/*
* �򵥵�����Ĵ���
* ����Grid��Cube�Ĵ���
*/

namespace ASNET {
	namespace Graph {
		namespace Direct3D {
			
			//�򵥵�GeometryMesh��
			class GeometryMesh {
			private:
				ASNET::Graph::Direct3D::Buffer*             buffer; //Mesh����
				friend class GeometryMaker;
			public:
				//���캯��
				GeometryMesh();
				//��������
				~GeometryMesh();
				
				std::vector<ASNET::Graph::Direct3D::Vertex> vertices; //����
				std::vector<ASNET::Graph::Direct3D::Index>  indices; //����
				

				operator ASNET::Graph::Direct3D::Buffer*&(); //�����仺������

			};


			class GeometryMaker {
			private:
			public:
				//����Grid��������������
				static void CreateGrid(ASNET::Graph::Direct3D::GeometryMesh &mesh,
					float width, float depth, UINT dx, UINT dz);
				
				//����Grid
				static void CreateGrid(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Direct3D::Buffer* &buffer,
					float width, float depth, UINT dx, UINT dz,
					bool CPUAcess = false);
				
				//����Cube��������������
				static void CreateBox(ASNET::Graph::Direct3D::GeometryMesh &mesh,
					float width, float height, float depth);
				
				//����Cube
				static void CreateBox(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Direct3D::Buffer* &buffer,
					float width, float height, float depth,
					bool CPUAcess = false);


			};

		}
	}
}
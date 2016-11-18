#pragma once
#include"ASNET.Graph.Direct3D.h"

/*
* 简单的物体的创建
* 比如Grid和Cube的创建
*/

namespace ASNET {
	namespace Graph {
		namespace Direct3D {
			
			//简单的GeometryMesh类
			class GeometryMesh {
			private:
				ASNET::Graph::Direct3D::Buffer*             buffer; //Mesh缓存
				friend class GeometryMaker;
			public:
				//构造函数
				GeometryMesh();
				//析构函数
				~GeometryMesh();
				
				std::vector<ASNET::Graph::Direct3D::Vertex> vertices; //顶点
				std::vector<ASNET::Graph::Direct3D::Index>  indices; //索引
				

				operator ASNET::Graph::Direct3D::Buffer*&(); //返回其缓存数据

			};


			class GeometryMaker {
			private:
			public:
				//创建Grid，但不创建缓存
				static void CreateGrid(ASNET::Graph::Direct3D::GeometryMesh &mesh,
					float width, float depth, UINT dx, UINT dz);
				
				//创建Grid
				static void CreateGrid(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Direct3D::Buffer* &buffer,
					float width, float depth, UINT dx, UINT dz,
					bool CPUAcess = false);
				
				//创建Cube，但不创建缓存
				static void CreateBox(ASNET::Graph::Direct3D::GeometryMesh &mesh,
					float width, float height, float depth);
				
				//创建Cube
				static void CreateBox(ASNET::Graph::Direct3D::GraphDirect3D* graph,
					ASNET::Graph::Direct3D::Buffer* &buffer,
					float width, float height, float depth,
					bool CPUAcess = false);


			};

		}
	}
}
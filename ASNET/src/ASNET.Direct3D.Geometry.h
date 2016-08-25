#pragma once
#include"ASNET.Graph.Direct3D.h"

namespace ASNET {
	namespace Graph {
		namespace Direct3D {
			
			class GeometryMesh {
			private:
				ASNET::Graph::Direct3D::Buffer*             buffer;
				friend class GeometryMaker;
			public:
				GeometryMesh();
				~GeometryMesh();
				std::vector<ASNET::Graph::Direct3D::Vertex> vertices;
				std::vector<ASNET::Graph::Direct3D::Index>  indices;
				

				operator ASNET::Graph::Direct3D::Buffer*&();

			};


			class GeometryMaker {
			private:
			public:
				static void MakeGrid(ASNET::Graph::Direct3D::GeometryMesh &mesh,
					float width, float depth, UINT dx, UINT dz);

			};

		}
	}
}
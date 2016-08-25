#include "ASNET.Direct3D.Geometry.h"

ASNET::Graph::Direct3D::GeometryMesh::GeometryMesh(){

	buffer = nullptr;
	vertices.clear();
	indices.clear();
}


ASNET::Graph::Direct3D::GeometryMesh::~GeometryMesh(){
	if (buffer) {
		delete buffer;
		buffer = nullptr;

	}
	vertices.clear();
	indices.clear();
}

ASNET::Graph::Direct3D::GeometryMesh::operator ASNET::Graph::Direct3D::Buffer*&(){
	return buffer;
}

void ASNET::Graph::Direct3D::GeometryMaker::MakeGrid(
	ASNET::Graph::Direct3D::GeometryMesh & mesh,
	float width, float depth, UINT dx, UINT dz){
	UINT VertexCount = dx*dz;
	UINT FaceCount = (dx - 1)*(dz - 1) * 2;
	
	float HalfWidth = 0.5f*width;
	float Halfdepth = 0.5f*depth;

	float Dx = width / (dx - 1);
	float Dz = depth / (dz - 1);

	float Du = 1.0f / (dx - 1);
	float Dv = 1.0f / (dz - 1);

	mesh.vertices.resize(VertexCount);
	for (UINT i = 0; i < dz; i++) {
		float z = Halfdepth - i*Dz;
		for (UINT j = 0; j < dx; j++) {
			float x = -HalfWidth + j*Dx;
			int index = i*dx + j;
			mesh.vertices[index] = ASNET::Graph::Direct3D::Vertex(x, 0.f, z, j*Du, i*Dv);
			mesh.vertices[index].Normal(0.f, 1.f, 0.f);
			mesh.vertices[index].Color(1, 1, 1, 1);
		}
	}

	UINT index = 0;
	mesh.indices.resize(FaceCount * 3);

	for (UINT i = 0; i < dz - 1; i++) {
		for (UINT j = 0; j < dx - 1; j++) {
			mesh.indices[index] = i*dx + j;
			mesh.indices[index + 1] = i*dx + j + 1;
			mesh.indices[index + 2] = (i + 1)*dx + j;

			mesh.indices[index + 3] = (i + 1)*dx + j;
			mesh.indices[index + 4] = i*dx + j + 1;
			mesh.indices[index + 5] = (i + 1)*dx + j + 1;

			index += 6;
		}
	}
}

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

void ASNET::Graph::Direct3D::GeometryMaker::CreateGrid(
	ASNET::Graph::Direct3D::GeometryMesh & mesh,
	float width, float depth, UINT dx, UINT dz,
	ASNET::Graph::Color color) {
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
			mesh.vertices[index].Color(color.x, color.y, color.z, color.w);
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

void ASNET::Graph::Direct3D::GeometryMaker::CreateGrid(
	ASNET::Graph::Direct3D::GraphDirect3D * graph,
	ASNET::Graph::Direct3D::Buffer * &buffer,
	float width, float depth, UINT dx, UINT dz,
	ASNET::Graph::Color color, bool CPUAcess) {
	ASNET::Graph::Direct3D::GeometryMesh mesh;
	CreateGrid(mesh, width, depth, dx, dz, color);

	graph->LoadBuffer(buffer, mesh.vertices, mesh.indices, CPUAcess);

}

void ASNET::Graph::Direct3D::GeometryMaker::CreateBox(
	ASNET::Graph::Direct3D::GeometryMesh & mesh,
	float width, float height, float depth){

	mesh.vertices.resize(24);

	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;

	mesh.vertices[0] = ASNET::Graph::Direct3D::Vertex(-w2, -h2, -d2, 0.0f, 1.0f);
	mesh.vertices[1] = ASNET::Graph::Direct3D::Vertex(-w2, +h2, -d2, 0.0f, 0.0f);
	mesh.vertices[2] = ASNET::Graph::Direct3D::Vertex(+w2, +h2, -d2, 1.0f, 0.0f);
	mesh.vertices[3] = ASNET::Graph::Direct3D::Vertex(+w2, -h2, -d2, 1.0f, 1.0f);

	mesh.vertices[4] = ASNET::Graph::Direct3D::Vertex(-w2, -h2, +d2, 1.0f, 1.0f);
	mesh.vertices[5] = ASNET::Graph::Direct3D::Vertex(+w2, -h2, +d2, 0.0f, 1.0f);
	mesh.vertices[6] = ASNET::Graph::Direct3D::Vertex(+w2, +h2, +d2, 0.0f, 0.0f);
	mesh.vertices[7] = ASNET::Graph::Direct3D::Vertex(-w2, +h2, +d2, 1.0f, 0.0f);

	mesh.vertices[8] = ASNET::Graph::Direct3D::Vertex(-w2, +h2, -d2, 0.0f, 1.0f);
	mesh.vertices[9] = ASNET::Graph::Direct3D::Vertex(-w2, +h2, +d2, 0.0f, 0.0f);
	mesh.vertices[10] = ASNET::Graph::Direct3D::Vertex(+w2, +h2, +d2, 1.0f, 0.0f);
	mesh.vertices[11] = ASNET::Graph::Direct3D::Vertex(+w2, +h2, -d2, 1.0f, 1.0f);

	mesh.vertices[12] = ASNET::Graph::Direct3D::Vertex(-w2, -h2, -d2, 1.0f, 1.0f);
	mesh.vertices[13] = ASNET::Graph::Direct3D::Vertex(+w2, -h2, -d2, 0.0f, 1.0f);
	mesh.vertices[14] = ASNET::Graph::Direct3D::Vertex(+w2, -h2, +d2, 0.0f, 0.0f);
	mesh.vertices[15] = ASNET::Graph::Direct3D::Vertex(-w2, -h2, +d2, 1.0f, 0.0f);

	mesh.vertices[16] = ASNET::Graph::Direct3D::Vertex(-w2, -h2, +d2, 0.0f, 1.0f);
	mesh.vertices[17] = ASNET::Graph::Direct3D::Vertex(-w2, +h2, +d2, 0.0f, 0.0f);
	mesh.vertices[18] = ASNET::Graph::Direct3D::Vertex(-w2, +h2, -d2, 1.0f, 0.0f);
	mesh.vertices[19] = ASNET::Graph::Direct3D::Vertex(-w2, -h2, -d2, 1.0f, 1.0f);

	mesh.vertices[20] = ASNET::Graph::Direct3D::Vertex(+w2, -h2, -d2, 0.0f, 1.0f);
	mesh.vertices[21] = ASNET::Graph::Direct3D::Vertex(+w2, +h2, -d2, 0.0f, 0.0f);
	mesh.vertices[22] = ASNET::Graph::Direct3D::Vertex(+w2, +h2, +d2, 1.0f, 0.0f);
	mesh.vertices[23] = ASNET::Graph::Direct3D::Vertex(+w2, -h2, +d2, 1.0f, 1.0f);

	mesh.indices.resize(36);

	mesh.indices =
	{ 0,1,2,0,2,3,
	4,5,6,4,6,7,
	8,9,10,8,10,11,
	12,13,14,12,14,15,
	16,17,18,16,18,19,
	20,21,22,20,22,23 };


}

void ASNET::Graph::Direct3D::GeometryMaker::CreateBox(
	ASNET::Graph::Direct3D::GraphDirect3D * graph,
	ASNET::Graph::Direct3D::Buffer * &buffer, 
	float width, float height, float depth, bool CPUAcess){
	ASNET::Graph::Direct3D::GeometryMesh mesh;
	CreateBox(mesh, width, height, depth);

	graph->LoadBuffer(buffer, mesh.vertices, mesh.indices, CPUAcess);
}

#include "ASNET.Direct3D.Mesh.h"

ASNET::Graph::Direct3D::MeshPart::MeshPart(){
	TextureID = 0;
	StartFace = 0;
	EffectCount = 0;

	Texture = nullptr;
}

ASNET::Graph::Direct3D::MeshPart::~MeshPart(){

	TextureID = 0;
	StartFace = 0;
	EffectCount = 0;

	Texture = nullptr;

}



ASNET::Graph::Direct3D::Mesh::Mesh(){
	Buffer = nullptr;
	VertexCount = 0;
	IndexCount = 0;
	MeshPartCount = 0;

	vertices.clear();
	indices.clear();
	MeshParts.clear();

	Textures.clear();
}

ASNET::Graph::Direct3D::Mesh::Mesh(
	ASNET::Graph::Direct3D::GraphDirect3D * graph){
	ParentGraph = graph;
	
	Buffer = nullptr;
	VertexCount = 0;
	IndexCount = 0;
	MeshPartCount = 0;

	vertices.clear();
	indices.clear();
	MeshParts.clear();

	Textures.clear();

}

ASNET::Graph::Direct3D::Mesh::~Mesh(){
	ParentGraph = nullptr;

	delete Buffer;

	VertexCount = 0;
	IndexCount = 0;
	MeshPartCount = 0;

	vertices.clear();
	indices.clear();
	MeshParts.clear();

	for (UINT i = 0; i < Textures.size(); i++) {
		delete Textures[i];
		Textures[i] = nullptr;
	}
	Textures.clear();
}

void ASNET::Graph::Direct3D::Mesh::Draw(UINT texture_id){
	PrepareDraw();

	for (UINT i = 0; i < MeshPartCount; i++) {
		if (MeshParts[i].Texture)
			ParentGraph->UsedShader->SendTextureToShader(texture_id, MeshParts[i].Texture);
		DrawPart(i);
	}

}

void ASNET::Graph::Direct3D::Mesh::Draw(
	ASNET::Graph::Direct3D::BasicEffect * effect,
	bool TextureEnable) {
	PrepareDraw();
	for (UINT i = 0; i < MeshPartCount; i++) {
		if (TextureEnable) {
			if (MeshParts[i].Texture) {
				effect->Enable(ASNET::Graph::Direct3D::Enable::Texture);
				effect->SetTexture(MeshParts[i].Texture);
			}
			else effect->UnEnable(ASNET::Graph::Direct3D::UnEnable::Texture);
		}
		effect->SetMaterial(MeshParts[i].Material);
		DrawPart(i);
	}
}



void ASNET::Graph::Direct3D::Mesh::PrepareDraw(){
	ParentGraph->g_devicecontext3d->IASetInputLayout(ParentGraph->InputLayout);
	UINT stride = sizeof(Direct3D::Vertex);
	UINT offset = 0;

	ParentGraph->g_devicecontext3d->IASetVertexBuffers(0, 1, &Buffer->VertexBuffer, &stride, &offset);
	ParentGraph->g_devicecontext3d->IASetIndexBuffer(Buffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	ParentGraph->g_devicecontext3d->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ASNET::Graph::Direct3D::Mesh::DrawPart(UINT index){
	ParentGraph->g_devicecontext3d->DrawIndexed(MeshParts[index].EffectCount,
		MeshParts[index].StartFace, 0);
}

auto ASNET::Graph::Direct3D::Mesh::Parts() -> int{
	return MeshPartCount;
}

void ASNET::Graph::Direct3D::Mesh::Release(){
	ParentGraph = nullptr;

	delete Buffer;

	VertexCount = 0;
	IndexCount = 0;
	MeshPartCount = 0;

	vertices.clear();
	indices.clear();
	MeshParts.clear();

	for (UINT i = 0; i < Textures.size(); i++) {
		delete Textures[i];
		Textures[i] = nullptr;
	}
	Textures.clear();
}


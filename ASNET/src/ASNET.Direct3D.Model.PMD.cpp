#include "ASNET.Direct3D.Model.PMD.h"



float ASNET::Graph::Direct3D::PMDModel::PMDFloatRead(std::ifstream*  file){
	PMDFloat Float;
	for (int i = 0; i < 4; i++)
		file->get(Float._char[i]);
	return Float._float;
}

short ASNET::Graph::Direct3D::PMDModel::PMDShortRead(std::ifstream * file){
	PMDShort Short;
	for (int i = 0; i < 2; i++)
		file->get(Short._char[i]);
	return Short._short;
}

DWORD ASNET::Graph::Direct3D::PMDModel::PMDDwordRead(std::ifstream * file){
	PMDDword Dword;
	for (int i = 0; i < 4; i++)
		file->get(Dword._char[i]);
	return Dword._Dwrod;
}

WORD ASNET::Graph::Direct3D::PMDModel::PMDWordRead(std::ifstream * file){
	PMDWord Word;
	for (int i = 0; i < 2; i++)
		file->get(Word._char[i]);
	return Word._Word;
}



void ASNET::Graph::Direct3D::PMDModel::PMDRuleOut(std::ifstream * file, int num) {
	char c;
	for (int i = 0; i < num; i++)
		file->get(c);
}

ASNET::Graph::Direct3D::PMDModel::~PMDModel(){
	ParentGraph = nullptr;
	delete Buffer;

	VertexNum = 0;
	IndexNum = 0;
	ModelPartsNum = 0;
	vertices.clear();
	indices.clear();
	ModelParts.clear();
	
}

void ASNET::Graph::Direct3D::PMDModel::Draw(int texture_id){
	ParentGraph->g_devicecontext3d->IASetInputLayout(ParentGraph->InputLayout);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ParentGraph->g_devicecontext3d->IASetVertexBuffers(0, 1, &Buffer->VertexBuffer, &stride, &offset);
	ParentGraph->g_devicecontext3d->IASetIndexBuffer(Buffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	ParentGraph->g_devicecontext3d->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (UINT i = 0; i < ModelPartsNum; i++) {
		ParentGraph->UsedShader->SendTextureToShader(texture_id, ModelParts[i].Texture);
		DrawPart(i);
	}

	
}

void ASNET::Graph::Direct3D::PMDModel::PrepareDraw(){
	ParentGraph->g_devicecontext3d->IASetInputLayout(ParentGraph->InputLayout);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ParentGraph->g_devicecontext3d->IASetVertexBuffers(0, 1, &Buffer->VertexBuffer, &stride, &offset);
	ParentGraph->g_devicecontext3d->IASetIndexBuffer(Buffer->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	ParentGraph->g_devicecontext3d->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ASNET::Graph::Direct3D::PMDModel::DrawPart(int index){
	ParentGraph->g_devicecontext3d->DrawIndexed(ModelParts[index].EffectCount,
		ModelParts[index].StartFace, 0);
}

auto ASNET::Graph::Direct3D::PMDModel::ModelPatsNum() -> int{
	return ModelPartsNum;
}

void ASNET::Graph::Direct3D::PMDModel::Release(){
	ParentGraph = nullptr;
	Buffer->~Buffer();

	VertexNum = 0;
	IndexNum = 0;
	ModelPartsNum = 0;
	vertices.clear();
	indices.clear();
	ModelParts.clear();
	
}

ASNET::Graph::Direct3D::PMDModelPart::operator ASNET::Graph::Direct3D::Material(){
	ASNET::Graph::Direct3D::Material material;
	material.ambient = Ambient;
	material.diffuse = Diffuse;
	material.specular = Specular;
	return material;
}

ASNET::Graph::Direct3D::PMDModelPart::PMDModelPart(){
	Ambient = { 0,0,0,0 };
	Diffuse = { 0,0,0,0 };
	Specular = { 0,0,0,0 };

	Alphadif = 0;
	Spemat = 0;

	TextureName.clear();


	StartFace = 0;
	EffectCount = 0;
	TextureID = 0;
	Texture = nullptr;

}

ASNET::Graph::Direct3D::PMDModelPart::~PMDModelPart(){
	Ambient = { 0,0,0,0 };
	Diffuse = { 0,0,0,0 };
	Specular = { 0,0,0,0 };

	Alphadif = 0;
	Spemat = 0;

	TextureName.clear();
	

	StartFace = 0;
	EffectCount = 0;
	TextureID = 0;
	delete Texture;
}

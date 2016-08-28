#include "ASNET.Direct3D.Model.h"

ASNET::Graph::Direct3D::Value ASNET::Graph::Direct3D::Direct3DModelLoader::ValueRead(
	std::ifstream * file, UINT size) {
	ASNET::Graph::Direct3D::Value value;
	memset(value._char, 0, sizeof(value._char));
	for (UINT i = 0; i < size; i++)
		file->get(value._char[i]);
	return value;
}

void ASNET::Graph::Direct3D::Direct3DModelLoader::ValueRuleOut(
	std::ifstream * file, UINT size){
	char c;
	for (UINT i = 0; i < size; i++)
		file->get(c);
}

void ASNET::Graph::Direct3D::Direct3DModelLoader::StringRead(
	std::ifstream * file, std::wstring &str){
	UINT size = ValueRead(file, 4)._int;
	for (UINT i = 0; i < size; i++)
		str.push_back(file->get());
}

void ASNET::Graph::Direct3D::Direct3DModelLoader::WideStringRead(
	std::ifstream * file, std::wstring & str){
	UINT size = ValueRead(file, 4)._int;
	size = size / 2;
	for (UINT i = 0; i < size; i++) {
		Value value;
		memset(value._char, 0, sizeof(value._char));
		for (UINT j = 0; j < 2; j++)
			file->get(value._char[j]);
		str.push_back(value._wchar[0]);
	}
}

void ASNET::Graph::Direct3D::Direct3DModelLoader::LoadPMXModel(
	ASNET::Graph::Direct3D::GraphDirect3D * graph,
	ASNET::Graph::Word filename, ASNET::Graph::Direct3D::Model *& model) {
	if (model) return;
	model = new ASNET::Graph::Direct3D::Model(graph);

	//model value size information
	bool IsCodingUTF16 = false;
	byte VertexIndexSize = 0;
	byte TextureIndexSize = 0;
	byte ModelPartIndexSize = 0;
	byte BoneIndexSize;
	byte AppUVCount = 0;

	//model name and comment
	std::wstring ModelName;
	std::wstring ModelComment;

	//texture path
	std::wstring  FilePath;
	UINT StrLen = wcslen(filename);
	UINT Last = 0;
	for (UINT i = 0; i < StrLen; i++)
		if (filename[i] == '/') Last = i;
	for (UINT i = 0; i < Last; i++)
		FilePath.push_back(filename[i]);
	FilePath.push_back('/');

	std::ifstream in_file;
	//open file
	in_file.open(filename, std::ios::binary);

	//__________________________
	//Header
	//__________________________

	ValueRead(&in_file, 4); //the information is "PMX "

	float version = ValueRead(&in_file, 4)._float; //the value of float is 2.0

	ValueRead(&in_file, 1); //the value byte of length?

	if (ValueRead(&in_file, 1)._byte[0] == 0) IsCodingUTF16 = true;
	else IsCodingUTF16 = false;
	


	AppUVCount = ValueRead(&in_file, 1)._byte[0]; //the byte of appUVcnt

	VertexIndexSize = ValueRead(&in_file, 1)._byte[0]; //index valuee's size?

	TextureIndexSize = ValueRead(&in_file, 1)._byte[0]; //texture id's size?

	ModelPartIndexSize = ValueRead(&in_file, 1)._byte[0]; //modelparts's size?

	BoneIndexSize = ValueRead(&in_file, 1)._byte[0]; //bone's size?

	ValueRead(&in_file, 1); //morph's size?

	ValueRead(&in_file, 1); //rigidBody's size?
	
	if (!IsCodingUTF16) {
		StringRead(&in_file, ModelName); //Model Name

		StringRead(&in_file, ModelComment); //Model Comment

		StringRead(&in_file, model->ModelName); //English Name

		StringRead(&in_file, model->ModelComment); //English Comment 
	}
	else {
		WideStringRead(&in_file, ModelName); //Model Name

		WideStringRead(&in_file, ModelComment); //Model Comment

		WideStringRead(&in_file, model->ModelName); //English Name

		WideStringRead(&in_file, model->ModelComment); //English Comment 
	}

	//__________________________
	//Vertex
	//__________________________
	
	model->VertexCount = ValueRead(&in_file, 4)._int;

	model->vertices.resize(model->VertexCount);

	for (UINT i = 0; i < model->VertexCount; i++) {
		model->vertices[i].x = ValueRead(&in_file, 4)._float;
		model->vertices[i].y = ValueRead(&in_file, 4)._float;
		model->vertices[i].z = ValueRead(&in_file, 4)._float;
		model->vertices[i].nx = ValueRead(&in_file, 4)._float;
		model->vertices[i].ny = ValueRead(&in_file, 4)._float;
		model->vertices[i].nz = ValueRead(&in_file, 4)._float;
		model->vertices[i].u = ValueRead(&in_file, 4)._float;
		model->vertices[i].v = ValueRead(&in_file, 4)._float;

		for (UINT i = 0; i < AppUVCount; i++) {
			ValueRead(&in_file, 4);
			ValueRead(&in_file, 4);
			ValueRead(&in_file, 4);
			ValueRead(&in_file, 4); //appuv?
		}

		byte WeightType = ValueRead(&in_file, 1)._byte[0];

		switch (WeightType) {
		case 0: { //BDEF 1
			ValueRead(&in_file, BoneIndexSize); //Bone1
			//Weight = 1;
			break;
		}
		case 1: { //BDEF2 
			ValueRead(&in_file, BoneIndexSize); //Bone1-2
			ValueRead(&in_file, BoneIndexSize);
			ValueRead(&in_file, 4)._float; //weight 1?
			//weight2 = 1 - weight1; ?
			break;
		}
		case 2: { //BDEF4
			ValueRead(&in_file, BoneIndexSize); //Bone1-4
			ValueRead(&in_file, BoneIndexSize);
			ValueRead(&in_file, BoneIndexSize);
			ValueRead(&in_file, BoneIndexSize);
			ValueRead(&in_file, 4)._float; //Weight1-4
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			break;
		}
		case 4: { //SDEF
			ValueRead(&in_file, BoneIndexSize); //Bone1-2
			ValueRead(&in_file, BoneIndexSize);
			ValueRead(&in_file, 4)._float; //Weight1
			//Weight2 = 1 - Weight1;
			ValueRead(&in_file, 4)._float; //the CX,CY,CZ...?
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			ValueRead(&in_file, 4)._float;
			break;
		}
		default:
			break;
		}
		ValueRead(&in_file, 4)._float; //Edge Scale
	}

	//__________________________
	//Index 
	//__________________________

	model->IndexCount = ValueRead(&in_file, 4)._int;

	for (UINT i = 0; i < model->IndexCount; i++)
		model->indices.push_back(ValueRead(&in_file, VertexIndexSize)._int);

	//__________________________
	//Texture
	//__________________________

	model->TextureCount = ValueRead(&in_file, 4)._int;

	for (UINT i = 0; i < model->TextureCount; i++) {
		std::wstring TextureName = FilePath;
		Direct3D::Texture* Texture = nullptr;

		if (IsCodingUTF16)
			WideStringRead(&in_file, TextureName);
		else StringRead(&in_file, TextureName);

		graph->LoadTexture(Texture, &TextureName[0]);
		model->Textures.push_back(Texture);
	}

	//__________________________
	//MeshPart
	//__________________________

	model->MeshPartCount = ValueRead(&in_file, 4)._int;

	model->MeshParts.resize(model->MeshPartCount);

	UINT NowStartFace = 0;

	for (UINT i = 0; i < model->MeshPartCount; i++) {
		std::wstring ModelPartName;
		std::wstring memo;
		byte toonflg = 0;
		if (IsCodingUTF16)
			WideStringRead(&in_file, ModelPartName);
		else StringRead(&in_file, ModelPartName);

		if (IsCodingUTF16)
			WideStringRead(&in_file, model->MeshParts[i].MeshPartName);
		else StringRead(&in_file, model->MeshParts[i].MeshPartName); //English Name

		model->MeshParts[i].Material.diffuse.x = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.diffuse.y = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.diffuse.z = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.diffuse.w = ValueRead(&in_file, 4)._float;

		model->MeshParts[i].Material.specular.x = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.specular.y = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.specular.z = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.specular.w = ValueRead(&in_file, 4)._float;

		model->MeshParts[i].Material.ambient.x = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.ambient.y = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.ambient.z = ValueRead(&in_file, 4)._float;
		model->MeshParts[i].Material.ambient.w = 0.0f;

		ValueRead(&in_file, 1)._byte[0]; //draw flg?

		ValueRead(&in_file, 4)._float; //edge color?
		ValueRead(&in_file, 4)._float;
		ValueRead(&in_file, 4)._float;
		ValueRead(&in_file, 4)._float;

		ValueRead(&in_file, 4)._float; //edge size?

		model->MeshParts[i].TextureID = ValueRead(&in_file, TextureIndexSize)._int;
		if (model->MeshParts[i].TextureID < model->TextureCount)
			model->MeshParts[i].Texture = model->Textures[model->MeshParts[i].TextureID];
		

		ValueRead(&in_file, TextureIndexSize)._int; //sph?

		ValueRead(&in_file, 1)._byte[0]; //sph mode?	

		toonflg = ValueRead(&in_file, 1)._byte[0]; //toon flg?

		if (toonflg == 1)
			ValueRead(&in_file, 1)._byte[0];
		else ValueRead(&in_file, TextureIndexSize)._int;

		if (IsCodingUTF16)
			WideStringRead(&in_file, memo);
		else StringRead(&in_file, memo);

		

		model->MeshParts[i].EffectCount = ValueRead(&in_file, 4)._int;
		
		model->MeshParts[i].StartFace = NowStartFace;
		NowStartFace += model->MeshParts[i].EffectCount;

	}
	in_file.close();

	graph->LoadBuffer(model->Buffer, model->vertices, model->indices);
	
}

ASNET::Graph::Direct3D::Model::Model(ASNET::Graph::Direct3D::GraphDirect3D * graph){
	ParentGraph = graph;
}

ASNET::Graph::Direct3D::Model::~Model(){
	
}

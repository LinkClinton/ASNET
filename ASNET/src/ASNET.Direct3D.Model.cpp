#include "ASNET.Direct3D.Model.h"


#include<fstream>



void ASNET::Graph::Direct3D::Direct3DModelLoader::LoadPMDModel(
	ASNET::Graph::Direct3D::GraphDirect3D * graph,
	ASNET::Graph::Word filename, PMDModel *& model) {
	std::ifstream in_file;
	if (model) return;
	model = new ASNET::Graph::Direct3D::PMDModel();
	int len = wcslen(filename);
	int Last = 0;
	for (int i = 0; i < len; i++) 
		if (filename[i] == '/') Last = i;
	for (int i = 0; i < Last; i++)
		model->FilePath.push_back(filename[i]);
	model->FilePath.push_back('/');
	
	in_file.open(filename, std::ios::binary);
	
	//过滤283个字节
	ASNET::Graph::Direct3D::PMDModel::PMDRuleOut(&in_file, 283);

	

	//读取顶点个数
	model->VertexNum = PMDModel::PMDDwordRead(&in_file);
	//读取顶点数据
	for (UINT i = 0; i < model->VertexNum; i++) {
		ASNET::Graph::Direct3D::Vertex vertex;
		vertex.x = PMDModel::PMDFloatRead(&in_file);
		vertex.y = PMDModel::PMDFloatRead(&in_file);
		vertex.z = PMDModel::PMDFloatRead(&in_file);

		vertex.nx = PMDModel::PMDFloatRead(&in_file);
		vertex.ny = PMDModel::PMDFloatRead(&in_file);
		vertex.nz = PMDModel::PMDFloatRead(&in_file);

		vertex.u = PMDModel::PMDFloatRead(&in_file);
		vertex.v = PMDModel::PMDFloatRead(&in_file);
		
		//vertex.v = abs(1.0f - vertex.v);
		//过滤6字节
		PMDModel::PMDRuleOut(&in_file, 6);
		model->vertices.push_back(vertex);
	}

	//读取索引个数
	model->IndexNum = PMDModel::PMDDwordRead(&in_file);
	//读取索引
	for (UINT i = 0; i < model->IndexNum; i++) 
		model->indices.push_back(PMDModel::PMDWordRead(&in_file));
	
	//读取材质数量
	model->ModelPartsNum = PMDModel::PMDDwordRead(&in_file);

	int NowStartFace = 0;
	for (UINT i = 0; i < model->ModelPartsNum; i++) {
		PMDModelPart ModelPart;
		ModelPart.Diffuse.x = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Diffuse.y = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Diffuse.z = PMDModel::PMDFloatRead(&in_file);

		ModelPart.Alphadif = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Spemat = PMDModel::PMDFloatRead(&in_file);

		ModelPart.Specular.x = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Specular.y = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Specular.z = PMDModel::PMDFloatRead(&in_file);

		ModelPart.Ambient.x = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Ambient.y = PMDModel::PMDFloatRead(&in_file);
		ModelPart.Ambient.z = PMDModel::PMDFloatRead(&in_file);


		//2
		PMDModel::PMDRuleOut(&in_file, 2);

		ModelPart.EffectCount = PMDModel::PMDDwordRead(&in_file);
		
		for (UINT i = 0; i < model->FilePath.size();i++)
			ModelPart.TextureName.push_back(model->FilePath[i]);

		char TexName[20];
		memset(TexName, 0, sizeof(TexName));
		for (int j = 0; j < 20; j++)
			in_file.get(TexName[j]);
		for (int j = 0; j < 20; j++)
			if (TexName[j] == 0 || TexName[j]=='*') break;
			else ModelPart.TextureName.push_back(TexName[j]);

		ModelPart.StartFace = NowStartFace;
		NowStartFace += ModelPart.EffectCount;

		model->ModelParts.push_back(ModelPart);
	}
	in_file.close();

	model->ParentGraph = graph;
	
	graph->LoadBuffer(model->Buffer, model->vertices, model->indices);

	graph->LoadTexture(model->ModelParts[0].Texture, &model->ModelParts[0].TextureName[0]);
	model->Textures.insert(std::pair<std::wstring, ASNET::Graph::Direct3D::Texture*>(
		model->ModelParts[0].TextureName, model->ModelParts[0].Texture));
	for (UINT i = 1; i < model->ModelPartsNum; i++) {

		if (model->Textures.find(model->ModelParts[i].TextureName) != model->Textures.end())
			model->ModelParts[i].Texture = model->Textures[model->ModelParts[i].TextureName];
		else graph->LoadTexture(model->ModelParts[i].Texture, &model->ModelParts[i].TextureName[0]),
			model->Textures.insert(std::pair<std::wstring, ASNET::Graph::Direct3D::Texture*>(
				model->ModelParts[i].TextureName, model->ModelParts[i].Texture));
	}
	
	
}

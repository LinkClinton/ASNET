#include "ASNET.Direct3D.Model.h"

#include<fstream>



void ASNET::Graph::Direct3D::Direct3DModelLoader::LoadPMDModel(
	ASNET::Graph::Direct3D::GraphDirect3D * graph,
	ASNET::Graph::Word filename, PMDModel *& model){
	std::ifstream in_file;
	if (!model) return;
	model = new ASNET::Graph::Direct3D::PMDModel();

	in_file.open(filename, 0);
	
	//����283���ֽ�
	ASNET::Graph::Direct3D::PMDModel::PMDRuleOut(&in_file, 283);
	
	//��ȡ�������
	model->VertexNum = PMDModel::PMDDwordRead(&in_file);
	//��ȡ��������
	for (int i = 0; i < model->VertexNum; i++) {
		ASNET::Graph::Direct3D::Vertex vertex;
		vertex.x = PMDModel::PMDFloatRead(&in_file);
		vertex.y = PMDModel::PMDFloatRead(&in_file);
		vertex.z = PMDModel::PMDFloatRead(&in_file);

		vertex.nx = PMDModel::PMDFloatRead(&in_file);
		vertex.ny = PMDModel::PMDFloatRead(&in_file);
		vertex.nz = PMDModel::PMDFloatRead(&in_file);

		vertex.u = PMDModel::PMDFloatRead(&in_file);
		vertex.v = PMDModel::PMDDwordRead(&in_file);
		//����6�ֽ�
		PMDModel::PMDRuleOut(&in_file, 6);
		model->vertices.push_back(vertex);
	}

	//��ȡ��������
	model->IndexNum = PMDModel::PMDDwordRead(&in_file);
	//��ȡ����
	for (int i = 0; i < model->IndexNum; i++) 
		model->indices.push_back(PMDModel::PMDWordRead(&in_file));
	
	//��ȡ��������
	model->MaterialNum = PMDModel::PMDDwordRead(&in_file);

	for (int i = 0; i < model->MaterialNum; i++) {
		PMDMaterial material;
		material.Diffuse.x = PMDModel::PMDFloatRead(&in_file);
		material.Diffuse.y = PMDModel::PMDFloatRead(&in_file);
		material.Diffuse.z = PMDModel::PMDFloatRead(&in_file);

		material.Alphadif = PMDModel::PMDFloatRead(&in_file);
		material.Spemat = PMDModel::PMDFloatRead(&in_file);

		material.Specular.x = PMDModel::PMDFloatRead(&in_file);
		material.Specular.y = PMDModel::PMDFloatRead(&in_file);
		material.Specular.z = PMDModel::PMDFloatRead(&in_file);

		material.Ambient.x = PMDModel::PMDFloatRead(&in_file);
		material.Ambient.y = PMDModel::PMDFloatRead(&in_file);
		material.Ambient.z = PMDModel::PMDFloatRead(&in_file);

		PMDModel::PMDRuleOut(&in_file, 2);

		material.EffectCount = PMDModel::PMDDwordRead(&in_file);
		
	}
	
	in_file.close();
}

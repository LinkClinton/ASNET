#include "FBXLoader.h"

void ASNET::Sample::FBXLoader::ProcessNode(FbxNode * node){
	if (node->GetNodeAttribute()) { //是否存在？
		switch (node->GetNodeAttribute()->GetAttributeType()) //类型？
		{
		case FbxNodeAttribute::eMesh:
			ProcessMesh(node);
			break;
		default:
			break;
		}
	} //遍历子节点
	for (size_t i = 0; i < node->GetChildCount(); i++)
		ProcessNode(node->GetChild(i));
}

void ASNET::Sample::FBXLoader::ProcessMesh(FbxNode * node){
	FbxMesh* mesh = node->GetMesh();

	if (!mesh) return;
	
	Model->vertices.clear();
	Model->indices.clear();

	size_t TriangleCount = mesh->GetPolygonCount();

	for (size_t i = 0; i < TriangleCount; i++) {
		for (size_t j = 0; j < 3; j++) {
			Model->indices.push_back(mesh->GetPolygonVertex(i, j));

			ASNET::Graph::Direct3D::Vertex vertex;



		}
	}

}

ASNET::Sample::FBXLoader::FBXLoader(){
	Manager = FbxManager::Create();

	Ios = FbxIOSettings::Create(Manager, IOSROOT);

	Manager->SetIOSettings(Ios);
}

void ASNET::Sample::FBXLoader::LoadFbxSence(char * filename, 
	ASNET::Sample::FBXModel * model){

	FbxImporter*   Importer = nullptr;
	FbxScene*      Scene = nullptr;

	Model = model;

	Importer = FbxImporter::Create(Manager, "");

	Scene = FbxScene::Create(Manager, "");

	Importer->Initialize(filename, -1, Manager->GetIOSettings());

	Importer->Import(Scene);




	Model = nullptr;

	Importer->Destroy();

	


}

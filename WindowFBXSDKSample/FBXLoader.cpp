#include "FBXLoader.h"

#pragma comment(lib,"libfbxsdk.lib")


void ASNET::Sample::FBXLoader::ReadVertex(FbxMesh * mesh, 
	int index, FbxVertex * vertex){
	FbxVector4 Point = mesh->GetControlPointAt(index);
	
	vertex->x = Point[0];
	vertex->y = Point[1];
	vertex->z = Point[2];
	
}

void ASNET::Sample::FBXLoader::ReadColor(FbxMesh * mesh, 
	int index, int vertexcount, FbxVertex * vertex){
	if (mesh->GetElementVertexColorCount() < 1) return;

	FbxGeometryElementVertexColor* pColor = mesh->GetElementVertexColor();

	switch (pColor->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint: {
		switch (pColor->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			vertex->r = pColor->GetDirectArray().GetAt(index).mRed;
			vertex->g = pColor->GetDirectArray().GetAt(index).mGreen;
			vertex->b = pColor->GetDirectArray().GetAt(index).mBlue;
			vertex->a = pColor->GetDirectArray().GetAt(index).mAlpha;
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pColor->GetIndexArray().GetAt(index);
			vertex->r = pColor->GetDirectArray().GetAt(id).mRed;
			vertex->g = pColor->GetDirectArray().GetAt(id).mGreen;
			vertex->b = pColor->GetDirectArray().GetAt(id).mBlue;
			vertex->a = pColor->GetDirectArray().GetAt(id).mAlpha;
			break;
		}
		default:
			break;
		}
		break;
	}
	case FbxGeometryElement::eByPolygonVertex: {
		switch (pColor->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			vertex->r = pColor->GetDirectArray().GetAt(vertexcount).mRed;
			vertex->g = pColor->GetDirectArray().GetAt(vertexcount).mGreen;
			vertex->b = pColor->GetDirectArray().GetAt(vertexcount).mBlue;
			vertex->a = pColor->GetDirectArray().GetAt(vertexcount).mAlpha;
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pColor->GetIndexArray().GetAt(vertexcount);
			vertex->r = pColor->GetDirectArray().GetAt(id).mRed;
			vertex->g = pColor->GetDirectArray().GetAt(id).mGreen;
			vertex->b = pColor->GetDirectArray().GetAt(id).mBlue;
			vertex->a = pColor->GetDirectArray().GetAt(id).mAlpha;
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

}



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

	Model->VertexCount = 0;
	Model->IndexCount = 0;

	size_t TriangleCount = mesh->GetPolygonCount();

	for (size_t i = 0; i < TriangleCount; i++) {
		for (size_t j = 0; j < 3; j++) {
			ASNET::Graph::Direct3D::Index  index = mesh->GetPolygonVertex(i, j);
			ASNET::Graph::Direct3D::Vertex vertex;

			Model->indices.push_back(index);

			ReadVertex(mesh, index, &vertex);

			ReadColor(mesh, index, Model->VertexCount, &vertex);

			Model->vertices.push_back(vertex);


			Model->VertexCount++;
		}
	}

}

ASNET::Sample::FBXLoader::FBXLoader(){
	Manager = FbxManager::Create();

	Ios = FbxIOSettings::Create(Manager, IOSROOT);

	Manager->SetIOSettings(Ios);
}

void ASNET::Sample::FBXLoader::LoadFbxSence(char * filename, 
	ASNET::Sample::FBXModel *& model,ASNET::Graph::Direct3D::GraphDirect3D* graph){



	model = new FBXModel(graph);



	FbxImporter*   Importer = nullptr;
	FbxScene*      Scene = nullptr;

	Model = model;

	Importer = FbxImporter::Create(Manager, "");

	Scene = FbxScene::Create(Manager, "");

	Importer->Initialize(filename, -1, Manager->GetIOSettings());

	Importer->Import(Scene);

	FbxNode* root = Scene->GetRootNode();

	for (int i = 0; i < root->GetChildCount(); i++)
		ProcessNode(root->GetChild(i));

	//ProcessNode()

	graph->LoadBuffer(Model->Buffer, Model->vertices, Model->indices);

	

	Model = nullptr;

	Importer->Destroy();

	


}

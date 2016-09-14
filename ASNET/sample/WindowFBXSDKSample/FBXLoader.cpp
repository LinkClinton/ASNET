#include "FBXLoader.h"

#pragma comment(lib,"libfbxsdk.lib")


void ASNET::Sample::FBXLoader::ReadVertex(FbxMesh * mesh, 
	int index, FbxVertex * vertex){
	FbxVector4 Point = mesh->GetControlPointAt(index);

	vertex->x = (float)Point[0];
	vertex->y = (float)Point[1];
	vertex->z = (float)Point[2];
	
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
			vertex->r = (float)pColor->GetDirectArray().GetAt(index).mRed;
			vertex->g = (float)pColor->GetDirectArray().GetAt(index).mGreen;
			vertex->b = (float)pColor->GetDirectArray().GetAt(index).mBlue;
			vertex->a = (float)pColor->GetDirectArray().GetAt(index).mAlpha;
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pColor->GetIndexArray().GetAt(index);
			vertex->r = (float)pColor->GetDirectArray().GetAt(id).mRed;
			vertex->g = (float)pColor->GetDirectArray().GetAt(id).mGreen;
			vertex->b = (float)pColor->GetDirectArray().GetAt(id).mBlue;
			vertex->a = (float)pColor->GetDirectArray().GetAt(id).mAlpha;
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
			vertex->r = (float)pColor->GetDirectArray().GetAt(vertexcount).mRed;
			vertex->g = (float)pColor->GetDirectArray().GetAt(vertexcount).mGreen;
			vertex->b = (float)pColor->GetDirectArray().GetAt(vertexcount).mBlue;
			vertex->a = (float)pColor->GetDirectArray().GetAt(vertexcount).mAlpha;
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pColor->GetIndexArray().GetAt(vertexcount);
			vertex->r = (float)pColor->GetDirectArray().GetAt(id).mRed;
			vertex->g = (float)pColor->GetDirectArray().GetAt(id).mGreen;
			vertex->b = (float)pColor->GetDirectArray().GetAt(id).mBlue;
			vertex->a = (float)pColor->GetDirectArray().GetAt(id).mAlpha;
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
		case FbxNodeAttribute::eSkeleton:
			ProcessSkeleton(node);
			break;
		default:
			break;
		}
	} //遍历子节点
	for (int i = 0; i < node->GetChildCount(); i++)
		ProcessNode(node->GetChild(i));
}

void ASNET::Sample::FBXLoader::ProcessMesh(FbxNode * node){
	FbxMesh* mesh = node->GetMesh();

	if (!mesh) return;
	
	Model->vertices.clear();
	Model->indices.clear();

	Model->VertexCount = 0;
	Model->IndexCount = mesh->GetPolygonVertexCount();

	for (size_t i = 0; i < Model->IndexCount; i++) {
		ASNET::Graph::Direct3D::Index index = (UINT)mesh->GetPolygonVertices()[i];
		Model->indices.push_back(index);
		Model->VertexCount = max(Model->VertexCount, index);
	}

	for (size_t i = 0; i <= Model->VertexCount; i++) {
		ASNET::Graph::Direct3D::Vertex vertex;
		ReadVertex(mesh, i, &vertex);

		ReadColor(mesh, i, i, &vertex);

		Model->vertices.push_back(vertex);
	}
	

}

void ASNET::Sample::FBXLoader::ProcessSkeleton(FbxNode * node)
{
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

	graph->LoadBuffer(Model->Buffer, Model->vertices, Model->indices);

	

	Model = nullptr;

	Importer->Destroy();

	Scene->Destroy();

	


}

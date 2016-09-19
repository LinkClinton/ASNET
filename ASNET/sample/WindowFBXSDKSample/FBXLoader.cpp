#include "FBXLoader.h"

#pragma comment(lib,"libfbxsdk.lib")








void ASNET::Sample::FBXLoader::ReadVertex(FbxMesh * mesh,
	int index, FbxVertex * vertex){
	FbxVector4 Point = mesh->GetControlPointAt(index);

	vertex->x = static_cast<float>(Point[0]);
	vertex->y = static_cast<float>(Point[1]);
	vertex->z = static_cast<float>(Point[2]);


	
}

void ASNET::Sample::FBXLoader::ReadColor(FbxMesh * mesh, 
	int index, int indexcount, FbxVertex * vertex){

	if (mesh->GetElementVertexColorCount() < 1) return; //if no color return 

	FbxGeometryElementVertexColor* pVertexColor = mesh->GetElementVertexColor();  //Color Set

	switch (pVertexColor->GetMappingMode()) //Format
	{
	case FbxGeometryElement::eByControlPoint: { //By ControlPoint
		switch (pVertexColor->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: { //use vertex id
			vertex->r = static_cast<float>(pVertexColor->GetDirectArray().GetAt(index).mRed);
			vertex->g = static_cast<float>(pVertexColor->GetDirectArray().GetAt(index).mGreen);
			vertex->b = static_cast<float>(pVertexColor->GetDirectArray().GetAt(index).mBlue);
			vertex->a = static_cast<float>(pVertexColor->GetDirectArray().GetAt(index).mAlpha);
			break;
		} 
		case FbxGeometryElement::eIndexToDirect: { //use index get id 
			int id = pVertexColor->GetIndexArray().GetAt(index);
			vertex->r = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mRed);
			vertex->g = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mGreen);
			vertex->b = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mBlue);
			vertex->a = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mAlpha);
			break;
		}
		default:
			break;
		}
		break;
	}
	case FbxGeometryElement::eByPolygonVertex: { 
		switch (pVertexColor->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			vertex->r = static_cast<float>(pVertexColor->GetDirectArray().GetAt(indexcount).mRed);
			vertex->g = static_cast<float>(pVertexColor->GetDirectArray().GetAt(indexcount).mGreen);
			vertex->b = static_cast<float>(pVertexColor->GetDirectArray().GetAt(indexcount).mBlue);
			vertex->a = static_cast<float>(pVertexColor->GetDirectArray().GetAt(indexcount).mAlpha);
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pVertexColor->GetIndexArray().GetAt(indexcount);
			vertex->r = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mRed);
			vertex->g = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mGreen);
			vertex->b = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mBlue);
			vertex->a = static_cast<float>(pVertexColor->GetDirectArray().GetAt(id).mAlpha);
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

void ASNET::Sample::FBXLoader::ReadTextureUV(FbxMesh * mesh, 
	int index, int textureindex, FbxVertex * vertex){
	
	if (mesh->GetElementUVCount() < 1) return; 

	FbxGeometryElementUV* pTextureUV = mesh->GetElementUV(); //the first layer


	switch (pTextureUV->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint: {
		switch (pTextureUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			vertex->u = static_cast<float>(pTextureUV->GetDirectArray().GetAt(index)[0]);
			vertex->v = static_cast<float>(pTextureUV->GetDirectArray().GetAt(index)[1]);
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pTextureUV->GetIndexArray().GetAt(index);
			vertex->u = static_cast<float>(pTextureUV->GetDirectArray().GetAt(id)[0]);
			vertex->v = static_cast<float>(pTextureUV->GetDirectArray().GetAt(id)[1]);
			break;
		}
		default:
			break;
		}
		break;
	}
	case FbxGeometryElement::eByPolygonVertex: {
		switch (pTextureUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			
			vertex->u = static_cast<float>(pTextureUV->GetDirectArray().GetAt(textureindex)[0]);
			vertex->v = static_cast<float>(pTextureUV->GetDirectArray().GetAt(textureindex)[1]);
			break;
		}
		case FbxGeometryElement::eIndexToDirect:{
			FbxVector2 vec2 = pTextureUV->GetDirectArray().GetAt(textureindex);
			vertex->u = static_cast<float>(pTextureUV->GetDirectArray().GetAt(textureindex)[0]);
			vertex->v = static_cast<float>(pTextureUV->GetDirectArray().GetAt(textureindex)[1]);
			break;
		}
		default:
			break; // other reference modes not shown here!
		}
		break;
	}
	default:
		break;
	}


}

void ASNET::Sample::FBXLoader::ReadNormal(FbxMesh * mesh, 
	int index, int indexcount, FbxVertex * vertex){

	if (mesh->GetElementNormalCount() < 1) return;

	FbxGeometryElementNormal* pNormal = mesh->GetElementNormal();

	switch (pNormal->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint: {
		switch (pNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			vertex->nx = static_cast<float>(pNormal->GetDirectArray().GetAt(index)[0]);
			vertex->ny = static_cast<float>(pNormal->GetDirectArray().GetAt(index)[1]);
			vertex->nz = static_cast<float>(pNormal->GetDirectArray().GetAt(index)[2]);
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pNormal->GetIndexArray().GetAt(index);
			vertex->nx = static_cast<float>(pNormal->GetDirectArray().GetAt(id)[0]);
			vertex->ny = static_cast<float>(pNormal->GetDirectArray().GetAt(id)[1]);
			vertex->nz = static_cast<float>(pNormal->GetDirectArray().GetAt(id)[2]);
			break;
		}
		default:
			break;
		}
		break;
	}
	case FbxGeometryElement::eByPolygonVertex: {
		switch (pNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect: {
			vertex->nx = static_cast<float>(pNormal->GetDirectArray().GetAt(indexcount)[0]);
			vertex->ny = static_cast<float>(pNormal->GetDirectArray().GetAt(indexcount)[1]);
			vertex->nz = static_cast<float>(pNormal->GetDirectArray().GetAt(indexcount)[2]);
			break;
		}
		case FbxGeometryElement::eIndexToDirect: {
			int id = pNormal->GetIndexArray().GetAt(indexcount);
			vertex->nx = static_cast<float>(pNormal->GetDirectArray().GetAt(id)[0]);
			vertex->ny = static_cast<float>(pNormal->GetDirectArray().GetAt(id)[1]);
			vertex->nz = static_cast<float>(pNormal->GetDirectArray().GetAt(id)[2]);
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

void ASNET::Sample::FBXLoader::ReadMaterial(FbxMesh * mesh,
	int materialindex, ASNET::Graph::Direct3D::MeshPart * part) {

	if (!mesh->GetNode()) return;

	FbxNode* pNode = mesh->GetNode();

	fbxsdk::FbxSurfaceMaterial* pSurfaceMaterial = pNode->GetMaterial(materialindex);

	if (pSurfaceMaterial->GetClassId().Is(FbxSurfacePhong::ClassId)) {

		fbxsdk::FbxSurfacePhong* pSurfacePhong = (FbxSurfacePhong*)pSurfaceMaterial;

		FbxDouble3 value;

		value = pSurfacePhong->Ambient;
		part->Material.ambient.x = static_cast<float>(value[0]);
		part->Material.ambient.y = static_cast<float>(value[1]);
		part->Material.ambient.z = static_cast<float>(value[2]);

		value = pSurfacePhong->Diffuse;
		part->Material.diffuse.x = static_cast<float>(value[0]);
		part->Material.diffuse.y = static_cast<float>(value[1]);
		part->Material.diffuse.z = static_cast<float>(value[2]);

		value = pSurfacePhong->Specular;
		part->Material.specular.x = static_cast<float>(value[0]);
		part->Material.specular.y = static_cast<float>(value[1]);
		part->Material.specular.z = static_cast<float>(value[2]);

	}

	if (pSurfaceMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
		fbxsdk::FbxSurfaceLambert* pSurfaceLambert = (FbxSurfaceLambert*)pSurfaceMaterial;

		FbxDouble3 value;

		value = pSurfaceLambert->Ambient;
		part->Material.ambient.x = static_cast<float>(value[0]);
		part->Material.ambient.y = static_cast<float>(value[1]);
		part->Material.ambient.z = static_cast<float>(value[2]);

		value = pSurfaceLambert->Diffuse;
		part->Material.diffuse.x = static_cast<float>(value[0]);
		part->Material.diffuse.y = static_cast<float>(value[1]);
		part->Material.diffuse.z = static_cast<float>(value[2]);

	}

}

void ASNET::Sample::FBXLoader::ReadTextureName(FbxMesh * mesh,
	int materialindex, ASNET::Sample::FBXModel* model){
	if (!mesh->GetNode()) return;

	FbxNode* pNode = mesh->GetNode();

	fbxsdk::FbxSurfaceMaterial* pSurfaceMaterial = pNode->GetMaterial(materialindex);


	
		FbxProperty Property = pSurfaceMaterial->
			FindProperty(FbxLayerElement::sTextureChannelNames[0]); //加载最为简单的模型贴图

		if (Property.IsValid()) {
			size_t TextureCount = Property.GetSrcObjectCount<FbxTexture>();
			for (size_t i = 0; i < TextureCount; i++) {
				FbxLayeredTexture* pLayeredTexture = Property.GetSrcObject<FbxLayeredTexture>(i);

				if (!pLayeredTexture) {
					FbxTexture* pTexture = Property.GetSrcObject<FbxTexture>(i);

					if (pTexture) {
						FbxFileTexture* pFileTexture = FbxCast<FbxFileTexture>(pTexture);
						std::string TextureFileName = pFileTexture->GetFileName();
						std::wstring WTextureFileName;



						for (size_t i = 0; i < TextureFileName.length(); i++) {
							if (TextureFileName[i] == 92)
								WTextureFileName.push_back('/');
							else
								WTextureFileName.push_back(TextureFileName[i]);
						}


						std::map<std::wstring, int>::iterator it =
							model->FileNameIndex.find(WTextureFileName);

						if (it != model->FileNameIndex.end())
							model->MeshParts[materialindex].TextureID = it->second;
						else {
							model->FileNameIndex.insert(
								std::pair<std::wstring, int>(WTextureFileName, model->TextureCount));
							model->MeshParts[materialindex].TextureID = model->TextureCount;
							model->TextureCount++;
						}

					}
				}
			}
		}
}



void ASNET::Sample::FBXLoader::LoadMaterialAndTexture(
	FbxMesh * mesh, FBXModel * model){

	int IndexCount = mesh->GetPolygonCount();

	FbxLayerElementArrayTemplate<int>* MaterialIndices = nullptr;
	FbxGeometryElement::EMappingMode MaterialMappingMode = FbxGeometryElement::eNone;

	if (mesh->GetElementMaterial() && mesh->GetNode()) {
		std::vector<bool> Visited;

		model->MeshPartCount = mesh->GetNode()->GetMaterialCount();
		model->MeshParts.resize(model->MeshPartCount);
		Visited.resize(model->MeshPartCount);
			
		MaterialIndices = &mesh->GetElementMaterial()->GetIndexArray();
		MaterialMappingMode = mesh->GetElementMaterial()->GetMappingMode();

		if (MaterialIndices && MaterialMappingMode == FbxGeometryElement::eByPolygon) {
			if (MaterialIndices->GetCount() == IndexCount) {
				for (size_t i = 0; i < (size_t)IndexCount; i++) {
					int MaterialIndex = MaterialIndices->GetAt(i);
					if (!Visited[MaterialIndex]) {
						
						ReadMaterial(mesh, MaterialIndex, &model->MeshParts[MaterialIndex]);
						
						ReadTextureName(mesh, MaterialIndex, model);
						
						Visited[MaterialIndex] = true;
					}
					model->MeshParts[MaterialIndex].EffectCount += 3;
				}
			}
			int StartFace = 0;
			for (size_t i = 0; i < model->MeshPartCount; i++) {
				model->MeshParts[i].StartFace = StartFace;
				StartFace += model->MeshParts[i].EffectCount;
			}
		}

	}

	model->Textures.resize(model->TextureCount); 
	std::map<std::wstring, int>::iterator it;
	for (it = model->FileNameIndex.begin(); it != model->FileNameIndex.end(); it++) {
		ASNET::Graph::Direct3D::Texture* pTexture = nullptr;

		std::wstring TextureFileName = it->first;

		model->ParentGraph->LoadTexture(pTexture, &TextureFileName[0]);

		model->Textures[it->second] = pTexture;
	}

	

	for (size_t i = 0; i < model->MeshParts.size(); i++)
		model->MeshParts[i].Texture = model->Textures[model->MeshParts[i].TextureID];

	
	if (model->MeshPartCount == 0) {
		model->MeshParts.push_back(ASNET::Graph::Direct3D::MeshPart());
		model->MeshParts[0].EffectCount = model->IndexCount;
		model->MeshParts[0].StartFace = 0;
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

	Model->VertexCount = mesh->GetControlPointsCount();
	Model->IndexCount = mesh->GetPolygonVertexCount();


	int TriangleCount = mesh->GetPolygonCount();
	int IndexCount = 0;
	
	std::vector<bool> Visited;


	Model->vertices.resize(Model->VertexCount);
	Visited.resize(Model->VertexCount);



	for (size_t i = 0; i < (size_t)TriangleCount; i++) {
		for (size_t j = 0; j < 3; j++) {
			int index = mesh->GetPolygonVertex(i, j);

			Model->indices.push_back(index);

			if (!Visited[index]) {
				ReadVertex(mesh, index, &Model->vertices[index]);
				ReadColor(mesh, index, IndexCount, &Model->vertices[index]);
				
				ReadNormal(mesh, index, IndexCount, &Model->vertices[index]);
				ReadTextureUV(mesh, index, mesh->GetTextureUVIndex(i, j), &Model->vertices[index]);
				//Model->vertices[index].v = 1.f - Model->vertices[index].v;
				//Model->vertices[index].u = 1.f - Model->vertices[index].u;
				//std::swap(Model->vertices[index].u, Model->vertices[index].v);
				Visited[index] = true;
			}
		
			
			//std::cout << Model->vertices[index].u << ", " << Model->vertices[index].v << std::endl;
			IndexCount++;
		}
	}

	

	LoadMaterialAndTexture(mesh, Model);
	


}

void ASNET::Sample::FBXLoader::ProcessSkeleton(FbxNode * node)
{
}

ASNET::Sample::FBXLoader::FBXLoader(){
	Manager = FbxManager::Create();

	Ios = FbxIOSettings::Create(Manager, IOSROOT);

	Manager->SetIOSettings(Ios);
}

ASNET::Sample::FBXLoader::~FBXLoader()
{
	Ios->Destroy();
	Manager->Destroy();
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

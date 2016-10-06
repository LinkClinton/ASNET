#include "FBXLoader.h"

#pragma comment(lib,"libfbxsdk.lib")








/*
FBX格式的骨骼动画的理解
然后就可以直接通过某些方法计算出矩阵了，虽然方便了些
首先有两种算法，要根据模型格式去选择
Linear Way
似乎就是对于每个骨骼的变换，可以通过计算直接获得矩阵

*/

void ASNET::Sample::FBXLoader::ProcessBoneName(FbxNode * pNode, ASNET::Sample::FBXModel* model, Bone* parent)
{
	std::string BoneName = pNode->GetName();

	std::map<std::string, Bone*>::iterator it = model->BoneNameIndex.find(BoneName);

	if (it == model->BoneNameIndex.end() && BoneName != "RootNode") {
		Bone* bone = new Bone(Model->BoneCount, parent);
		if (parent = nullptr)
			model->root = bone;
		model->BoneNameIndex.insert(std::pair<std::string, Bone*>(BoneName, bone));
		model->BoneCount++;
	}

	it = model->BoneNameIndex.find(BoneName);

	for (int i = 0; i < pNode->GetChildCount(); i++)
		if (it != model->BoneNameIndex.end())
			ProcessBoneName(pNode->GetChild(i), model, it->second);
		else ProcessBoneName(pNode->GetChild(i), model, nullptr);
}

void ASNET::Sample::FBXLoader::HashBoneName(FbxScene * pScene, FbxNode * pNode, ASNET::Sample::FBXModel * model)
{
	pNode = pScene->GetRootNode();

	Model->Animations.resize(pScene->GetSrcObjectCount<FbxAnimStack>());

	for (int i = 0; i < pScene->GetSrcObjectCount<FbxAnimStack>(); i++) {
		FbxAnimStack* AnimStack = pScene->GetSrcObject<FbxAnimStack>(i);
		for (int j = 0; j < AnimStack->GetMemberCount<FbxAnimLayer>(); j++) {
			FbxAnimLayer* AnimLayer = AnimStack->GetMember<FbxAnimLayer>(j);
			//ProcessBoneName()
			ProcessBoneName(pNode, model, nullptr);
		}

	}
}

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
			int id = pTextureUV->GetIndexArray().GetAt(textureindex);
			vertex->u = static_cast<float>(pTextureUV->GetDirectArray().GetAt(id)[0]);
			vertex->v = static_cast<float>(pTextureUV->GetDirectArray().GetAt(id)[1]);
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
		part->Material.ambient.w = 1.0f;

		value = pSurfacePhong->Diffuse;
		part->Material.diffuse.x = static_cast<float>(value[0]);
		part->Material.diffuse.y = static_cast<float>(value[1]);
		part->Material.diffuse.z = static_cast<float>(value[2]);
		part->Material.diffuse.w = 1.0f;

		value = pSurfacePhong->Specular;
		part->Material.specular.x = static_cast<float>(value[0]);
		part->Material.specular.y = static_cast<float>(value[1]);
		part->Material.specular.z = static_cast<float>(value[2]);
		part->Material.specular.w = 1.0f;

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

void ASNET::Sample::FBXLoader::ReadWeightsAndBoneIndex(
	FbxMesh * mesh, ASNET::Sample::FBXModel * model)
{
	std::vector<int> VertexCounter;
	VertexCounter.resize(model->VertexCount);

	size_t SkinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
	for (size_t Skin_i = 0; Skin_i < SkinCount; Skin_i++) {
		FbxSkin* Skin = (FbxSkin*)mesh->GetDeformer(Skin_i, FbxDeformer::eSkin);
		FbxSkin::EType Type = Skin->GetSkinningType();
		size_t ClusterCount = Skin->GetClusterCount();
		for (size_t Cluster_i = 0; Cluster_i < ClusterCount; Cluster_i++) {
			FbxCluster* pCluster = Skin->GetCluster(Cluster_i);
			FbxNode*    pBone = pCluster->GetLink();
			std::string BoneName = pBone->GetName();
			size_t Count = pCluster->GetControlPointIndicesCount();
			double* pWeights = pCluster->GetControlPointWeights();
			int* pIndex = pCluster->GetControlPointIndices();
			std::map<std::string, Bone*>::iterator it = model->BoneNameIndex.find(BoneName);
			it->second->pCluster = pCluster;
			for (size_t i = 0; i < Count; i++) {
				model->vertices[pIndex[i]].Weight((float)pWeights[i], VertexCounter[pIndex[i]]);
				model->vertices[pIndex[i]].BoneIndices[VertexCounter[pIndex[i]]] = (byte)it->second->id;
				VertexCounter[pIndex[i]]++;
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

	
	if (model->TextureCount)
		for (size_t i = 0; i < model->MeshParts.size(); i++)
			model->MeshParts[i].Texture = model->Textures[model->MeshParts[i].TextureID];

	
	if (model->MeshPartCount == 0) {
		model->MeshParts.push_back(ASNET::Graph::Direct3D::MeshPart());
		model->MeshParts[0].EffectCount = model->IndexCount;
		model->MeshParts[0].StartFace = 0;
	}
	
}

void ASNET::Sample::FBXLoader::LoadAnimationLayer(FbxAnimLayer * layer, FbxNode * pNode,
	int animation_id)
{
	std::string BoneName = pNode->GetName();
	std::map<std::string, Bone*>::iterator it = Model->BoneNameIndex.find(BoneName);
	if (it != Model->BoneNameIndex.end()) {
		ASNET::Sample::BoneAnimation* BoneAnimation = &Model->Animations[animation_id].BoneAnimations[it->second->id];
		FbxAnimCurve* pAnimCurve = nullptr;

		pAnimCurve = pNode->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].Translation.x = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].Translation.y = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].Translation.z = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].RotationQuat.x = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].RotationQuat.y = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].RotationQuat.z = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclScaling.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].Scale.x = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclScaling.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].Scale.y = pAnimCurve->KeyGetValue(i);
			}
		}

		pAnimCurve = pNode->LclScaling.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
		if (pAnimCurve) {
			if (BoneAnimation->KeyFrames.empty())
				BoneAnimation->KeyFrames.resize(pAnimCurve->KeyGetCount());
			for (int i = 0; i < pAnimCurve->KeyGetCount(); i++) {
				BoneAnimation->KeyFrames[i].TimePos = (float)pAnimCurve->KeyGetTime(i).GetMilliSeconds() / 1000.f;
				BoneAnimation->KeyFrames[i].Scale.z = pAnimCurve->KeyGetValue(i);
			}
		}
		
	}
	

	for (int i = 0; i < pNode->GetChildCount(); i++)
		LoadAnimationLayer(layer, pNode->GetChild(i), animation_id);
	
}



void ASNET::Sample::FBXLoader::LoadAnimation(FbxScene * pScene)
{
	FbxNode* pNode = pScene->GetRootNode();

	Model->Animations.resize(pScene->GetSrcObjectCount<FbxAnimStack>());
	
	for (int i = 0; i < pScene->GetSrcObjectCount<FbxAnimStack>(); i++) {
		FbxAnimStack* AnimStack = pScene->GetSrcObject<FbxAnimStack>(i);
		Model->Animations[i].BoneAnimations.resize(Model->BoneCount);
		for (int j = 0; j < AnimStack->GetMemberCount<FbxAnimLayer>(); j++) {
			FbxAnimLayer* AnimLayer = AnimStack->GetMember<FbxAnimLayer>(j);
			LoadAnimationLayer(AnimLayer, pNode, i);
		}

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
		case FbxNodeAttribute::eLight:
			ProcessLight(node);
			break;
		default:
			break;
		}
	} //遍历子节点
	for (int i = 0; i < node->GetChildCount(); i++)
		ProcessNode(node->GetChild(i));
}

void ASNET::Sample::FBXLoader::ProcessMesh(FbxNode * node){
	if (Once) return;
	FbxMesh* mesh = node->GetMesh();
	if (!mesh) return;

	Model->Mesh = mesh;

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
				
				ReadTextureUV(mesh, index, IndexCount, &Model->vertices[index]);
		
				Model->vertices[index].v = (1.f - Model->vertices[index].v);
				Model->UpDataCenterPos(Model->vertices[index]);
				//std::swap(Model->vertices[index].u, Model->vertices[index].v);
				Visited[index] = true;
			}
		
			//std::cout << Model->vertices[index].u << ", " << Model->vertices[index].v << std::endl;
			IndexCount++;
		}
	}

	Once = true;

	LoadMaterialAndTexture(mesh, Model);
	
	ReadWeightsAndBoneIndex(mesh, Model);

}

void ASNET::Sample::FBXLoader::ProcessLight(FbxNode * node)
{

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

	Once = false;

	model = new FBXModel(graph);



	FbxImporter*   Importer = nullptr;

	Model = model;

	Importer = FbxImporter::Create(Manager, "");

	model->Scene = FbxScene::Create(Manager, "");

	Importer->Initialize(filename, -1, Manager->GetIOSettings());

	Importer->Import(model->Scene);

	HashBoneName(model->Scene, nullptr, Model);

	model->ModelBone.resize(model->BoneCount);

	for (std::map<std::string, Bone*>::iterator it = model->BoneNameIndex.begin(); it != model->BoneNameIndex.end(); it++){
		model->ModelBone[it->second->id] = it->second;
	}

	FbxNode* root = model->Scene->GetRootNode();

	for (int i = 0; i < root->GetChildCount(); i++)
		ProcessNode(root->GetChild(i));

	//LoadAnimation(model->Scene);

	graph->LoadBuffer(Model->Buffer, Model->vertices, Model->indices, true);
	


	Model = nullptr;

	Importer->Destroy();

	

	


}

void ASNET::Sample::FBXModel::MatrixAdd(FbxAMatrix & pDstMatrix, FbxAMatrix & pSrcMatrix)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pDstMatrix[i][j] += pSrcMatrix[i][j];
		}
	}
}

void ASNET::Sample::FBXModel::MatrixAddToDiagonal(FbxAMatrix & pMatrix, double pValue)
{
	pMatrix[0][0] += pValue;
	pMatrix[1][1] += pValue;
	pMatrix[2][2] += pValue;
	pMatrix[3][3] += pValue;
}

void ASNET::Sample::FBXModel::MatrixScale(FbxAMatrix & pMatrix, double pValue)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pMatrix[i][j] *= pValue;
		}
	}
}

FbxAMatrix ASNET::Sample::FBXModel::GetGeometry(FbxNode * pNode)
{
	const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(lT, lR, lS);
}

FbxAMatrix ASNET::Sample::FBXModel::GetPoseMatrix(FbxPose * pPose, int pNodeIndex)
{
	FbxAMatrix lPoseMatrix;
	FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

	memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

	return lPoseMatrix;
}

FbxAMatrix ASNET::Sample::FBXModel::GetGlobalPosition(FbxNode * pNode, const FbxTime & pTime, FbxPose * pPose, FbxAMatrix * pParentGlobalPosition)
{
	FbxAMatrix lGlobalPosition;
	bool        lPositionFound = false;

	if (pPose)
	{
		int lNodeIndex = pPose->Find(pNode);

		if (lNodeIndex > -1)
		{
			// The bind pose is always a global matrix.
			// If we have a rest pose, we need to check if it is
			// stored in global or local space.
			if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
			{
				lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
			}
			else
			{
				// We have a local matrix, we need to convert it to
				// a global space matrix.
				FbxAMatrix lParentGlobalPosition;

				if (pParentGlobalPosition)
				{
					lParentGlobalPosition = *pParentGlobalPosition;
				}
				else
				{
					if (pNode->GetParent())
					{
						lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
					}
				}

				FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
				lGlobalPosition = lParentGlobalPosition * lLocalPosition;
			}

			lPositionFound = true;
		}
	}

	if (!lPositionFound)
	{
		// There is no pose entry for that node, get the current global position instead.

		// Ideally this would use parent global position and local position to compute the global position.
		// Unfortunately the equation 
		//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
		// does not hold when inheritance type is other than "Parent" (RSrs).
		// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
		lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
	}

	return lGlobalPosition;
}

void ASNET::Sample::FBXModel::ComputeClusterDeformation(FbxAMatrix & pGlobalPosition,
	FbxMesh * pMesh, FbxCluster * pCluster, FbxAMatrix & pVertexTransformMatrix, FbxTime pTime, FbxPose * pPose)
{
	FbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

	FbxAMatrix lReferenceGlobalInitPosition;
	FbxAMatrix lReferenceGlobalCurrentPosition;
	FbxAMatrix lAssociateGlobalInitPosition;
	FbxAMatrix lAssociateGlobalCurrentPosition;
	FbxAMatrix lClusterGlobalInitPosition;
	FbxAMatrix lClusterGlobalCurrentPosition;

	FbxAMatrix lReferenceGeometry;
	FbxAMatrix lAssociateGeometry;
	FbxAMatrix lClusterGeometry;

	FbxAMatrix lClusterRelativeInitPosition;
	FbxAMatrix lClusterRelativeCurrentPositionInverse;

	if (lClusterMode == FbxCluster::eAdditive && pCluster->GetAssociateModel())
	{
		pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
		// Geometric transform of the model
		lAssociateGeometry = GetGeometry(pCluster->GetAssociateModel());
		lAssociateGlobalInitPosition *= lAssociateGeometry;
		lAssociateGlobalCurrentPosition = GetGlobalPosition(pCluster->GetAssociateModel(), pTime, pPose);

		pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		// Multiply lReferenceGlobalInitPosition by Geometric Transformation
		lReferenceGeometry = GetGeometry(pMesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;
		lReferenceGlobalCurrentPosition = pGlobalPosition;

		// Get the link initial global position and the link current global position.
		pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		// Multiply lClusterGlobalInitPosition by Geometric Transformation
		lClusterGeometry = GetGeometry(pCluster->GetLink());
		lClusterGlobalInitPosition *= lClusterGeometry;
		lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);

		// Compute the shift of the link relative to the reference.
		//ModelM-1 * AssoM * AssoGX-1 * LinkGX * LinkM-1*ModelM
		pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition * lAssociateGlobalCurrentPosition.Inverse() *
			lClusterGlobalCurrentPosition * lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
	}
	else
	{
		pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		lReferenceGlobalCurrentPosition = pGlobalPosition;
		// Multiply lReferenceGlobalInitPosition by Geometric Transformation
		lReferenceGeometry = GetGeometry(pMesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;

		// Get the link initial global position and the link current global position.
		pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);

		// Compute the initial position of the link relative to the reference.
		lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;

		// Compute the current position of the link relative to the reference.
		lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;

		// Compute the shift of the link relative to the reference.
		pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
	}
}

void ASNET::Sample::FBXModel::ComputeLinearDeformation(FbxAMatrix & pGlobalPosition, FbxMesh * pMesh, FbxTime & pTime,
	FbxVector4 * pVertexArray, FbxPose * pPose)
{
	// All the links must have the same link mode.
	FbxCluster::ELinkMode lClusterMode = ((FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin))->GetCluster(0)->GetLinkMode();

	int lVertexCount = pMesh->GetControlPointsCount();
	FbxAMatrix* lClusterDeformation = new FbxAMatrix[lVertexCount];
	memset(lClusterDeformation, 0, lVertexCount * sizeof(FbxAMatrix));

	double* lClusterWeight = new double[lVertexCount];
	memset(lClusterWeight, 0, lVertexCount * sizeof(double));

	if (lClusterMode == FbxCluster::eAdditive)
	{
		for (int i = 0; i < lVertexCount; ++i)
		{
			lClusterDeformation[i].SetIdentity();
		}
	}

	// For all skins and all clusters, accumulate their deformation and weight
	// on each vertices and store them in lClusterDeformation and lClusterWeight.
	int lSkinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);
	for (int lSkinIndex = 0; lSkinIndex<lSkinCount; ++lSkinIndex)
	{
		FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin);

		int lClusterCount = lSkinDeformer->GetClusterCount();
		for (int lClusterIndex = 0; lClusterIndex<lClusterCount; ++lClusterIndex)
		{
			FbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
			if (!lCluster->GetLink())
				continue;

			FbxAMatrix lVertexTransformMatrix;
			ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);

			int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
			for (int k = 0; k < lVertexIndexCount; ++k)
			{
				int lIndex = lCluster->GetControlPointIndices()[k];

				// Sometimes, the mesh can have less points than at the time of the skinning
				// because a smooth operator was active when skinning but has been deactivated during export.
				if (lIndex >= lVertexCount)
					continue;

				double lWeight = lCluster->GetControlPointWeights()[k];

				if (lWeight == 0.0)
				{
					continue;
				}

				// Compute the influence of the link on the vertex.
				FbxAMatrix lInfluence = lVertexTransformMatrix;
				MatrixScale(lInfluence, lWeight);

				if (lClusterMode == FbxCluster::eAdditive)
				{
					// Multiply with the product of the deformations on the vertex.
					MatrixAddToDiagonal(lInfluence, 1.0 - lWeight);
					lClusterDeformation[lIndex] = lInfluence * lClusterDeformation[lIndex];

					// Set the link to 1.0 just to know this vertex is influenced by a link.
					lClusterWeight[lIndex] = 1.0;
				}
				else // lLinkMode == FbxCluster::eNormalize || lLinkMode == FbxCluster::eTotalOne
				{
					// Add to the sum of the deformations on the vertex.
					MatrixAdd(lClusterDeformation[lIndex], lInfluence);

					// Add to the sum of weights to either normalize or complete the vertex.
					lClusterWeight[lIndex] += lWeight;
				}
			}//For each vertex			
		}//lClusterCount
	}

	//Actually deform each vertices here by information stored in lClusterDeformation and lClusterWeight
	for (int i = 0; i < lVertexCount; i++)
	{
		FbxVector4 lSrcVertex = pVertexArray[i];
		FbxVector4& lDstVertex = pVertexArray[i];
		double lWeight = lClusterWeight[i];

		// Deform the vertex if there was at least a link with an influence on the vertex,
		if (lWeight != 0.0)
		{
			lDstVertex = lClusterDeformation[i].MultT(lSrcVertex);
			if (lClusterMode == FbxCluster::eNormalize)
			{
				// In the normalized link mode, a vertex is always totally influenced by the links. 
				lDstVertex /= lWeight;
			}
			else if (lClusterMode == FbxCluster::eTotalOne)
			{
				// In the total 1 link mode, a vertex can be partially influenced by the links. 
				lSrcVertex *= (1.0 - lWeight);
				lDstVertex += lSrcVertex;
			}
		}
	}

	delete[] lClusterDeformation;
	delete[] lClusterWeight;
}



void ASNET::Sample::FBXModel::UpDataFrame(float time, int animation)
{
	std::vector<DirectX::XMFLOAT4X4> matrix;
	GetFinalTransform(time, animation, matrix);

	std::vector<FbxVertex> vertex(VertexCount);

	for (size_t i = 0; i < VertexCount; i++) {
		float weights[4];
		weights[0] = vertices[i].wx;
		weights[1] = vertices[i].wy;
		weights[2] = vertices[i].wz;
		weights[3] = 1 - weights[0] - weights[1] - weights[2];
		DirectX::XMFLOAT4 pos = DirectX::XMFLOAT4(vertices[i].x, vertices[i].y, vertices[i].z, 1.0f);
		DirectX::XMFLOAT4 posl = DirectX::XMFLOAT4(0, 0, 0, 0);
		for (int j = 0; j < 4; j++) {
			posl = Add(posl, Mul(Mul(pos, matrix[vertices[i].BoneIndices[j]]), weights[j]));
		}
		vertex[i] = vertices[i];
		vertex[i].x = posl.x;
		vertex[i].y = posl.y;
		vertex[i].z = posl.z;
	}

	Buffer->reset(vertex, indices);
	
}

void ASNET::Sample::FBXModel::DrawAnimation(int animation)
{
	if (!IsFrame) {
		Time = Animations[animation].GetStartKeyFrame();
		IsFrame = true;
	}

	UpDataFrame(Time, animation);

	if (Time >= Animations[animation].GetEndKeyFrame()) {
		IsFrame = false;
		Buffer->reset(vertices, indices);
		return;
	}

	Time += ParentGraph->RenderTime();
	

}

void ASNET::Sample::FBXModel::UpDataCenterPos(
	ASNET::Sample::FbxVertex vertex){
	MaxPos.x = max(MaxPos.x, vertex.x);
	MaxPos.y = max(MaxPos.y, vertex.y);
	MaxPos.z = max(MaxPos.z, vertex.z);
	MinPos.x = min(MinPos.x, vertex.x);
	MinPos.y = min(MinPos.y, vertex.y);
	MinPos.z = min(MinPos.z, vertex.z);
	CenterPos.x = (MaxPos.x + MinPos.x) / 2.f;
	CenterPos.y = (MaxPos.y + MinPos.y) / 2.f;
	CenterPos.z = (MaxPos.z + MinPos.z) / 2.f;
}

void ASNET::Sample::FBXModel::GetFinalTransform(float time, int animation, std::vector<DirectX::XMFLOAT4X4> &matrix)
{
	
}

void ASNET::Sample::FBXModel::SetCurrentPose(int index)
{
	Pose = Scene->GetPose(index);
}

void ASNET::Sample::FBXModel::SetCurrentAnimation(int index)
{
	if (IsFrame) return;

	int AnimStackCount = Scene->GetSrcObjectCount<FbxAnimStack>();

	if (index >= AnimStackCount || !AnimStackCount) { FrameStartTime = 0; FrameEndTime = 0; return; }

	FbxAnimStack* AnimStack = Scene->GetSrcObject<FbxAnimStack>(index);

	AnimLayer = AnimStack->GetMember<FbxAnimLayer>();
	
	Scene->SetCurrentAnimationStack(AnimStack);

	FbxTakeInfo* TakeInfo = Scene->GetTakeInfo(AnimStack->GetName());

	if (TakeInfo) {
		FrameStartTime = TakeInfo->mLocalTimeSpan.GetStart();
		FrameEndTime.SetSecondDouble(TakeInfo->mLocalTimeSpan.GetStop().GetSecondDouble() - 2.0);
	}
	else {
		FbxTimeSpan TimeLineTimeSpan;
		Scene->GetGlobalSettings().GetTimelineDefaultTimeSpan(TimeLineTimeSpan);

		FrameStartTime = TimeLineTimeSpan.GetStart();
		FrameEndTime = TimeLineTimeSpan.GetStop();
	}

	FrameTime = FrameStartTime;
	
}

void ASNET::Sample::FBXModel::DrawAnimation(ASNET::Graph::Direct3D::BasicEffect* effect)
{
	if (!IsFrame) {
		FrameTime = FrameStartTime;
		IsFrame = true;
	}
	
	FbxAMatrix World;

	std::vector<FbxAMatrix> matrix(BoneCount);
	std::vector<FbxAMatrix> vmatrix(VertexCount);
	//std::vector<FbxVertex>  vertex(VertexCount);
	
	for (int i = 0; i < BoneCount; i++) {
		if (ModelBone[i]->pCluster) {
			if (!ModelBone[i]->pCluster->GetLink()) continue;
			ComputeClusterDeformation(World, Mesh, ModelBone[i]->pCluster, matrix[i], FrameTime, Pose);
			effect->SetBoneAnimationMatrix(i, DirectX::XMMatrixTranspose(LoadFbxMatrix(matrix[i])));
		}
	}



	if (FrameTime >= FrameEndTime) {
		IsFrame = false;
		return;
	}
	

	double render_time = ParentGraph->RenderTime();

	FrameTime.SetSecondDouble(FrameTime.GetSecondDouble() + render_time);

	//delete[] Vertex;
}

DirectX::XMMATRIX ASNET::Sample::FBXModel::FromCenterToOrigin()
{
	return DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(-CenterPos.x, -CenterPos.y, -CenterPos.z));
}

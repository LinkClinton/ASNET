#include "FBXLoader.h"

#pragma comment(lib,"libfbxsdk.lib")








/*
FBX格式的骨骼动画的理解
简直和其他方法有很大区别,他可以设置使用什么动画
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
			for (size_t i = 0; i < Count; i++) {
				model->vertices[pIndex[i]].Weight((float)pWeights[i], VertexCounter[pIndex[i]]);
				std::map<std::string, Bone*>::iterator it = model->BoneNameIndex.find(BoneName);
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
	FbxScene*      Scene = nullptr;

	Model = model;

	Importer = FbxImporter::Create(Manager, "");

	Scene = FbxScene::Create(Manager, "");

	Importer->Initialize(filename, -1, Manager->GetIOSettings());

	Importer->Import(Scene);

	HashBoneName(Scene, nullptr, Model);

	model->Parent.resize(model->BoneCount);

	for (std::map<std::string, Bone*>::iterator it = model->BoneNameIndex.begin(); it != model->BoneNameIndex.end(); it++){
		model->Parent[it->second->id] = it->second->parent;
	}

	FbxNode* root = Scene->GetRootNode();

	for (int i = 0; i < root->GetChildCount(); i++)
		ProcessNode(root->GetChild(i));

	LoadAnimation(Scene);

	graph->LoadBuffer(Model->Buffer, Model->vertices, Model->indices, true);
	

	Model = nullptr;

	Importer->Destroy();

	Scene->Destroy();

	


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
	std::vector<DirectX::XMFLOAT4X4> toParentMatrix;
	std::vector<DirectX::XMFLOAT4X4> toRootMatrix(BoneCount);
	matrix.resize(BoneCount);

	Animations[animation].GetKeyFrame(time, toParentMatrix);

	toRootMatrix[0] = toParentMatrix[0];

	DirectX::XMMATRIX toRoot = DirectX::XMLoadFloat4x4(&toRootMatrix[0]);
	DirectX::XMStoreFloat4x4(&matrix[0], toRoot);

	for (int i = 1; i < BoneCount; i++) {
		DirectX::XMMATRIX toParent = DirectX::XMLoadFloat4x4(&toParentMatrix[i]);
		Bone* parent = Parent[i];
		DirectX::XMMATRIX parentToRoot = DirectX::XMLoadFloat4x4(&toRootMatrix[parent->id]);
		toRoot = DirectX::XMMatrixMultiply(toParent, parentToRoot);
		DirectX::XMStoreFloat4x4(&toRootMatrix[i], toRoot);
		DirectX::XMStoreFloat4x4(&matrix[i], toRoot);
	}

}

DirectX::XMMATRIX ASNET::Sample::FBXModel::FromCenterToOrigin()
{
	return DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(-CenterPos.x, -CenterPos.y, -CenterPos.z));
}

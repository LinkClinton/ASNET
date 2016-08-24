#include "ASNET.Direct3D.Effect.h"

const ASNET::Graph::Word VertexShaderName = L"ASNET.Effect.Vertex.hlsl";
const ASNET::Graph::Word PixelShaderName = L"ASNET.Effect.Pixel.hlsl";
const bool ShaderIsCompiled = false;

const int EffectBufferID = 0;
const int LightsBufferID = 1;
const int DirLightsBufferID = 2;
const int SpotLightsBufferID = 3;
const int PointLightsBufferID = 4;
const int MaterialBufferID = 5;
const int EyePosBufferID = 6;
const int TextureId = 0;

const int ProjMatrixBufferID = 0;
const int ViewMatrixBufferID = 1;
const int WorldMatrixBufferID = 2;
const int NormalMatrixBufferID = 3;


void ASNET::Graph::Direct3D::BasicEffect::UpdateBufferToShader(){
	EffectShader->SendBufferToVertexShader(ProjMatrixBufferID, ProjMatrixBuffer);
	EffectShader->SendBufferToVertexShader(ViewMatrixBufferID, ViewMatrixBuffer);
	EffectShader->SendBufferToVertexShader(WorldMatrixBufferID, WorldMatrixBuffer);
	EffectShader->SendBufferToVertexShader(NormalMatrixBufferID, NormalMatrixBuffer);
	
	EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);


	EffectShader->SendBufferToPixelShader(MaterialBufferID, MaterialBuffer);
	EffectShader->SendBufferToPixelShader(DirLightsBufferID, DirLightsBuffer);
	EffectShader->SendBufferToPixelShader(SpotLightsBufferID, SpotLightsBuffer);
	EffectShader->SendBufferToPixelShader(PointLightsBufferID, PointLightsBuffer);
	EffectShader->SendBufferToPixelShader(EyePosBufferID, EyePosBuffer);
}


DirectX::XMMATRIX ASNET::Graph::Direct3D::BasicEffect::Transpose(DirectX::CXMMATRIX matrix){
	return DirectX::XMMatrixTranspose(matrix);
}

DirectX::XMMATRIX ASNET::Graph::Direct3D::BasicEffect::InverseTranspose(DirectX::CXMMATRIX matrix){
	DirectX::XMMATRIX inv = matrix;
	inv.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(inv);
	return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, inv));
}

ASNET::Graph::Direct3D::BasicEffect::BasicEffect(
	ASNET::Graph::Direct3D::GraphDirect3D * graph){
	ParentGraph = graph;

	EffectIsBegin = false;

	EffectShader = new ASNET::Graph::Direct3D::Shader(VertexShaderName, PixelShaderName,
		ShaderIsCompiled);

	if (!EffectShader->IsCompile)
		ParentGraph->CompileShader(EffectShader);
	else ParentGraph->LoadShader(EffectShader);

	EffectShader->ParentGraph = graph;
	//need change the shader 

	ParentGraph->LoadShaderDataBuffer(&EffectState, sizeof(EffectState), EffectStateBuffer);
	ParentGraph->LoadShaderDataBuffer(&LightsState, sizeof(LightsState), LightsStateBuffer);

	ParentGraph->LoadShaderDataBuffer(nullptr, sizeof(Material), MaterialBuffer);
	ParentGraph->LoadShaderDataBuffer(&DirLights, sizeof(DirLights), DirLightsBuffer);
	ParentGraph->LoadShaderDataBuffer(&SpotLights, sizeof(SpotLights), SpotLightsBuffer);
	ParentGraph->LoadShaderDataBuffer(&PointLights, sizeof(PointLights), PointLightsBuffer);

	ParentGraph->LoadShaderDataBuffer(nullptr, 64, ProjMatrixBuffer);
	ParentGraph->LoadShaderDataBuffer(nullptr, 64, ViewMatrixBuffer);
	ParentGraph->LoadShaderDataBuffer(nullptr, 64, WorldMatrixBuffer);
	ParentGraph->LoadShaderDataBuffer(nullptr, 64, NormalMatrixBuffer);
	ParentGraph->LoadShaderDataBuffer(nullptr, 16, EyePosBuffer);

	/*EffectShader->SendBufferToVertexShader(ProjMatrixBufferID, ProjMatrixBuffer);
	EffectShader->SendBufferToVertexShader(ViewMatrixBufferID, ViewMatrixBuffer);
	EffectShader->SendBufferToVertexShader(WorldMatrixBufferID, WorldMatrixBuffer);
	EffectShader->SendBufferToVertexShader(NormalMatrixBufferID, NormalMatrixBuffer);

	EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);

	EffectShader->SendBufferToPixelShader(DirLightsBufferID, DirLightsBuffer);
	EffectShader->SendBufferToPixelShader(SpotLightsBufferID, SpotLightsBuffer);
	EffectShader->SendBufferToPixelShader(PointLightsBufferID, PointLightsBuffer);*/

	

}

ASNET::Graph::Direct3D::BasicEffect::~BasicEffect(){
	delete EffectShader;
	delete EffectStateBuffer;
	delete LightsStateBuffer;
	delete MaterialBuffer;
	delete DirLightsBuffer;
	delete SpotLightsBuffer;
	delete PointLightsBuffer;
	delete ProjMatrixBuffer;
	delete ViewMatrixBuffer;
	delete WorldMatrixBuffer;
	delete NormalMatrixBuffer;
	delete EyePosBuffer;
}

void ASNET::Graph::Direct3D::BasicEffect::Enable(
	ASNET::Graph::Direct3D::Enable thing){
	switch (thing)
	{
	case ASNET::Graph::Direct3D::Enable::DirLight:
		EffectState.EnableDirLight = true;
		break;
	case ASNET::Graph::Direct3D::Enable::SpotLight:
		EffectState.EnableSpotLight = true;
		break;
	case ASNET::Graph::Direct3D::Enable::PointLight:
		EffectState.EnablePointLight = true;
		break;
	case ASNET::Graph::Direct3D::Enable::Texture:
		EffectState.EnableTexture = true;
		break;
	default:
		break;
	}
	EffectStateBuffer->UpDateBuffer();
	//EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::UnEnable(
	ASNET::Graph::Direct3D::UnEnable thing){
	switch (thing)
	{
	case ASNET::Graph::Direct3D::UnEnable::DirLight:
		EffectState.EnableDirLight = false;
		break;
	case ASNET::Graph::Direct3D::UnEnable::SpotLight:
		EffectState.EnableSpotLight = false;
		break;
	case ASNET::Graph::Direct3D::UnEnable::PointLight:
		EffectState.EnablePointLight = false;
		break;
	case ASNET::Graph::Direct3D::UnEnable::Texture:
		EffectState.EnableTexture = false;
		break;
	default:
		break;
	}
	EffectStateBuffer->UpDateBuffer();
	//EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::DirLightOn(int which,
	ASNET::Graph::Direct3D::DirLight dirlight){
	LightsState[which].DirLightsState = true;
	DirLights[which] = dirlight;

	LightsStateBuffer->UpDateBuffer();
	DirLightsBuffer->UpDateBuffer();

	//EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
	//EffectShader->SendBufferToPixelShader(DirLightsBufferID, DirLightsBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::DirLightOff(int which){
	LightsState[which].DirLightsState= false;
	LightsStateBuffer->UpDateBuffer();
	//EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);

}

void ASNET::Graph::Direct3D::BasicEffect::SpotLightOn(int which,
	ASNET::Graph::Direct3D::SpotLight spotlight){
	LightsState[which].SpotLihtsState = true;
	SpotLights[which] = spotlight;

	LightsStateBuffer->UpDateBuffer();
	SpotLightsBuffer->UpDateBuffer();

	//EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
	//EffectShader->SendBufferToPixelShader(SpotLightsBufferID , SpotLightsBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::SpotLightOff(int which){
	LightsState[which].SpotLihtsState = false;
	LightsStateBuffer->UpDateBuffer();
	//EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::PointLightOn(int which,
	ASNET::Graph::Direct3D::PointLight pointlight){
	LightsState[which].PointLightsState = true;
	PointLights[which] = pointlight;

	LightsStateBuffer->UpDateBuffer();
	PointLightsBuffer->UpDateBuffer();

	//EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
	//EffectShader->SendBufferToPixelShader(PointLightsBufferID, PointLightsBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::PointLightOff(int which){
	LightsState[which].PointLightsState = false;
	LightsStateBuffer->UpDateBuffer();
	//EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::SetMaterial(
	ASNET::Graph::Direct3D::Material  material){
	ParentGraph->g_devicecontext3d->UpdateSubresource(MaterialBuffer->DataBuffer, 0,
		nullptr, &material, 0, 0);
}

void ASNET::Graph::Direct3D::BasicEffect::SetTexture(
	ASNET::Graph::Direct3D::Texture * texture){
	if (EffectIsBegin)
		EffectShader->SendTextureToShader(TextureId, texture);
}

void ASNET::Graph::Direct3D::BasicEffect::SetProjMatrix(
	DirectX::CXMMATRIX matrix){
	ParentGraph->g_devicecontext3d->UpdateSubresource(ProjMatrixBuffer->DataBuffer, 0,
		nullptr, &matrix, 0, 0);
}

void ASNET::Graph::Direct3D::BasicEffect::SetViewMatrix(DirectX::XMVECTOR eyepos,
	DirectX::XMVECTOR lookat){
	DirectX::XMMATRIX matrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(eyepos,
		lookat, DirectX::XMVectorSet(0.f, 1.f, 0.f, 1.f)));
	ParentGraph->g_devicecontext3d->UpdateSubresource(ViewMatrixBuffer->DataBuffer, 0,
		nullptr, &matrix, 0, 0);
	ParentGraph->g_devicecontext3d->UpdateSubresource(EyePosBuffer->DataBuffer, 0,
		nullptr, &eyepos, 0, 0);
}


void ASNET::Graph::Direct3D::BasicEffect::SetWorldMatrix(
	DirectX::CXMMATRIX matrix){
	ParentGraph->g_devicecontext3d->UpdateSubresource(WorldMatrixBuffer->DataBuffer, 0,
		nullptr, &matrix, 0, 0);
	ParentGraph->g_devicecontext3d->UpdateSubresource(NormalMatrixBuffer->DataBuffer, 0,
		nullptr, &InverseTranspose(matrix), 0, 0);

}

void ASNET::Graph::Direct3D::BasicEffect::EffectBegin(){
	EffectIsBegin = true;

	ParentGraph->g_devicecontext3d->VSSetShader(EffectShader->VertexShader, 0, 0);
	ParentGraph->g_devicecontext3d->PSSetShader(EffectShader->PixelShader, 0, 0);

	UpdateBufferToShader();
}

void ASNET::Graph::Direct3D::BasicEffect::EffectEnd(){
	EffectIsBegin = false;
	ParentGraph->g_devicecontext3d->VSSetShader(ParentGraph->UsedShader->VertexShader, 0, 0);
	ParentGraph->g_devicecontext3d->PSSetShader(ParentGraph->UsedShader->PixelShader, 0, 0);
}

ASNET::Graph::Direct3D::BasicEffect::StateEnable::StateEnable(){
	EnableDirLight = false;
	EnableSpotLight = false;
	EnablePointLight = false;
	EnableTexture = false;
}

ASNET::Graph::Direct3D::BasicEffect::StateLights::StateLights(){
	DirLightsState = false;
	SpotLihtsState = false;
	PointLightsState = false;
}

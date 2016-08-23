#include "ASNET.Direct3D.Effect.h"

const ASNET::Graph::Word VertexShaderName = L"";
const ASNET::Graph::Word PixelShaderName = L"";
const bool ShaderIsCompiled = false;

const int EffectBufferID = 0;
const int LightsBufferID = 1;
const int DirLightsBufferID = 2;
const int SpotLightsBufferID = 3;
const int PointLightsBufferID = 4;
const int TextureId = 0;


ASNET::Graph::Direct3D::BasicEffect::BasicEffect(
	ASNET::Graph::Direct3D::GraphDirect3D * graph){
	ParentGraph = graph;

	EffectShader = new ASNET::Graph::Direct3D::Shader(VertexShaderName, PixelShaderName,
		ShaderIsCompiled);

	if (!EffectShader->IsCompile)
		ParentGraph->CompileShader(EffectShader);
	else ParentGraph->LoadShader(EffectShader);

	ParentGraph->LoadShaderDataBuffer(&EffectState, sizeof(EffectState), EffectStateBuffer);
	ParentGraph->LoadShaderDataBuffer(&LightsState, sizeof(LightsState), LightsStateBuffer);

	ParentGraph->LoadShaderDataBuffer(&DirLights, sizeof(DirLights), DirLightsBuffer);
	ParentGraph->LoadShaderDataBuffer(&SpotLights, sizeof(SpotLights), SpotLightsBuffer);
	ParentGraph->LoadShaderDataBuffer(&PointLights, sizeof(PointLights), PointLightsBuffer);

	EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);

	EffectShader->SendBufferToPixelShader(DirLightsBufferID, DirLightsBuffer);
	EffectShader->SendBufferToPixelShader(SpotLightsBufferID, SpotLightsBuffer);
	EffectShader->SendBufferToPixelShader(PointLightsBufferID, PointLightsBuffer);

}

ASNET::Graph::Direct3D::BasicEffect::~BasicEffect(){
	delete EffectShader;
	delete EffectStateBuffer;
	delete LightsStateBuffer;
	delete DirLightsBuffer;
	delete SpotLightsBuffer;
	delete PointLightsBuffer;
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
	EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
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
	EffectShader->SendBufferToPixelShader(EffectBufferID, EffectStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::DirLightOn(int which,
	ASNET::Graph::Direct3D::DirLight dirlight){
	LightsState.DirLightsState[which] = true;
	DirLights[which] = dirlight;

	LightsStateBuffer->UpDateBuffer();
	DirLightsBuffer->UpDateBuffer();

	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
	EffectShader->SendBufferToPixelShader(DirLightsBufferID, DirLightsBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::DirLightOff(int which){
	LightsState.DirLightsState[which] = false;
	LightsStateBuffer->UpDateBuffer();
	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);

}

void ASNET::Graph::Direct3D::BasicEffect::SpotLightOn(int which,
	ASNET::Graph::Direct3D::SpotLight spotlight){
	LightsState.SpotLihtsState[which] = true;
	SpotLights[which] = spotlight;

	LightsStateBuffer->UpDateBuffer();
	SpotLightsBuffer->UpDateBuffer();

	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
	EffectShader->SendBufferToPixelShader(SpotLightsBufferID , SpotLightsBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::SpotLightOff(int which){
	LightsState.SpotLihtsState[which] = false;
	LightsStateBuffer->UpDateBuffer();
	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::PointLightOn(int which,
	ASNET::Graph::Direct3D::PointLight pointlight){
	LightsState.PointLightsState[which] = true;
	PointLights[which] = pointlight;

	LightsStateBuffer->UpDateBuffer();
	PointLightsBuffer->UpDateBuffer();

	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
	EffectShader->SendBufferToPixelShader(PointLightsBufferID, PointLightsBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::PointLightOff(int which){
	LightsState.PointLightsState[which] = false;
	LightsStateBuffer->UpDateBuffer();
	EffectShader->SendBufferToPixelShader(LightsBufferID, LightsStateBuffer);
}

void ASNET::Graph::Direct3D::BasicEffect::SetTexture(
	ASNET::Graph::Direct3D::Texture * texture){
	EffectShader->SendTextureToShader(TextureId, texture);
}

ASNET::Graph::Direct3D::BasicEffect::StateEnable::StateEnable(){
	EnableDirLight = false;
	EnableSpotLight = false;
	EnablePointLight = false;
	EnableTexture = false;
}

ASNET::Graph::Direct3D::BasicEffect::StateLights::StateLights(){
	memset(DirLightsState, false, sizeof(DirLightsState));
	memset(SpotLihtsState, false, sizeof(SpotLihtsState));
	memset(PointLightsState, false, sizeof(PointLightsState));
}

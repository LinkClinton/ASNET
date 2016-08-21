struct PixelIn
{
	float4 posH: SV_POSITION;
	float3 pos: POSITION;
	float2 tex: TEXCOORD;
	float4 Color:COLOR;
};
cbuffer IsUsedTex:register(b0) {
	bool IsUsedTex = false;
}
Texture2D Tex : register(s0);
SamplerState samTex
{
	Filter = MIN_MAG_MIP_LINEAR;

	//Filter = MIN_POINT_MAG_LINEAR_MIP_POINT;
};

float4 main(PixelIn In) :SV:SV_TARGET{
	float4 TexColor;
TexColor = Tex.Sample(samTex, In.tex);
//clip(TexColor.a - 0.1f);
return TexColor;
}
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
};

float4 main(PixelIn In) :SV_TARGET{
	//return float4(1,0,0,1);
	float4 TexColor;
	TexColor = Tex.Sample(samTex, In.tex);
//clip(TexColor.a - 0.1f);
	return TexColor	;
}
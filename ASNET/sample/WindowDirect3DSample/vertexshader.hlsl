cbuffer ProjectionMatrix:register(b0){
	matrix Projection;
};
cbuffer WorldMatrix:register(b1) {
	matrix World;
}
cbuffer ViewMatrix : register(b2) {
	matrix View;
}

struct VertexIn {
	float3 pos:POSITION;
	float3 normal:NORMAL;
	float2 tex:TEXCOORD;
	float4 Color:COLOR;
};
struct VertexOut
{
	float4 posH: SV_POSITION; 
	float3 pos: POSITION;  
	float2 tex: TEXCOORD;  
	float4 Color:COLOR;
};
VertexOut main(VertexIn In){
VertexOut Out;

Out.pos = mul(float4(In.pos, 1.f), World).xyz;
Out.posH = mul(float4(In.pos, 1.f), World);
Out.posH = mul(Out.posH, View);
Out.posH = mul(Out.posH, Projection);

Out.tex = In.tex;
Out.Color = In.Color;
return Out;
}
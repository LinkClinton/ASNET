 cbuffer ProjMatrix:register(b0) {
	matrix proj;
}
cbuffer ViewMatrix : register(b1) {
	matrix view;
}
cbuffer WorldMatrix : register(b2) {
	matrix world;
}
cbuffer NormalMatrix : register(b3) {
	matrix normal;
}
struct VertexIn {
	float3 pos:POSITION;
	float3 normal:NORMAL;
	float2 tex:TEXCOORD;
	float4 Color:COLOR;
};
struct VertexOut {
	float4 posH: SV_POSITION;
	float3 pos: POSITION;
	float2 tex: TEXCOORD;
	float3 normal: NORMAL;
	float4 Color:COLOR;
};
VertexOut main(VertexIn In) {
	VertexOut Out;
	Out.pos = mul(float4(In.pos, 1.f), world).xyz;
	Out.posH = mul(float4(In.pos, 1.f), world);
	Out.posH = mul(Out.posH, view);
	Out.posH = mul(Out.posH, proj);
	Out.tex = In.tex;
	Out.normal = mul(float4(In.normal, 1.f), normal).xyz;
	Out.Color = In.Color;
	return Out;
}

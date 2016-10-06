#include"ASNET.Effect.hlsli"
static const int MaxAnimationMatrix = 200;
cbuffer _EffectState:register(b0) {
	EffectStates EffectState;
}
cbuffer ProjMatrix : register(b1) {
	matrix proj;
}
cbuffer ViewMatrix : register(b2) {
	matrix view;
}
cbuffer WorldMatrix : register(b3) {
	matrix world;
}
cbuffer NormalMatrix : register(b4) {
	matrix normal;
}
cbuffer BoneAnimationMatrix : register(b5) {
	matrix BoneMatrix[MaxAnimationMatrix];
}
VertexOut main(VertexIn In) {
	VertexOut Out;
	if (EffectState.EnableAnimation) {
		matrix Matrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		float weights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float3 posL = float3(0.0f, 0.0f, 0.0f);
		float3 normalL = float3(0.0f, 0.0f, 0.0f);
		weights[0] = In.weights.x;
		weights[1] = In.weights.y;
		weights[2] = In.weights.z;
		weights[3] = 1.0f - weights[0] - weights[1] - weights[2];

		//blend skin vertex
		[unroll]
		for (int i = 0; i < 4; ++i) {
			if (weights[i] == 0.0) continue;
			posL += weights[i] * mul(float4(In.pos, 1.0f), BoneMatrix[In.BoneIndices[i]]).xyz;
			normalL += weights[i] * mul(In.normal, (float3x3)BoneMatrix[In.BoneIndices[i]]);
		}
		Out.pos = mul(float4(posL, 1.f), world).xyz;
		Out.posH = mul(float4(posL, 1.f), world);
		Out.posH = mul(Out.posH, view);
		Out.posH = mul(Out.posH, proj);
		Out.tex = In.tex;
		Out.normal = mul(float4(In.normal, 1.f), normal).xyz;
		Out.Color = In.Color;
		return Out;
	}

	Out.pos = mul(float4(In.pos, 1.f), world).xyz;
	Out.posH = mul(float4(In.pos, 1.f), world);
	Out.posH = mul(Out.posH, view);
	Out.posH = mul(Out.posH, proj);
	Out.tex = In.tex;
	Out.normal = mul(float4(In.normal, 1.f), normal).xyz;
	Out.Color = In.Color;
	return Out;
}

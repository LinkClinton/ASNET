#include"ASNET.Effect.Pixel.hlsli"
float4 main(PixelIn In): SV_TARGET{
	float3 ToEye = EyePos.xyz - In.pos;
	ToEye = normalize(ToEye);
	float3 normal = normalize(In.normal);
	float4 A = float4(0.f, 0.f, 0.f, 0.f);
	float4 D = float4(0.f, 0.f, 0.f, 0.f);
	float4 S = float4(0.f, 0.f, 0.f, 0.f);
	if (EffectState.EnableDirLight) {
		for (int i = 0; i < MaxLights; i++)
			if (EffectLights[i].DirLightsState) {
				float4 ambient, diff, spec;
				ComputeDirLight(material, DirLights[i], normal, ToEye, ambient, diff, spec);
				A += ambient;
				D += diff;
				S += spec;
			}
	}
	if (EffectState.EnableSpotLight) {
		for (int i = 0; i < MaxLights; i++)
			if (EffectLights[i].SpotLihtsState) {
				float4 ambient, diff, spec;
				ComputeSpotLight(material, SpotLights[i], normal, In.pos, ToEye, ambient, diff, spec);
				A += ambient;
				D += diff;
				S += spec;
			}
	}
	if (EffectState.EnablePointLight) {
		for (int i = 0; i < MaxLights; i++)
			if (EffectLights[i].PointLightsState) {
				float4 ambient, diff, spec;
				ComputePointLight(material, PointLights[i], normal, In.pos, ToEye, ambient, diff, spec);
				A += ambient;
				D += diff;
				S += spec;
			}
	}
	if (EffectState.EnableTexture) {
		if (EffectState.EnableDirLight || EffectState.EnablePointLight || EffectState.EnableSpotLight) {
			float4 litColor = A + D + S;
			litColor.a = material.diffuse.a;
			float4 texColor = Tex.Sample(samTex, In.tex);
			float4 FinaColor = texColor*(A + D) + S;
			FinaColor.a = texColor.a*material.diffuse.a;
			return FinaColor;
		}
		else {
			float4 texColor = Tex.Sample(samTex, In.tex);
			return Tex.Sample(samTex, In.tex);
		}
		
	}
	else {
		if (EffectState.EnablePointLight || EffectState.EnablePointLight || EffectState.EnableSpotLight) {
			float4 litColor = A + D + S;
			litColor.a = material.diffuse.a;
			return litColor;
		}
		else {
			return In.Color;
		}
	}
	
}
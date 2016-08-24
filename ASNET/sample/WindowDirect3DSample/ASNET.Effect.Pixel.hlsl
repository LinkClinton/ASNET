static int MaxLights = 16;	
struct PixelIn{
	float4 posH: SV_POSITION;
	float3 pos: POSITION;
	float2 tex: TEXCOORD;
	float3 normal: NORMAL;
	float4 Color:COLOR;
};
struct DirLight {
	float4 ambient;
	float4 diffuse;
	float4 specular;

	float3 dir;

	float  unsed;
};
struct SpotLight {
	float4 ambient;
	float4 diffuse;
	float4 specular;

	float3 dir;
	float  range;

	float3 pos;
	float  spot;

	float3 att;
	float  theta;
};
struct PointLight {
	float4 ambient;
	float4 diffuse;
	float4 specular;

	float3 pos;
	float  range;

	float3 att;

	float  unused;
};
struct Material {
	float4 ambient;
	float4 diffuse;
	float4 specular; //第四个元素是材质光滑
};
struct EffectStates {
	int EnableDirLight;
	int EnableSpotLight;
	int EnablePointLight;
	int EnableTexture;
};
struct EffectLights_ {
	int DirLightsState;
	int SpotLihtsState;
	int PointLightsState;
	int unused;
};
cbuffer _EffectState:register(b0) {
	EffectStates EffectState;
}
cbuffer _EffectLights:register(b1) {
	EffectLights_ EffectLights[16];
}
cbuffer EffectDirLights : register(b2) {
	DirLight DirLights[16];
}
cbuffer EffectSpotLights : register(b3) {
	SpotLight SpotLights[16];
}
cbuffer EffectPointLights : register(b4) {
	PointLight PointLights[16];
}
cbuffer EffectMaterial : register(b5) {
	Material material;
}
cbuffer EffectEyePos : register(b6) {
	float4 EyePos;
}
Texture2D Tex : register(s0);
SamplerState samTex{
	Filter = MIN_MAG_MIP_LINEAR;
};
void ComputeDirLight(Material mat,
	DirLight dirLight, float3 normal, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 specular) {

	ambient = float4(0.0f, 0.0f, 0.f, 0.f);
	diffuse = float4(0.f, 0.f, 0.f, 0.f);
	specular = float4(0.f, 0.f, 0.f, 0.f);


	ambient = mat.ambient * dirLight.ambient;

	float diffFactor = -dot(normal, dirLight.dir);


	[flatten]
	if (diffFactor > 0) {

		diffuse = mat.diffuse * dirLight.diffuse * diffFactor;

		float3 refLight = reflect(dirLight.dir, normal);
		float specFactor = pow(max(dot(refLight, toEye), 0.f), mat.specular.w);
		specular = mat.specular * dirLight.specular * specFactor;
	}
}

void ComputeSpotLight(Material mat,
	SpotLight L, float3 normal, float3 position, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 specular) {
	
	ambient = float4(0.f, 0.f, 0.f, 0.f);
	diffuse = float4(0.f, 0.f, 0.f, 0.f);
	specular = float4(0.f, 0.f, 0.f, 0.f);

	
	float3 dir = L.pos - position;

	float dist = length(dir);

	
	if (dist > L.range)
		return;


	dir /= dist;


	float att = 1 / (L.att.x + L.att.y*dist + L.att.z*dist*dist);

	float tmp = -dot(dir, L.dir);
	if (tmp < cos(L.theta))
		return;
	float spotFactor = pow(max(tmp, 0.f), L.spot);

	ambient = mat.ambient * L.ambient * att * spotFactor;

	
	float diffFactor = dot(dir, normal);

	
	if (diffFactor > 0){
		
		diffuse = mat.diffuse * L.diffuse * diffFactor * att * spotFactor;

		float3 refLight = reflect(-dir, normal);
		
		float specFactor = pow(max(dot(refLight, toEye), 0.f), mat.specular.w);

		
		specular = mat.specular * L.specular * specFactor * att * spotFactor;
	}
}

void ComputePointLight(Material mat,
	PointLight pLight, float3 normal, float3 position, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 specular) {

	ambient = float4(0.f, 0.f, 0.f, 0.f);
	diffuse = float4(0.f, 0.f, 0.f, 0.f);
	specular = float4(0.f, 0.f, 0.f, 0.f);


	float3 dir = pLight.pos - position;


	float dist = length(dir);


	if (dist > pLight.range)
		return;


	dir /= dist;


	float att = 1 / (pLight.att.x + pLight.att.y*dist + pLight.att.z*dist*dist);


	ambient = mat.ambient * pLight.ambient * att;


	float diffFactor = dot(dir, normal);


	if (diffFactor > 0) {

		diffuse = mat.diffuse * pLight.diffuse * diffFactor * att;

		float3 refLight = reflect(-dir, normal);

		float specFactor = pow(max(dot(refLight, toEye), 0.f), mat.specular.w);


		specular = mat.specular * pLight.specular * specFactor * att;
	}
}

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
		float4 litColor = A + D + S;
		litColor.a = material.diffuse.a;
		float4 texColor = Tex.Sample(samTex, In.tex);
		float4 FinaColor = texColor*(A + D) + S;
		FinaColor.a = texColor.a*material.diffuse.a;

		return FinaColor;
	}
	else {
		float4 litColor = A + D + S;
		litColor.a = material.diffuse.a;
		return litColor;
	}
	
}
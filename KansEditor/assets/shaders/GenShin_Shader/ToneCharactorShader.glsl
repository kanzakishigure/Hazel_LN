#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCroods;
layout(location = 3) in vec4 a_BaseColor;
layout(location = 3) in vec3 a_Tangent;
uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;
out vec3 V_Normal;
out vec2 V_TexCroods;
out vec4 V_BaseColor;
out vec3 V_FragPos;
void main()
{
	// gl_Position is in the screen space
	gl_Position = U_ViewProjection*U_Transform*vec4(a_Position, 1.0);

	V_TexCroods = a_TextureCroods;
	V_BaseColor = vec4(1.0);
	//（Moldle-1）T
	//the normal is in worldspcae
	V_Normal = mat3(transpose(inverse(U_Transform)))*a_Normal;
	//Get the position in worldspcae
	vec4 pos = U_Transform*vec4(a_Position, 1.0);
	V_FragPos = vec3(pos.xyz)/pos.w;
}

#type fragment
#version 330 core
layout(location = 0) out vec4 O_Color;
layout(location = 1) out vec4 O_Normal;
#define PI 3.1415926

struct Material
{
	sampler2D U_DiffuseTexture;
	sampler2D U_ToneLightMap;
	sampler2D U_ToneRampMap;
};

struct DirLight
{
	vec3 LightDir;
	vec3 Diffuse_Intensity;
	vec3 Specular_Intensity;
	vec3 Ambient_Intensity;
};
struct PointLight
{
	vec3 Position;
	vec3 Diffuse_Intensity;
	vec3 Specular_Intensity;
	vec3 Ambient_Intensity;
};

//ToneShader parameter
uniform vec4 U_ShadowMultColor;
uniform vec4 U_DarkShadowMultColor;
uniform float U_ShadowArea;
uniform float U_FixDarkShadow;
uniform float U_ShadowSmooth;
uniform float U_DarkShadowSmooth;
uniform float U_DarkShadowArea;

//shading point Material
uniform Material material;
//scene info 
uniform DirLight dirLight;
uniform PointLight pointLight;

//geometry attribute
in vec2 V_TexCroods;
in vec4 V_BaseColor;
//World space attribute
in vec3 V_FragPos;
in vec3 V_Normal;
//camera attribute
uniform vec3 U_ViewPos;

void main()
{
	// properties
    vec3 norm = normalize(V_Normal);
    vec3 viewDir = normalize(U_ViewPos - V_FragPos );
	vec3 lightdir = normalize(pointLight.Position - V_FragPos);
	vec3 HalfVector = normalize(lightdir + viewDir);

	vec4 BaseColor = texture2D(material.U_DiffuseTexture,V_TexCroods);
    vec4 LightMapColor = texture2D(material.U_ToneLightMap,V_TexCroods);
	//Prep
		//lambert(LoN)
		float lambert =  dot(lightdir,norm);
		lambert = lambert*0.5 + 0.5;
		float NoV = dot(viewDir,norm);
		vec3 ShadowColor = BaseColor.rgb * U_ShadowMultColor.rgb;
		vec3 DarkShadowColor = BaseColor.rgb * U_DarkShadowMultColor.rgb;

	float SWeight = (LightMapColor.g * V_BaseColor.r + lambert) * 0.5 + 1.125;
	float SFactor = floor(SWeight - U_ShadowArea);
	
	vec3 ShallowShadowColor = SFactor * BaseColor.rgb + (1 - SFactor) * ShadowColor.rgb;
	
	SFactor = floor(SWeight - U_DarkShadowArea);
	DarkShadowColor = SFactor * (U_FixDarkShadow * ShadowColor + (1 - U_FixDarkShadow) * ShallowShadowColor) + (1 - SFactor) * DarkShadowColor;

	float rampS = smoothstep(0, U_ShadowSmooth, lambert - U_ShadowArea);
	float rampDS = smoothstep(0, U_DarkShadowSmooth, lambert - U_DarkShadowArea);
	ShallowShadowColor.rgb = mix(ShadowColor, BaseColor.rgb, rampS);
	DarkShadowColor.rgb = mix(DarkShadowColor.rgb, ShadowColor, rampDS);

	SFactor = floor(LightMapColor.g * V_BaseColor.r + 0.9f);
	vec4 FinalColor = vec4(1.0);
	FinalColor.rgb = SFactor * ShallowShadowColor + (1 - SFactor) * DarkShadowColor;

	O_Color = FinalColor;
	
	
}
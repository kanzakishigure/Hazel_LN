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
	V_BaseColor = a_BaseColor;

	//the V_Normal is in worldspcae
	//（Moldle-1）T
	V_Normal = mat3(transpose(inverse(U_Transform)))*a_Normal;
	//Get the position in worldspcae
	V_FragPos = mat3(U_Transform)*a_Position;
}

#type fragment
#version 330 core
layout(location = 0) out vec4 O_Color;
layout(location = 1) out vec4 O_Normal;
#define PI 3.1415926

struct Material
{
	sampler2D U_DiffuseTexture;
	sampler2D U_SpecularTexture;
	sampler2D U_NormalTexture;
	sampler2D U_EmissionTexture;
	float U_Shininess;

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

//shading point Material
uniform Material material;
//scene info 
uniform DirLight dirLight;
uniform PointLight pointLight;

uniform float U_BoundSharp;
uniform float U_DividLineH;
uniform float U_DividLineM;
uniform float U_DividLineL;
uniform float U_DarkColor;
//geometry attribute
in vec2 V_TexCroods;
in vec4 V_BaseColor;

//World space attribute
in vec3 V_FragPos;
in vec3 V_Normal;

//camera attribute
uniform vec3 U_ViewPos;

float sigmoid(float x, float center, float sharp) 
{
	float s;
	s = 1 / (1 + pow(100000, (-3 * sharp * (x - center))));
	return s;
}
vec4 HDRColormap(vec3 hdrColor)
{
	const float gamma = 2.2;
    // Reinhard色调映射
    vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
    // Gamma校正
    mapped = pow(mapped, vec3(1.0 / gamma));
	return vec4(mapped, 1.0);
}
void main()
{
	// properties
    vec3 norm = normalize(V_Normal);
    vec3 viewDir = normalize(U_ViewPos - V_FragPos);

	vec3 lightdir = normalize(pointLight.Position - V_FragPos);;
	float NoL = max(dot(lightdir,norm),0.0);

	vec3 HalfVector = lightdir + viewDir;
	HalfVector = normalize(HalfVector);
	float spec = dot(norm,HalfVector);
	spec = mix(0,1,smoothstep(-0.001,+0.001,spec-U_BoundSharp));

	float HLightSig = sigmoid(NoL, U_DividLineH, U_BoundSharp);
	float MidSig = sigmoid(NoL, U_DividLineM,U_BoundSharp);
	float DarkSig = sigmoid(NoL, U_DividLineL,U_BoundSharp);
	float HLightWin = HLightSig;
	float MidLWin = MidSig - HLightSig;
	float MidDWin = DarkSig - MidSig;
	float DarkWin = 1 - DarkSig;
	float Intensity = HLightWin * 1.0 + MidLWin * 0.8 + MidDWin * 0.5 + DarkWin * 0.3;
	vec4 Texcolor = texture2D(material.U_DiffuseTexture,V_TexCroods);
	/*
	float rgbBright = Texcolor.r*0.2126+Texcolor.g*0.7152+Texcolor.b*0.0722;
	rgbBright*=Intensity;
	Texcolor = vec4(Texcolor.r+Intensity/0.2126,Texcolor.g+Intensity/0.7152,Texcolor.b+Intensity/0.0722,1.0);
	*/
	O_Color = vec4(Texcolor.rgb*Intensity,Texcolor.a);
	//O_Color = vec4(vec3(Intensity),1.0);
	//O_Color = vec4(vec3(NoL),1.0);
	O_Color += vec4(vec3(spec),1.0);
	O_Normal = vec4(V_Normal,1.0);

	//O_Normal = vec4(result.r*0.2126+result.g*0.7152+result.b*0.0722);
}
#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCroods;
layout(location = 3) in vec4 a_BaseColor;
uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;
void main()
{
	// gl_Position is in the screen space
	gl_Position = U_ViewProjection*U_Transform*vec4(a_Position, 1.0);

}

#type fragment
#version 330 core
layout(location = 0) out vec4 O_Color;

uniform sampler2D ColorAttachment;
uniform sampler2D DepthAttachment;
uniform sampler2D NormalTexture;
//hack
float DepthSensitivity = 0.75;
float NormalsSensitivity = 0.25;
float ColorSensitivity = 0.65;
vec4 OutlineColor = vec4(1.0);
void main()
{
    vec2 texcoords = gl_FragCoord.xy;
    vec2 Samplerpos[4];
    vec3 normalSamples[4];
    vec4 colorSamples[4]
;   float depthSamples[4];

    Samplerpos[0] = texcoords-vec2(1.0);
    Samplerpos[1] = texcoords+vec2(1.0);
    Samplerpos[2] = vec2(texcoords.x+1.0,texcoords.y-1.0);
    Samplerpos[3] = vec2(texcoords.x-1.0,texcoords.y+1.0);

    for(int i = 0; i < 4 ; i++)
    {
        depthSamples[i] = texture2D(DepthAttachment,Samplerpos[i]).r;
        normalSamples[i] = texture2D(NormalTexture,Samplerpos[i]).xyz;
        colorSamples[i] = texture2D(ColorAttachment,Samplerpos[i]).rgba;
    }

    // Depth
        //权重
    float depthFiniteDifference0  = depthSamples[0] - depthSamples[2];
    float depthFiniteDifference1  = depthSamples[1] - depthSamples[3];

    float edgeDepth = sqrt(pow(depthFiniteDifference0, 2) + pow(depthFiniteDifference1, 2)) * 100;
    float depthThreshold = (1/DepthSensitivity) * depthSamples[0];
    edgeDepth = edgeDepth > depthThreshold ? 1 : 0;
    // Normals
    vec3 normalFiniteDifference0 = normalSamples[1] - normalSamples[0];
    vec3 normalFiniteDifference1 = normalSamples[3] - normalSamples[2];

    float edgeNormal = sqrt(dot(normalFiniteDifference0, normalFiniteDifference0) + dot(normalFiniteDifference1, normalFiniteDifference1));
    edgeNormal = edgeNormal > (1/NormalsSensitivity) ? 1 : 0;
    // Color
    vec4 colorFiniteDifference0 = colorSamples[1] - colorSamples[0];
    vec4 colorFiniteDifference1 = colorSamples[3] - colorSamples[2];
    float edgeColor = sqrt(dot(colorFiniteDifference0, colorFiniteDifference0) + dot(colorFiniteDifference1, colorFiniteDifference1));
	edgeColor = edgeColor > (1/ColorSensitivity) ? 1 : 0;

    float edge = max(edgeDepth, max(edgeNormal, edgeColor));

    vec4 original = texture2D(ColorAttachment,texcoords);	
    //O_Color = ((1 - edge) * original) + (edge * mix(original, OutlineColor,  OutlineColor.a));
    //O_Color = vec4(1.0);
    O_Color =vec4(gl_FragCoord);
}
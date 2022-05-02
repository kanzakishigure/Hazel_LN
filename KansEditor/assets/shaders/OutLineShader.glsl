#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCroods;
layout(location = 3) in vec4 a_BaseColor;
layout(location = 4) in vec3 a_Tangent;
uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;
float rand(float x)
{
    float y = fract(sin(x)*100000.0);
    return y;
}
float noise(float x)
{
    float i = floor(x); 
    float f = fract(x);  
    float u = f * f * (3.0 - 2.0 * f ); // custom cubic curve
    float y = mix(rand(i), rand(i + 1.0), u); // using it in the interpolation
    return y ;
}
void main()
{
	// gl_Position is in the screen space
    vec4 Normal =  U_ViewProjection*vec4(mat3(transpose(inverse(U_Transform)))*a_Normal,1.0);
    //处理背面遮挡问题
    Normal.z = -0.5;
    Normal = normalize(Normal);
    vec4 Tangent =  U_ViewProjection*vec4(mat3(transpose(inverse(U_Transform)))*a_Tangent,1.0);
    vec4 o_Position = U_ViewProjection*U_Transform*vec4(a_Position, 1.0);
	gl_Position = vec4(o_Position.xy + Normal.xy*o_Position.w*0.005*(0.8+0.2*noise(a_Position.x+a_Position.y+a_Position.z)),o_Position.z,o_Position.w);

}

#type fragment
#version 330 core
layout(location = 0) out vec4 O_Color;

vec4 OutLineColor = vec4(0, 0, 0, 1);
void main()
{
    O_Color =vec4(OutLineColor);
}
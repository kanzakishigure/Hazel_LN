#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCroods;
layout(location = 3) in vec4 a_BaseColor;
uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;
out vec3 V_Normal;
out vec2 V_TexCroods;
out vec4 V_BaseColor;
void main()
{
	gl_Position = U_ViewProjection*U_Transform*vec4(a_Position, 1.0);
	V_TexCroods = a_TextureCroods;
	V_BaseColor = a_BaseColor;
	V_Normal = a_Normal;
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec3 V_Normal;
in vec2 V_TexCroods;
in vec4 V_BaseColor;
void main()
{
	color = vec4(V_Normal,1.0);
}
#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;

void main()
{
	gl_Position = U_ViewProjection * U_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 U_Color;
void main()
{
	color = U_Color;
}
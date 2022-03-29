#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 V_color;

uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;
void main()
{
    gl_Position = U_ViewProjection*U_Transform*vec4(aPos,1.0);
    V_color = aColor;
}



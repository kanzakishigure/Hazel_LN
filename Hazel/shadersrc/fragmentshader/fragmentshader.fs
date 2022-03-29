#version 330
out vec4 fragcolor;

in vec4 V_color;
uniform vec3 U_Color;
void main()
{
   
    fragcolor  = mix(V_color,vec4(U_Color,1.0),0.5);
}
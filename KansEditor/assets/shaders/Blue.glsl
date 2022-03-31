#type fragment
#version 330 core 
out vec4 fragcolor;
in vec2 croods;
uniform vec4 U_Value;
uniform sampler2D U_Texture;
void main()
{
    vec3 uv = vec3((croods.x+1.0)/2.0,(croods.y+1.0)/2.0,1);
    //fragcolor  =U_Value*mix(vec4(0.2,0.8,0.7,1.0),vec4(uv,1.0),0.5);
    fragcolor = texture(U_Texture,croods);
        
}

#type vertex
#version 330 core 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aText;
out vec2 croods;
uniform mat4 U_ViewProjection;
uniform mat4 U_Transform;
void main()
{
    gl_Position = U_ViewProjection*U_Transform*vec4 (aPos,1.0);
    croods = aText;
   
}
// Version du GLSL
 
#version 100

// Entrée Shader (liée au tableau Vertex Attrib)
attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec2 vTexCoord0;

// Fonction main
void main()
{
    // Position finale du vertex
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    
    vTexCoord0 = in_TexCoord0;
}
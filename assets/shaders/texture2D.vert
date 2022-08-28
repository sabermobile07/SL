// Version du GLSL
#version 100


// Entrée Shader (liée au tableau Vertex Attrib)
attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 model;

varying vec2 vTexCoord0;

// Fonction main
void main()
{
    vTexCoord0 = in_TexCoord0;
    // Position finale du vertex
    gl_Position = projection * model * vec4(in_Vertex.xy, 0.0, 1.0);
}
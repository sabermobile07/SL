// Version du GLSL
 
#version 100


// Entrée Shader (liée au tableau Vertex Attrib)
attribute vec3 in_Vertex;
attribute vec3 in_Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec3 vNorm;

// Fonction main
void main()
{
    // Position finale du vertex
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    
    vNorm = in_Normal;
}

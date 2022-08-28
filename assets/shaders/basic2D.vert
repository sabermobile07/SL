// Version du GLSL
 
#version 100


// Entrée Shader (liée au tableau Vertex Attrib)
attribute vec3 in_Vertex;
attribute vec4 in_Color;

uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

varying vec3 vColor;

// Fonction main
void main()
{
    // Position finale du vertex
    gl_Position = projection * model * vec4(in_Vertex.xy, 0.0, 1.0);
    
    vColor = color;
}

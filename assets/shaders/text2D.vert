#version 100


// Entrée Shader (liée au tableau Vertex Attrib)
attribute vec4 in_Vertex;

uniform mat4 projection;

varying vec2 vTexCoord0;

// Fonction main
void main()
{
    // Position finale du vertex
    //gl_Position = projection * vec4(in_Vertex.xy, 0.1, 1.0);
    gl_Position = vec4(in_Vertex.xy, 0.0, 1.0);
    
    vTexCoord0 = in_Vertex.zw;
}
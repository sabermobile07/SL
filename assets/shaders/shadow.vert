// Version du GLSL

#version 100

// Entre Shader (lie au tableau Vertex Attrib)
attribute vec3 in_Vertex;

// Variable uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Fonction main
void main()
{
	// Position finale du vertex
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

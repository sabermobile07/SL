// Version du GLSL

#version 100

// Entre Shader (lie au tableau Vertex Attrib)
attribute vec3 in_Vertex; 
attribute vec3 in_Normal;
attribute vec2 in_TexCoord0;

// Variable uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 transpose_inverse_model;

// Sortie
varying vec3 position;
varying vec3 normal;
varying vec2 vTexCoord0;

// Fonction main
void main()
{
	const int light_total = 3;
	// Envoi de la couleur au Fragment Shader
	position = vec3(model * vec4(in_Vertex, 1.0));
	normal = in_Normal * mat3(transpose_inverse_model);
	vTexCoord0 = in_TexCoord0;
	
	// Position finale du vertex
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

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

// Sortie
varying vec2 coordTexture;

// Fonction main
void main()
{
	coordTexture = in_TexCoord0;
	// Envoi de la couleur au Fragment Shader
	
	// Position finale du vertex
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

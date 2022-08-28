// Version du GLSL

#version 100

// Entre Shader (lie au tableau Vertex Attrib)
attribute vec3 in_Vertex; 
attribute vec3 in_Color;
attribute vec3 in_Normal;
attribute vec2 in_TexCoord0;

// Variable uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 transpose_inverse_model;
uniform vec3 in_view_position;

// Sortie
varying vec3 position;
varying vec3 color;
varying vec3 normal;
varying vec3 view_position;
varying vec2 texCoord0;

// Fonction main
void main()
{
	texCoord0 = in_TexCoord0;
	// Envoi de la couleur au Fragment Shader
	position = vec3(model * vec4(in_Vertex, 1.0));
	color = in_Color;
	
	normal = normalize(in_Normal);
	
	view_position = in_view_position;
	
	// Position finale du vertex
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

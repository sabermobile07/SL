// Version du GLSL

#version 100

// Entre Shader (lie au tableau Vertex Attrib)
attribute vec3 in_Vertex; 
attribute vec3 in_Color;
attribute vec3 in_Normal;

// Variable uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Light model
uniform vec3 in_Light_position;
uniform vec3 in_Light_color;
uniform float in_Shininess;
uniform vec3 in_Ambient_color;

// Sortie
varying vec3 position;
varying vec4 v_color;
varying vec3 normal;

// Fonction main
void main()
{
	position = vec3( view * model * vec4(in_Vertex, 1.0) );
	normal = vec3( view * model * vec4(in_Normal, 0.0) );
	v_color = vec4(1.0, 0.3, 0.3, 1.0);
	
	// Position finale du vertex
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

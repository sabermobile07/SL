// Version du GLSL

#version 100

// Entre Shader (lie au tableau Vertex Attrib)
attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;

// Variable uniform
uniform mat4 lightProj;
uniform mat4 lightView;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec2 vTexCoord0;
varying vec4 vPos;
varying vec4 vPosLight;

// Fonction main
void main()
{
	vTexCoord0 = in_TexCoord0;
	vPos = projection * view * model * vec4(in_Vertex, 1.0);
	vPosLight = lightProj * lightView * model * vec4(in_Vertex, 1.0);
	// Position finale du vertex
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
	//gl_Position = vec4(in_Vertex, 1.0);
}

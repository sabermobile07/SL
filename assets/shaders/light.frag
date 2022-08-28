// Version du GLSL
 
#version 100

// Précision pour les variables float
precision mediump float;

varying vec2 vTexCoord0;

// Uniform
uniform sampler2D texture0;
uniform mat4 view;
uniform vec3 lightPos;
uniform vec3 lightDir;

// Fonction main
void main()
{
    //AMBIENT
	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * vec3(0.3f, 0.5f, 0.8f);

    // Couleur finale du pixel
    //gl_FragColor = texture2D(texture0, vTexCoord0);
    gl_FragColor = vec4(ambient, 1.0f) * texture2D(texture0, vTexCoord0);
}
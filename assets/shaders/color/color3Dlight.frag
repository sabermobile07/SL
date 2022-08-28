// Version du GLSL
#version 100

// Precision pour les variables float
precision mediump float; 

// Entre
varying vec3 position;
varying vec3 color;
varying vec3 normal;
varying vec3 view_position;

uniform vec3 in_light_position;
uniform vec3 in_light_color;

// Fonction main
void main()
{
	// Ambient
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * in_light_color;
  	
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(in_light_position - position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * in_light_color;
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(view_position - position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * in_light_color;  
        
    vec3 result = (ambient + diffuse + specular) * color;
	
	gl_FragColor = vec4(result, 1.0);
}

// Version du GLSL
#version 100

// Precision pour les variables float
precision mediump float;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Light light;

// Entre
varying vec3 position;
varying vec3 color;
varying vec3 normal;
varying vec3 view_position;
varying vec2 texCoord0;

// Fonction main
void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, texCoord0));
  	
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, texCoord0));
    
    // Specular
    vec3 viewDir = normalize(view_position - position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture2D(material.specular, texCoord0));
    
    float distance = length(light.position - position);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        
    vec3 result = (ambient + diffuse + specular) * attenuation;
	
	gl_FragColor = vec4(result, 1.0);
}

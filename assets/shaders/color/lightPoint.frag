// Version du GLSL
#version 100

// Precision pour les variables float
precision mediump float;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
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

// Fonction main
void main()
{
	// Ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // Specular
    vec3 viewDir = normalize(view_position - position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;
    
    float distance = length(light.position - position);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        
    vec3 result = (ambient + diffuse + specular) * attenuation;// * color;
	
	gl_FragColor = vec4(result, 1.0);
}

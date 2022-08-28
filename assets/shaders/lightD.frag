// Version du GLSL
#version 100

// Precision pour les variables float
precision mediump float;
//precision highp float;

struct Material
{
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 view_position;
uniform Material material;
uniform Light light;
uniform sampler2D texture0;

// Entre
varying vec3 position;
varying vec3 normal;
varying vec2 vTexCoord0;

// Fonction main
void main()
{
	vec3 color = vec3(texture2D(texture0, vec2(vTexCoord0.x, -vTexCoord0.y)));
	
	// Ambient
    vec3 ambient = light.ambient * color;
  	
    // Diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * color;
    
    // Specular
    vec3 viewDir = normalize(view_position - position);
    //new
    //vec3 halfwayDir = normalize(lightDir + viewDir);
    // ____________
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // new
    //float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    // ________________
    vec3 specular = light.specular * spec * material.specular;
        
    vec3 result = (ambient + diffuse + specular);// * color;
	
	float gamma = 2.2;
	//result = pow(result, vec3(1.0/gamma));
	gl_FragColor = vec4(result, 1.0);
	//gl_FragColor = vec4(1.0f, 0.31f, 0.31f, 1.0f);
}

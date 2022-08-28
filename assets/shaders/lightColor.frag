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
	float ambientStrength = 0.2;
	vec3 ambient = vec3(0.0);
	vec3 light_direction;
	float diff = 0.0;
	vec3 diffuse = vec3(0.0);
	float specularStrength = 0.5;
	vec3 view_direction = normalize(view_position - position);
	vec3 reflect_direction = vec3(0.0);
	float spec = 0.0;
	vec3 specular = vec3(0.0);
	vec3 result = vec3(0.0);

		//AMBIENT	
		ambient = vec3(ambientStrength * in_light_color); // Not good



		//DIFFUSE	
		light_direction = normalize(in_light_position - position);
		diff = max(dot(normal, light_direction), 0.0);
		diffuse = vec3(diff * in_light_color);
		
		//SPECULAR
		reflect_direction = reflect(-light_direction, normal);
		spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32.0);
		specular = vec3(specularStrength * spec * in_light_color);

		result += ambient + diffuse + specular;

	// Couleur finale du pixel
	result = result * color;
	gl_FragColor = vec4(result, 1.0);
}

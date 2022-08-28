// Version du GLSL
#version 100

// Precision pour les variables float
precision mediump float;
//precision highp float;

varying vec2 coordTexture;

uniform sampler2D texture0;

float near = 0.1;
float far = 100.0;
float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; // back to NDC
	return (2.0 * near * far) / (far + near - z * (far - near));
}

// Fonction main
void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
	
	float blur[9];
	blur[0] = 1.0 / 16.0;
	blur[1] = 2.0 / 16.0;
	blur[2] = 1.0 / 16.0;
	blur[3] = 2.0 / 16.0;
	blur[4] = 4.0 / 16.0;
	blur[5] = 2.0 / 16.0;
	blur[6] = 1.0 / 16.0;
	blur[7] = 2.0 / 16.0;
	blur[8] = 1.0 / 16.0;
	
	float offset = 1.0 / 300.0;
	vec2 offsets[9];
	    offsets[0] = vec2(-offset, offset); // top-left 
	    offsets[1] = vec2( 0.0, offset); // top-center 
	    offsets[2] = vec2( offset, offset); // top-right 
	    offsets[3] = vec2(-offset, 0.0); // center-left 
	    offsets[4] = vec2( 0.0, 0.0); // center-center 
	    offsets[5] = vec2( offset, 0.0);// center-right 
	    offsets[6] = vec2(-offset, -offset); // bottom-left 
	    offsets[7] = vec2( 0.0, -offset); // bottom-center 
	    offsets[8] = vec2( offset, -offset); // bottom-right 
	    
	float kernel[9];
	for(int i=0; i<9; i++)
	{
		if( i != 4 )
		{
			kernel[i] = -1.0;
		}
		else
		{
			kernel[i] = 9.0;
		}
	}
	
	vec2 co = vec2(coordTexture.s, -coordTexture.t);
	vec3 sampleTex[9]; 
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture2D(texture0, co + offsets[i]));
	}
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
	{
		col += sampleTex[i] * kernel[i];
		//col += sampleTex[i] * blur[i];
	}
	gl_FragColor = vec4(col, 1.0);
	
	
	
	
	//gl_FragColor = vec4(vec3(depth), 1.0) * texture2D(texture0, vec2(coordTexture.x, -coordTexture.y));
}

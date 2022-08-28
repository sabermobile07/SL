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
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // division par far pour la démonstration
    gl_FragColor = vec4(vec3(depth), 1.0);
    
    //gl_FragColor = texture2D(texture0, vec2(coordTexture.x, -coordTexture.y));
}

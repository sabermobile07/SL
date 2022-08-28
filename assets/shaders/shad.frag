// Version du GLSL
#version 100

precision mediump float;

uniform sampler2D texture0;

varying vec2 vTexCoord0;
varying vec4 vPos;
varying vec4 vPosLight;

// Fonction main
void main()
{
    vec4 color = texture2D(texture0, vec2(vTexCoord0.x, 1.0-vTexCoord0.y));
    
    if(vPos.z == color.z)
    {
    	color = vec4(1.0);
    }
    
    gl_FragColor = color;
}

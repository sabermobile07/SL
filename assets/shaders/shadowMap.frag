// Version du GLSL
#version 100

precision mediump float;

uniform sampler2D texture0;

varying vec2 vTexCoord0;

// Fonction main
void main()
{
    gl_FragColor = texture2D(texture0, vec2(vTexCoord0.x, 1.0-vTexCoord0.y));
}

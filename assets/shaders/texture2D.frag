// Version du GLSL
 
#version 100

// Précision pour les variables float
precision mediump float;

varying vec2 vTexCoord0;

// Uniform
uniform sampler2D texture0;

// Fonction main
void main()
{
    // Couleur finale du pixel
    gl_FragColor = texture2D(texture0, vTexCoord0);
}
// Version du GLSL
 
#version 100

// Précision pour les variables float
precision mediump float;

varying vec2 vTexCoord0;

// Uniform
uniform sampler2D texture;
uniform vec4 color;

// Fonction main
void main()
{
    // Couleur finale du pixel
    gl_FragColor  = vec4(1.0, 1.0, 1.0, texture2D(texture, vTexCoord0).a) * color;
    
    //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    
    //gl_FragColor = color;
}
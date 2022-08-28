// Version du GLSL
 
#version 100

// Précision pour les variables float
precision mediump float;

varying vec3 vColor;

// Fonction main
void main()
{
    // Couleur finale du pixel
    gl_FragColor = vec4(vColor, 1.0);
}
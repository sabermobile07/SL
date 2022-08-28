// Version du GLSL
 
#version 100

// Précision pour les variables float
precision mediump float;

varying vec3 vNorm;

// Fonction main
void main()
{
    // Couleur finale du pixel
    vec3 norm = normalize(vNorm);
    gl_FragColor = vec4(norm, 1.0) * vec4(1.0, 0.3, 0.3, 1.0);
}
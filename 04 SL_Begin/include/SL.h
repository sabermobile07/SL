#ifndef __SL_H
#define __SL_H


// Include Mac
#ifdef __APPLE__
    #define GL3_PROTOTYPES 1
    #include <OpenGL/gl3.h>
    
// Include OpenGL ES iOS
#elif __IPHONE_NA
    #include <OpenGLES/ES3/gl.h>
    
// Include OpenGL ES Android
#elif __ANDROID__
    #include <GLES3/gl3.h>
    
// Include Windows
#elif WIN32
    #define GLEW_STATIC
    #define GLEW_BUILD
    #include <GL/glew.h>
    #include <glad/glad.h>
    #include <KHR/khrplatform.h>

// Other
#else
#include <GLES3/gl3.h>

#endif

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Must be before all
#include <slTypes.h>
#include <slString.h>
#include <slWindow.h>
#include <slInput.h>
#include <slShader.h>

void SL_init();
void SL_quit();
char* SL_readFile(const char* path);
void SL_errorBox(const char* error);
void SL_printError(const char* error);
void SL_printErrors(const char* error1, const char* error2, const char* error3);

#endif

#ifndef __SL_SHADER_H
#define __SL_SHADER_H

#include <SL.h>

// Classe slShader

typedef struct slShader slShader;

slShader* slShader_init(char* shaderName);
void slShader_free(slShader** me);
void slShader_use(slShader* me);
int slShader_charger(slShader * me);
int slShader_compilerShader(slShader * me, GLuint * shader, GLenum type, char* fichierSource);
GLuint slShader_getID(slShader * me);
void slShader_stop();

#endif

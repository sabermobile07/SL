#ifndef __SL_SHADER_H
#define __SL_SHADER_H

#include <SL.h>

typedef struct slShader slShader;

slShader* slShader_init(char* name);

void slShader_free(slShader** me);

void slShader_compile(slShader* me, const char* vCode, const char* fCode);

void slShader_buildTextures(slShader* me);

void slShader_use(slShader* me);

unsigned int slShader_get(slShader* me);

void slShader_setBool(slShader* me, const char* name, bool value);

void slShader_setInt(slShader* me, const char* name, int value);

void slShader_setFloat(slShader* me, const char* name, float value);

#endif

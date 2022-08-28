#ifndef __SL_OBJ_H
#define __SL_OBJ_H

#include <SL.h>

typedef struct slMaterial slMaterial;
struct slMaterial
{
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

typedef struct slObj slObj;

slObj* slObj_init(char* path, vec3 pos, vec3 scale);
void slObj_free(slObj** me);
size_t slObj_size();
void slObj_draw(slObj* me, slShader* shader, mat4 projection, mat4 view, slCamera* cam, slLightD* lightD);
void slObj_update(slObj* me, slShader* shader);
void slObj_setPos(slObj* me, vec3 pos);
void slObj_setRot(slObj* me, vec3 deg);
void slObj_setScale(slObj* me, vec3 scale);
void slObj_getPos(slObj* me, vec3 dest);
void slObj_getScale(slObj* me, vec3 dest);
void slObj_move(slObj* me, vec3 v);
void slObj_rotate(slObj* me, vec3 deg);
void slObj_scale(slObj* me, float x, float y, float z);
void slObj_setTexID(slObj* me, GLuint id);
bool slObj_testCollision(slObj* me, slObj* other);

#endif
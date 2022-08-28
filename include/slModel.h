#ifndef __SL_MODEL_H
#define __SL_MODEL_H

#include <SL.h>

typedef struct slModel slModel;
struct slModel
{
	slMesh* mesh;
	slTexture* texture;
};

slModel* slModel_init(char* dir);
void slModel_free(slModel* me);
void slModel_draw(slModel* me);
void slModel_setTexID(slModel* me, GLuint id);

#endif
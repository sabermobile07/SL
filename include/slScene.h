#ifndef __SL_SCENE_H
#define __SL_SCENE_H

#include <SL.h>

typedef struct slScene slScene;

slScene* slScene_init(slWindow* win, float x, float y, float w, float h);
void slScene_free(slScene** me);
void slScene_update(slScene* me, slWindow* win);
void slScene_draw(slScene* me, slObj* obj, slShader* shader, bool _3d);
void slScene_drawV(slScene* me, slVector* objs, slShader* shader, bool _3d);
void slScene_calcViewport(slScene* me, slWindow* win);

#endif

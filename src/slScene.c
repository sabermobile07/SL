#include <SL.h>

struct slScene
{
    float x;
    float y;
    float w;
    float h;
    vec2 r; // ratio
    slCamera* cam;
    slLightD* lightD;
    mat4 ortho;
    mat4 perspective;
    mat4 view;
};

slScene* slScene_init(slWindow* win, float x, float y, float w, float h)
{
    slScene* me = malloc(sizeof(slScene));
    
    me->cam = slCamera_init((vec3){0.f, 5.f, 10.f}, (vec3){0.f, 0.f, -100.f}, (vec3){0.f, 1.f, 0.f}, 0.5, 0.5);
    me->lightD = slLightD_init();
    
    me->x = x;
    me->y = y;
    me->w = w;
    me->h = h;
    
    return me;
}

void slScene_free(slScene** me)
{
    slCamera_free(&(*me)->cam);
    slLightD_free(&(*me)->lightD);
    free(*me);
    *me = NULL;
}

void slScene_update(slScene* me, slWindow* win)
{
    slScene_calcViewport(me, win);
    glm_ortho(-me->r[0], me->r[0], -me->r[1], me->r[1], -1.f, 1.f, me->ortho);
    glm_perspective(45.f, me->r[0], 0.1f, 100.f, me->perspective);
    slCamera_lookat(me->cam, &me->view);
}

void slScene_draw(slScene* me, slObj* obj, slShader* shader, bool _3d)
{
    if( _3d == true)
    {
        slObj_draw(obj, shader, me->perspective, me->view, me->cam, me->lightD);
    }
    else
    {
        slObj_draw(obj, shader, me->ortho, me->view, me->cam, me->lightD);
    }
}

void slScene_drawV(slScene* me, slVector* objs, slShader* shader, bool _3d)
{
    slObj* o;
    for(int i=0; i<slVector_getTotal(objs); i++)
    {
        o = slVector_get(objs, i);
        slScene_draw(me, o, shader, _3d);
    }
}

void slScene_calcViewport(slScene* me, slWindow* win)
{
    int x = (1 + me->x) * (win->w / 2.f);
    int y = (1 + me->y) * (win->h / 2.f);
    int w = me->w * win->w / 2.f;
    int h = me->h * win->h / 2.f;
    if(w < h)
    {
        me->r[0] = 1.f;
        me->r[1] = (float)h / w;
    }
    else
    {
        me->r[0] = (float)w / h;
        me->r[1] = 1.f;
    }
    glViewport(x, y, w, h);
}

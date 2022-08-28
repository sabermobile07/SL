#include <SL.h>

struct Enemy
{
    slShader* shader;
    slObj* obj;
};

Enemy* Enemy_init()
{
    Enemy* me = malloc(sizeof(Enemy*));
    me->shader = slShader_init("texture2D");
    me->obj = slObj_init("cube", (vec3){-0.5, 1, 0}, (vec3){0.2, 0.2, 0.2});
    
    return me;
}

void Enemy_free(Enemy** me)
{
    slObj_free(&(*me)->obj);
}

void Enemy_draw(Enemy* me, slScene* scene)
{
    slScene_draw(scene, me->obj, me->shader, false);
}

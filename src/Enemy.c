#include <SL.h>

struct Enemy
{
    slShader* shader;
    slObj* obj;
    float speed;
    vec3 dir;
    float lifeOriginal;
    float life;
    float level;
};

struct EnemyV
{
    slVector* v;
    float dt;
};

Enemy* Enemy_init(vec3 pos, float life, float level)
{
    Enemy* me = malloc(sizeof(Enemy));
    me->shader = slShader_init("texture2D");
    me->obj = slObj_init("cube", pos, (vec3){0.2*level, 0.2*level, 0.2*level});
    me->speed = 1.f;
    glm_vec3_copy((vec3){0.2f, -0.8f, 0.f}, me->dir);
    me->lifeOriginal = life;
    me->life = life;
    me->level = level;
    
    return me;
}

void Enemy_free(Enemy** me)
{
    slShader_free(&(*me)->shader);
    slObj_free(&(*me)->obj);
    free(*me);
}

void Enemy_draw(Enemy* me, slScene* scene, slFont* font, slWindow* win)
{
    char s[4];
    sprintf(s, "%d", (int)me->life);
    vec3 pos;
    slObj_getPos(me->obj, pos);
    
    slFont_draw(font, win, s, pos[0]/win->ratio[0], pos[1]/win->ratio[1]);
    
    slScene_draw(scene, me->obj, me->shader, false);
}

void Enemy_update(Enemy* me, float dt)
{
    if(me->life <= 0.f)
    {
        return;
    }
    vec3 pos, scale;
    slObj_getPos(me->obj, pos);
    slObj_getScale(me->obj, scale);
    
    if(pos[0] - (scale[0] / 2.f) <= -1.f)
    {
        pos[0] = -1.f + (scale[0] / 2.f);
        slObj_setPos(me->obj, pos);
        me->dir[0] *= -1.f;
    }
    else if(pos[0] + (scale[0] / 2.f) >= 1.f)
    {
        pos[0] = 1.f - (scale[0] / 2.f);
        slObj_setPos(me->obj, pos);
        me->dir[0] *= -1.f;
    }
    if(pos[1] - (scale[1] / 2.f) <= -1.f)
    {
        pos[1] = -1.f + (scale[1] / 2.f);
        slObj_setPos(me->obj, pos);
        me->dir[1] *= -1.f;
    }
    else if(pos[1] + (scale[1] / 2.f) >= 1.f)
    {
        pos[1] = 1.f - (scale[1] / 2.f);
        slObj_setPos(me->obj, pos);
        me->dir[1] *= -1.f;
    }
    
    vec3 vel;
    me->dir[1] -= dt;
    float s = me->speed * dt;
    glm_vec3_scale(me->dir, s, vel);
    slObj_move(me->obj, vel);
}

void Enemy_hited(Enemy* me, float power)
{
    me->life -= power;
}

float Enemy_getLife(Enemy* me)
{
    return me->life;
}

slObj* Enemy_getObj(Enemy* me)
{
    return me->obj;
}

// EnemyV
EnemyV* EnemyV_init()
{
    EnemyV* me = malloc(sizeof(EnemyV));
    me->v = slVector_init();
    me->dt = 0.f;
    return me;
}

void EnemyV_free(EnemyV** me)
{
    for(size_t i=0; i<slVector_getTotal((*me)->v); i++)
    {
        Enemy* e = slVector_get((*me)->v, i);
        Enemy_free(&e);
    }
    free(*me);
}

void EnemyV_draw(EnemyV* me, slScene* scene, slFont* font, slWindow* win)
{
    for(size_t i=0; i<slVector_getTotal(me->v); i++)
    {
        Enemy* e = slVector_get(me->v, i);
        Enemy_draw(e, scene, font, win);
    }
}

void EnemyV_update(EnemyV* me, float dt)
{
    for(size_t i=0; i<slVector_getTotal(me->v); i++)
    {
        Enemy* e = slVector_get(me->v, i);
        Enemy_update(e, dt);
        if(e->life <= 0)
        {
            if(e->level > 1)
            {
                vec3 pos, scale;
                slObj_getPos(e->obj, pos);
                slObj_getScale(e->obj, scale);
                pos[0] += scale[0] / 4.f;
                slVector_push(me->v, Enemy_init(pos, e->lifeOriginal/2.f, e->level-1.f));
                pos[0] -= scale[0] / 2.f;
                Enemy* tmp = Enemy_init(pos, e->lifeOriginal/2.f, e->level-1.f);
                tmp->dir[0] *= -1.f;
                slVector_push(me->v, tmp);
            }
            Enemy_free(&e);
            slVector_delete(me->v, i);
        }
    }
    
    me->dt += dt;
    if((me->dt >= 4 && slVector_getTotal(me->v) < 4) || slVector_getTotal(me->v) == 0)
    {
        slVector_push(me->v, Enemy_init((vec3){-0.f, 1.f, 0.f}, 2.f, 2.f));
        me->dt = 0.f;
    }
}

size_t EnemyV_getTotal(EnemyV* me)
{
    return slVector_getTotal(me->v);
}

Enemy* EnemyV_get(EnemyV* me, size_t n)
{
    return slVector_get(me->v, n);
}

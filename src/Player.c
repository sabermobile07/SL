#include <SL.h>

struct Player
{
    slShader* shader;
	slObj* obj;
	slVector* weapons;
	float level;
	float dt;
	bool life;
};

Player* Player_init()
{
	Player* me = malloc(sizeof(Player));
	me->shader = slShader_init("texture2D");
	me->obj = slObj_init("cube", (vec3){0.f, -1.f, 0.f}, (vec3){0.2f, 0.2f, 0.2f});
	me->weapons = slVector_init();
	me->level = 1.f;
	me->dt = 0.f;
	me->life = true;

	return me;
}

void Player_free(Player** me)
{
    slVector_free(&(*me)->weapons);
	slObj_free(&(*me)->obj);
	slShader_free(&(*me)->shader);
	free(*me);
	*me = NULL;
}

void Player_update(Player* me, float dt)
{
    me->dt += dt;
    int t = slVector_getTotal(me->weapons);
    Weapon* tmp;
    
    for(int i=0; i<t; i++)
    {
        tmp = slVector_get(me->weapons, i);
        Weapon_update(tmp, dt);
    }
    
    if(me->dt > 1.f / me->level)
    {
        vec3 pos, scale;
        slObj_getPos(me->obj, pos);
        slVector_push(me->weapons, Weapon_init(pos, 1.f)); // chage 1 to power in magasin
        me->dt = 0.f;
    }
}

void Player_setX(Player* me, float x)
{
    x = -1.f + (x * 2.f);
    vec3 pos;
    slObj_getPos(me->obj, pos);
    pos[0] = x;
    slObj_setPos(me->obj, pos);
}

void Player_draw(Player* me, slScene* scene)
{
    slScene_draw(scene, me->obj, me->shader, false);
    size_t t = slVector_getTotal(me->weapons);
    for(size_t i=0; i<t; i++)
    {
        Weapon* w = slVector_get(me->weapons, i);
        Weapon_draw(w, scene, me->shader, false);
    }
}

bool Player_doCollision(Player* me, Enemy* enemy)
{
    bool ret = false;
    
    slObj* o = Enemy_getObj(enemy);
    if(slObj_testCollision(me->obj, o))
    {
        ret = true;
    }
    else
    {
        size_t t = slVector_getTotal(me->weapons);
        for(size_t i=0; i<t; i++)
        {
            Weapon* w = slVector_get(me->weapons, i);
            if(Weapon_doCollision(w, enemy))
            {
                slVector_delete(me->weapons, i);
            }
        }
    }
    
    return ret;
}

bool Player_doCollisionV(Player* me, EnemyV* enemyV)
{
    bool ret = false;
    for(size_t i=0; i<EnemyV_getTotal(enemyV); i++)
    {
        Enemy* e = EnemyV_get(enemyV, i);
        if(Player_doCollision(me, e))
        {
            ret = true;
            return ret;
        }
    }
    return ret;
}

bool Player_getLife(Player* me)
{
    return me->life;
}

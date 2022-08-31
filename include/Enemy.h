#ifndef __ENEMY_H
#define __ENEMY_H

#include <SL.h>

typedef struct Enemy Enemy;
typedef struct EnemyV EnemyV;

Enemy* Enemy_init(vec3 pos, float life, float level);
void Enemy_free(Enemy** me);
void Enemy_draw(Enemy* me, slScene* scene, slFont* font, slWindow* win);
void Enemy_update(Enemy* me, float dt);
void Enemy_hited(Enemy* me, float power);
float Enemy_getLife(Enemy* me);
slObj* Enemy_getObj(Enemy* me);

// EnemyV
EnemyV* EnemyV_init();
void EnemyV_free(EnemyV** me);
void EnemyV_draw(EnemyV* me, slScene* scene, slFont* font, slWindow* win);
void EnemyV_update(EnemyV* me, float dt);
size_t EnemyV_getTotal(EnemyV* me);
Enemy* EnemyV_get(EnemyV* me, size_t n);

#endif

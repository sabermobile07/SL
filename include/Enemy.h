#ifndef __ENEMY_H
#define __ENEMY_H

#include <SL.h>

typedef struct Enemy Enemy;

Enemy* Enemy_init();
void Enemy_free(Enemy** me);
void Enemy_draw(Enemy* me, slScene* scene);

#endif

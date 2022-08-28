#ifndef __PLAYER_H
#define __PLAYER_H

#include <SL.h>

typedef struct Player Player;

Player* Player_init();
void Player_free(Player** me);
void Player_update(Player* me, float dt);
void Player_setX(Player* me, float x);
void Player_draw(Player* me, slScene* scene);

#endif
#ifndef __WEAPON_H
#define __WEAPON_H

#include <SL.h>

typedef struct Weapon Weapon;

Weapon* Weapon_init(vec3 pos);
void Weapon_free(Weapon** me);
void Weapon_push(Weapon* me, slScene* scene);
void Weapon_update(Weapon* me, float dt);
void Weapon_draw(Weapon* me, slScene* scene, slShader* shader, bool _3d);

#endif
#include <SL.h>

struct Weapon
{
	slObj* obj;
	float speed;
	vec3 dir;
	slAudio* audio;
};

Weapon* Weapon_init(vec3 pos)
{
	Weapon* me = malloc(sizeof(Weapon));
	me->obj = slObj_init("cube", pos, (vec3){0.02f, 0.05f, 0.001f});
	me->speed = 2.f;
	glm_vec3_copy((vec3){0.f, 1.f, 0.f}, me->dir);
	me->audio = slAudio_init("assets/audio/ball.wav");
	slAudio_play(me->audio);

	return me;
}

void Weapon_free(Weapon** me)
{
    slAudio_free((*me)->audio);
	slObj_free(&(*me)->obj);
	free(*me);
	*me = NULL;
}

void Weapon_update(Weapon* me, float dt)
{
    vec3 vel;
    glm_vec3_scale(me->dir, me->speed * dt, vel);
    /*glm_vec3_copy(me->dir, vel);
    vel[0] *= me->speed * dt;
    vel[1] *= me->speed * dt;
    vel[2] *= me->speed * dt;*/
    slObj_move(me->obj, vel);
}

void Weapon_draw(Weapon* me, slScene* scene, slShader* shader, bool _3d)
{
    slScene_draw(scene, me->obj, shader, _3d);
}

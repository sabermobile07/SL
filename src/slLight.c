#include <SL.h>

slLightD* slLightD_init()
{
	slLightD* me = malloc(sizeof(slLightD));
	glm_vec3_copy((vec3){-0.2f, -1.f, -0.8f}, me->direction);
	glm_vec3_copy((vec3){0.2f, 0.2f, 0.2f}, me->ambient);
	glm_vec3_copy((vec3){0.8f, 0.8f, 0.8f}, me->diffuse);
	glm_vec3_copy((vec3){1.f, 1.f, 1.f}, me->specular);
	
	return me;
}

void slLightD_free(slLightD** me)
{
	free(*me);
	*me = NULL;
}

#ifndef __SLLIGHT_H
#define __SLLIGHT_H

typedef struct
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} slLightD;

slLightD* slLightD_init();
void slLightD_free(slLightD** me);

#endif

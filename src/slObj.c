#include <SL.h>

struct slObj
{
	slModel* model;
	slMaterial material;
	vec3 pos;
	vec3 rot;
	vec3 scale;
};

slObj* slObj_init(char* path, vec3 pos, vec3 scale)
{
	slObj* me = malloc(sizeof(slObj));
	
    me->model = slModel_init(path);
    glm_vec3_copy((vec3){1.f, 0.5f, 0.31f}, me->material.diffuse);
    glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, me->material.specular);
    me->material.shininess = 32.f;
	glm_vec3_copy(pos, me->pos);
	glm_vec3_zero(me->rot);
	glm_vec3_copy(scale, me->scale);

	return me;
}

void slObj_free(slObj** me)
{
	slModel_free((*me)->model);
	free(*me);
	*me = NULL;
}

size_t slObj_size()
{
	return sizeof(slObj);
}

void slObj_draw(slObj* me, slShader* shader, mat4 projection, mat4 view, slCamera* cam, slLightD* lightD)
{
	mat4 m;
	glm_mat4_identity(m);
	glm_translate(m, me->pos);
	glm_rotate(m, glm_rad(me->rot[0]), (vec3){1.f, 0.f, 0.f});
	glm_rotate(m, glm_rad(me->rot[1]), (vec3){0.f, 1.f, 0.f});
	glm_rotate(m, glm_rad(me->rot[2]), (vec3){0.f, 0.f, 1.f});
	vec3 tmp;
	glm_vec3_scale(me->scale, 0.5f, tmp);
	glm_scale(m, tmp);
	
	mat4 trInv;
	glm_mat4_copy(m, trInv);
	glm_mat4_transpose(trInv);

	slShader_use(shader);
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "projection"), 1, GL_FALSE, *(projection));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "view"), 1, GL_FALSE, *(view));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "model"), 1, GL_FALSE, *(m));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "transpose_inverse_model"), 1, GL_FALSE, *(trInv));
	
	vec3 camPos;
	slCamera_getPos(cam, camPos);
	glUniform3f(glGetUniformLocation(slShader_getID(shader), "view_position"), camPos[0], camPos[1], camPos[2]);
	glUniform3f(glGetUniformLocation(slShader_getID(shader), "light.direction"), lightD->direction[0], lightD->direction[1], lightD->direction[2]);
		glUniform3f(glGetUniformLocation(slShader_getID(shader), "light.ambient"), lightD->ambient[0], lightD->ambient[1], lightD->ambient[2]);
		glUniform3f(glGetUniformLocation(slShader_getID(shader), "light.diffuse"), lightD->diffuse[0], lightD->diffuse[1], lightD->diffuse[2]);
		glUniform3f(glGetUniformLocation(slShader_getID(shader), "light.specular"), lightD->specular[0], lightD->specular[1], lightD->specular[2]);
	glUniform3f(glGetUniformLocation(slShader_getID(shader), "material.diffuse"), me->material.diffuse[0], me->material.diffuse[1], me->material.diffuse[2]);
	glUniform3f(glGetUniformLocation(slShader_getID(shader), "material.specular"), me->material.specular[0], me->material.specular[1], me->material.specular[2]);
	glUniform1f(glGetUniformLocation(slShader_getID(shader), "material.shininess"), me->material.shininess);
	
	slModel_draw(me->model);
	slShader_stop();
}

void slObj_setPos(slObj* me, vec3 pos)
{
	glm_vec3_copy(pos, me->pos);
}

void slObj_setRot(slObj* me, vec3 deg)
{
	glm_vec3_copy(deg, me->rot);
}

void slObj_setScale(slObj* me, vec3 scale)
{
	glm_vec3_copy(scale, me->scale);
}

void slObj_getPos(slObj* me, vec3 dest)
{
	glm_vec3_copy(me->pos, dest);
}

void slObj_getScale(slObj* me, vec3 dest)
{
	glm_vec3_copy(me->scale, dest);
}

void slObj_move(slObj* me, vec3 v)
{
    glm_vec3_add(me->pos, v, me->pos);
}

void slObj_rotate(slObj* me, vec3 deg)
{
	glm_vec3_add(deg, me->rot, me->rot);
	for(int i=0; i<3; i++)
	{
		if(me->rot[i] >= 360.f)
		{
			me->rot[i] -= 360.f;
		}
	}
}

void slObj_scale(slObj* me, float x, float y, float z)
{
    me->scale[0] *= x;
    me->scale[1] *= y;
    me->scale[2] *= z;
}

void slObj_setTexID(slObj* me, GLuint id)
{
	slModel_setTexID(me->model, id);
}

bool slObj_testCollision(slObj* me, slObj* other)
{
	bool collisionX =  me->pos[0] + me->scale[0] / 2.f >= other->pos[0] - other->scale[0] / 2.f && other->pos[0] + other->scale[0] / 2.f >= me->pos[0] - me->scale[0] / 2.f;
	
	bool collisionY =  me->pos[1] + me->scale[1] / 2.f >= other->pos[1] - other->scale[1] / 2.f && other->pos[1] + other->scale[1] / 2.f >= me->pos[1] - me->scale[1] / 2.f;
	
	return collisionX && collisionY;
}

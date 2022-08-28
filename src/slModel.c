#include <SL.h>

slModel* slModel_init(char* dir)
{
	slModel* me = malloc(sizeof(slModel));
	char s[256] = "";
	sprintf(s, "assets/objs/%s/model.gltf", dir);
	me->mesh = slMesh_init(s);
	
	//me->texture = slTexture_initFile("assets/objs/rect/Caisse2_jpg.jpg");
	sprintf(s, "assets/objs/%s/%s", dir, slMesh_getImage(me->mesh));
	me->texture = slTexture_initFile(s);
	
	return me;
}

void slModel_free(slModel* me)
{
	slMesh_free(me->mesh);
	slTexture_free(me->texture);
	free(me);
	me = NULL;
}

void slModel_draw(slModel* me)
{
	// Verrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, slTexture_getID(me->texture));
    
	slMesh_draw(me->mesh);
	
	// Deverrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void slModel_setTexID(slModel* me, GLuint id)
{
	slTexture_setID(me->texture, id);
}

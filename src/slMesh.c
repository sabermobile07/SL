#include <SL.h>

slMesh* slMesh_init(char* path)
{
    slMesh* ret = malloc(sizeof(slMesh));
    ret->VBO = 0;
	ret->EBO = 0;
    ret->pos = slGltfAttribute_init();
    ret->norm = slGltfAttribute_init();
    ret->uv = slGltfAttribute_init();
	ret->ind = slGltfIndice_init();
	ret->ver = NULL;
	slString_init(&ret->image, "");
	
	cgltf_load(ret, path);
	slMesh_setup(ret);
    return ret;
}

void slMesh_free(slMesh* me)
{
	slGltfAttribute_free(me->pos);
	slGltfAttribute_free(me->norm);
	slGltfAttribute_free(me->uv);
	slGltfIndice_free(me->ind);
	free(me->ver);
	me->ver = NULL;
}

void slMesh_setup(slMesh* me)
{
	glGenBuffers(1, &me->VBO);
	glGenBuffers(1, &me->EBO);

    glBindBuffer(GL_ARRAY_BUFFER, me->VBO);
    	glBufferData(GL_ARRAY_BUFFER, (me->pos->stride * me->pos->count) + (me->norm->stride * me->norm->count) + (me->uv->stride * me->uv->count), 0, GL_STATIC_DRAW);
    	glBufferSubData(GL_ARRAY_BUFFER, 0, (me->pos->stride * me->pos->count), me->pos->data);
    	glBufferSubData(GL_ARRAY_BUFFER, (me->pos->stride * me->pos->count), (me->norm->stride * me->norm->count), me->norm->data);
    	glBufferSubData(GL_ARRAY_BUFFER, (me->pos->stride * me->pos->count)+(me->norm->stride * me->norm->count), (me->uv->stride * me->uv->count), me->uv->data);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, me->EBO);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, me->ind->count * sizeof(GLuint), me->ind->data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void slMesh_draw(slMesh* me)
{
	// Draw mesh
    glBindBuffer(GL_ARRAY_BUFFER, me->VBO);
	
	// Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
    
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (me->pos->stride*me->pos->count));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (me->pos->stride*me->pos->count)+(me->norm->stride*me->norm->count));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, me->EBO);
    
    glDrawElements(GL_TRIANGLES, me->ind->count, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

char* slMesh_getImage(slMesh* me)
{
	return slString_get(&me->image);
}

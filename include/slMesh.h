#ifndef __SL_MESH_H
#define __SL_MESH_H

#include <SL.h>

typedef struct slMesh slMesh;
struct slMesh
{
	GLuint VBO;
	GLuint EBO;
    slGltfAttribute* pos;
    slGltfAttribute* norm;
    slGltfAttribute* uv;
    slGltfIndice* ind;
    slString image;
    
    float* ver;
};

slMesh* slMesh_init(char* path);
void slMesh_free(slMesh* me);
void slMesh_setup(slMesh* me);
void slMesh_draw(slMesh* me);
char* slMesh_getImage(slMesh* me);

#endif

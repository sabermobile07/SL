#ifndef __SLGLTFINDICE_H
#define __SLGLTFINDICE_H

#include <SL.h>

typedef struct slGltfIndice slGltfIndice;
struct slGltfIndice
{
	unsigned int count;
    unsigned int* data;
};

slGltfIndice* slGltfIndice_init();
void slGltfIndice_free(slGltfIndice* me);

#endif
#ifndef __SLGLTFATTRIBUTE_H
#define __SLGLTFATTRIBUTE_H

#include <SL.h>

typedef struct slGltfAttribute slGltfAttribute;
struct slGltfAttribute
{
	unsigned int numCmp;
	unsigned int count;
    unsigned int stride;
    unsigned int offset;
    float* data;
};

slGltfAttribute* slGltfAttribute_init();
void slGltfAttribute_free(slGltfAttribute* me);

#endif
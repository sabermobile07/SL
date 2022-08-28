#include <SL.h>

slGltfAttribute* slGltfAttribute_init()
{
	slGltfAttribute* ret = malloc(sizeof(slGltfAttribute));
	ret->numCmp = 0;
	ret->count = 0;
    ret->stride = 0;
    ret->offset = 0;
    ret->data = NULL;
	return ret;
}

void slGltfAttribute_free(slGltfAttribute* me)
{
	free(me->data);
	me->data = NULL;
	free(me);
	me = NULL;
}

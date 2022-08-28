#include <SL.h>

slGltfIndice* slGltfIndice_init()
{
	slGltfIndice* ret = malloc(sizeof(slGltfIndice));
	ret->count = 0;
    ret->data = NULL;
	return ret;
}

void slGltfIndice_free(slGltfIndice* me)
{
	free(me->data);
	me->data = NULL;
	free(me);
	me = NULL;
}

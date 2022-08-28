#include <SL.h>

struct slVector
{
    unsigned int total;
    void** data;
};

slVector* slVector_init()
{
    slVector* me = malloc(sizeof(slVector));
    me->total = 0;
    me->data = malloc(0);
    return me;
}

void slVector_free(slVector** me)
{
    free((*me)->data);
    (*me)->data = NULL;
    free(*me);
    *me = NULL;
}

void* slVector_get(slVector* me, unsigned int n)
{
	if(slVector_testRange(me, n) == false)
	{
		return NULL;
	}
    return me->data[n];
}

unsigned int slVector_getTotal(slVector* me)
{
    return me->total;
}

void slVector_set(slVector* me, unsigned int n, void* data)
{
	if(slVector_testRange(me, n) == false)
	{
		return;
	}
    me->data[n] = data;
}

void slVector_push(slVector* me, void* data)
{
	me->total += 1;
    me->data = realloc(me->data, me->total*sizeof(void*));
    slVector_set(me, me->total - 1, data);
}

void slVector_delete(slVector* me, unsigned int n)
{
    if(slVector_testRange(me, n))
    {
        for(unsigned int i=n+1; i<me->total; i++)
        {
            me->data[i-1] = me->data[i];
        }
        me->total -= 1;
        me->data = realloc(me->data, me->total * sizeof(void*));
    }
}

bool slVector_testRange(slVector* me, unsigned int n)
{
	if(n > me->total - 1)
	{
		printf("slVector out of range\n");
		return false;
	}
	return true;
}

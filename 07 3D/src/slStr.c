#include <slStr.h>

struct slStr
{
	char* data;
	size_t size;
	size_t cap;
};



slStr* slStr_new(const char* str)
{
	assert(str);
    if(!str) str = "";

    slStr* me = malloc(sizeof(slStr));
    if(!me) return NULL;
    
    assert(me);

    me->size = strlen(str);
    me->cap = (me->size == 0) ? 16 : me->size * 2 + 1;

    me->data = malloc(me->cap);
    assert(me->data);
    if(!me->data)
    {
        free(me);
        return NULL;
    }

    memcpy(me->data, str, me->size);
    me->data[me->size] = '\0';

    assert(me && me->data);
    
    return me;
}

void slStr_free(slStr** me)
{
	assert(me && *me);
    
    free((*me)->data);
    (*me)->data = NULL;
    free(*me);
    *me = NULL;
}

const char* slStr_get(const slStr* me)
{
	assert(me);
	if(!me) return NULL;
	return me->data;
}

size_t slStr_getSize(const slStr* me)
{
	assert(me);
	if(!me) return 0;
	return me->size;
}

bool slStr_set(slStr* me, const char* str)
{
	assert(me && str);
    if(!me || !str) return false;

    size_t len = strlen(str);

    if(!slStr_reserve(me, len + 1)) return false;

    memcpy(me->data, str, len);
    me->size = len;
    me->data[len] = '\0';

    return true;
}

bool slStr_shrink(slStr* me)
{
	assert(me);
    if (!me) return false;

    size_t nc = me->size + 1;

    char* tmp = realloc(me->data, nc);
    if (!tmp)
        return false;

    me->data = tmp;
    me->cap  = nc;
    return true;
}

bool slStr_reserve(slStr* me, size_t cap)
{
	assert(me);
    if(!me) return false;

    if(cap <= me->cap) return true;
    
    char* tmp = realloc(me->data, cap);
    if(!tmp) return false;

    me->data = tmp;
    me->cap  = cap;
    me->data[me->size] = '\0';
    
    return true;
}

bool slStr_clean(slStr* me)
{
	assert(me);
    if(!me) return false;

    me->size = 0;
    me->data[0] = '\0';
    return true;
}

bool slStr_add(slStr* me, const char* str)
{
	assert(me && str);
	if(!me || !str) return false;
	
    size_t size = strlen(str);
    size_t os = me->size;
    if (size > SIZE_MAX - os) return false;
    size_t ns = os + size;
    size_t nc = me->cap;

    while (nc < ns + 1)
    {
    	if (nc > SIZE_MAX / 2)
    	{
    		nc = ns + 1;
    		break;
    	}
    	nc *= 2;
    }

    if(!slStr_reserve(me, nc)) return false;
    memcpy(me->data + os, str, size);
    
    me->size = ns;
    me->data[ns] = '\0';
    
    return true;
}

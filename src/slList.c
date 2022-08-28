#include <SL.h>

struct slElement
{
    size_t id;
	void* data;
	slElement* next;
};

struct slList
{
    size_t total;
	slElement* element;
};

slList* slList_init()
{
    slList* me = malloc(sizeof(slList));
    me->total = 0;
    me->element = NULL;
    return me;
}

void slList_free(slList** me)
{
    slElement* e = (*me)->element;
    for(size_t i=0; i<(*me)->total; i++)
    {
        e = (*me)->element;
        (*me)->element = e->next;
        free(e);
        e = NULL;
    }
	free(*me);
	*me = NULL;
}

size_t slList_getTotal(slList* me)
{
    return me->total;
}

void* slList_get(slList* me, size_t id)
{
    slElement* element = me->element;
    for(size_t i=0; i<=id; i++)
    {
        if(i == id)
        {
            return element->data;
        }
        element = element->next;
    }
    
    return NULL;
}

void slList_push(slList* me, void* data)
{
    slElement* tmp = malloc(sizeof(slElement));
    tmp->id = me->total;
    tmp->data = data;
    tmp->next = NULL;
    me->total += 1;
    
    if(me->element == NULL)
    {
        me->element = tmp;
        return;
    }
    
    slElement* element = me->element;
    while(element->next != NULL)
    {
        element = element->next;
    }
    
    element->next = tmp;
    
}

#include <SL.h>

struct slString
{
	int count;
	char* data;
};

slString* slString_init(char* text)
{
	slString* me = calloc(1, sizeof(slString));
	me->count = strlen(text);
	me->data = malloc(sizeof(char)*(me->count +1));
	strcpy(me->data, text);
	
	return me;
}

void slString_free(slString* me)
{
	me->count = 0;
	free(me->data);
	free(me);
}

void slString_set(slString* me, char* text)
{
	me->count = strlen(text);
	me->data = NULL;
	me->data = realloc(me->data,sizeof(char) * (me->count + 1));
	strcpy(me->data, text);
}

char* slString_get(slString* me)
{
	return me->data;
}

void slString_add(slString* me, char* text)
{
	me->count += strlen(text);
	me->data = realloc(me->data,sizeof(char) * (me->count + 1));
	strcat(me->data, text);
}

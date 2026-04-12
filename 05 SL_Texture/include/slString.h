#ifndef __SL_STRING_H
#define __SL_STRING_H

#include <SL.h>

typedef struct slString slString;

slString* slString_init(char* text);

void slString_free(slString* me);

void slString_set(slString* me, char* text);

char* slString_get(slString* me);

void slString_add(slString* me, char* text);

#endif

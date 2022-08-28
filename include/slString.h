#ifndef __SL_STRING_H
#define __SL_STRING_H

//#pragma pack(1)

#include <SL.h>

typedef struct slString slString;
struct slString
{
    char* data;
    int count;
};

void slString_init(slString* me, char* string);
void slString_free(slString* me);
char* slString_get(slString* me);
void slString_set(slString* me, char* str);
void slString_add(slString* me, char* string);
void slString_addChar(slString* me, char c);
void slString_addInt(slString* me, int a);
void slString_addFloat(slString* me, float a);
void slString_print(slString* me);


#endif
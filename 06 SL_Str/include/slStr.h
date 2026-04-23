#ifndef _SLSTR_H
#define _SLSTR_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct slStr slStr;

slStr* slStr_new(const char* str);

void slStr_free(slStr** me);

const char* slStr_get(const slStr* me);

size_t slStr_getSize(const slStr* me);

bool slStr_set(slStr* me, const char* str);

bool slStr_shrink(slStr* me);

bool slStr_reserve(slStr* me, size_t cap);

bool slStr_clean(slStr* me);

bool slStr_add(slStr* me, const char* str);


#endif

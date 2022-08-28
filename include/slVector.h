#ifndef __SL_VECTOR_H
#define __SL_VECTOR_H

#include <SL.h>

typedef struct slVector slVector;

slVector* slVector_init();
void slVector_free(slVector** me);
void* slVector_get(slVector* me, unsigned int n);
unsigned int slVector_getTotal(slVector* me);
void slVector_set(slVector* me, unsigned int n, void* data);
void slVector_push(slVector* me, void* data);
void slVector_delete(slVector* me, unsigned int n);
bool slVector_testRange(slVector* me, unsigned int n);

#endif
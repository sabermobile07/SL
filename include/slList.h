#ifndef __SL_LIST_H
#define __SL_LIST_H

#include <SL.h>

typedef struct slElement slElement;
typedef struct slList slList;

slList* slList_init();
void slList_free(slList** me);
size_t slList_getTotal(slList* me);
void* slList_get(slList* me, size_t id);
void slList_push(slList* me, void* data);

#endif
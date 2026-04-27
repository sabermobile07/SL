#ifndef __SL_WINDOW_H
#define __SL_WINDOW_H

#include <SL.h>

typedef struct slWindow slWindow;

slWindow* slWindow_new();

void slWindow_free(slWindow* me);

bool slWindow_getStatus(slWindow* me);

void slWindow_setStatus(slWindow* me, bool status);

void slWindow_draw(slWindow* me);

#endif

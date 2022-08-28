#ifndef __SL_SHADOW_H
#define __SL_SHADOW_H

    #include "SL.h"
    typedef struct slShadow slShadow;
    
    slShadow* slShadow_init(int w, int h);
    void slShadow_free(slShadow* me);
    void slShadow_clear(slShadow* me);
    void slShadow_draw(slShadow* me, slShader* shader, slWindow* win);
    unsigned int slShadow_getID(slShadow* me);
    unsigned int slShadow_getColorID(slShadow* me);

#endif

#ifndef __SL_TEXTURE_H
#define __SL_TEXTURE_H

    // Include
    #include <SL.h>

    // Classe
    typedef struct slTexture slTexture;

    slTexture* slTexture_init(char* name);
    void slTexture_free(slTexture* me);
    void slTexture_use(slTexture* me, int nbr);
    unsigned int slTexture_getID(slTexture* me);

#endif

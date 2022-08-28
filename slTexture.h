#ifndef __SL_TEXTURE_H

#define __SL_TEXTURE_H

#include <SL.h>

// Classe slTexture
typedef struct slTexture slTexture;
struct slTexture
{
    GLuint id;
    slString path;
    //char* type;
    //struct aiString path; // We store the path of the texture to compare with other textures
};

    void slTexture_init(slTexture * me, char* path);
    void slTexture_free(slTexture * me);
    int slTexture_charger(slTexture * me);
    GLuint const slTexture_getID(slTexture * me);
    SDL_Surface* const slTexture_inverserPixels(SDL_Surface *imageSource);
#endif

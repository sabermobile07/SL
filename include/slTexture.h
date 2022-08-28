#ifndef __SL_TEXTURE_H
#define __SL_TEXTURE_H

    #include <SL.h>
    
    typedef struct
    {
        GLuint id;
        char* fichierImage;
        int w;
        int h;
        GLenum format;
        GLenum formatInterne;
        bool textureVide;
    } slTexture;
        
    slTexture* slTexture_init();
    slTexture* slTexture_initFile(char* fichierImage);
    slTexture* slTexture_initTexture(int w, int h, GLenum format, GLenum formatInterne, bool textureVide);
    void slTexture_free(slTexture* me);
    void slTexture_copy(slTexture* dst, slTexture* const src);
    //Texture& operator=(Texture const &textureACopier);
    void slTexture_chargerTextureVide(slTexture* me);
    bool slTexture_charger(slTexture* me);
    const GLuint slTexture_getID(slTexture* me);
    void slTexture_setFichierImage(slTexture* me, const char* fichierImage);
    
    void slTexture_setID(slTexture* me, GLuint id);

#endif

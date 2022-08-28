#ifndef __SL_FBO_H
#define __SL_FBO_H

    #include "SL.h"
    typedef struct slFbo slFbo;
    
    slFbo* slFbo_init(char* dir, char* shaderName, int w, int h, bool needStencilBuffer);
    void slFbo_free(slFbo* me);
    void slFbo_clear(slFbo* me);
    void slFbo_draw(slFbo* me, slWindow* win);
    void slFbo_copy(slFbo* dst, slFbo*src);
    void slFbo_createRenderBuffer(slFbo* me, GLenum format);
    bool slFbo_setup(slFbo* me);
    GLuint slFbo_getID(slFbo* me);
    GLuint slFbo_getColorBufferID(slFbo* me, unsigned int index);
    GLuint slFbo_getDepthBufferID(slFbo* me);
    int slFbo_getWidth(slFbo* me);
    int slFbo_getHeight(slFbo* me);

#endif

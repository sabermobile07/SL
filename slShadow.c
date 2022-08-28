#include "SL.h"

struct slShadow
{
	unsigned int id;
    unsigned int color;
    unsigned int depth;
    unsigned int stencil;
    unsigned int rbo;
    int w;
    int h;
    slMesh* mesh;
};

slShadow* slShadow_init(int w, int h)
{
    slShadow* me = malloc(sizeof(slShadow));
    me->w = w;
    me->h = h;
    me->mesh = slMesh_init("assets/objs/rect/model.gltf");

    // FBO Creation
    glGenFramebuffers(1, &me->id);
    glBindFramebuffer(GL_FRAMEBUFFER, me->id);
    
    // Color Texture Creation
    glGenTextures(1, &me->color);
    glBindTexture(GL_TEXTURE_2D, me->color);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Texture Attachement
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, me->color, 0);
    
    /*
    // Stencil Texture Creation
    glGenTextures(1, &me->stencil);
    glBindTexture(GL_TEXTURE_2D, me->stencil);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX8, w, h, 0, GL_STENCIL_INDEX8, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Texture Attachement
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, me->stencil, 0);
    */
    
    // RBO
    // Generation de l'identifiant
    glGenRenderbuffers(1, &me->depth);
    // Verrouillage
    glBindRenderbuffer(GL_RENDERBUFFER, me->depth);
    // Configuration du Render Buffer
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, me->w, me->h);
    // Deverrouillage
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
   // Association du Depth Buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, me->depth);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        // Liberation des buffers
        glDeleteFramebuffers(1, &me->id);
        glDeleteRenderbuffers(1, &me->depth);
        SL_errorPrint(STRING, "Error : the Shadow not created");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return me;
}

void slShadow_free(slShadow* me)
{
    slMesh_free(me->mesh);
    free(me);
}

void slShadow_clear(slShadow* me)
{
   glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, me->w, me->h);
}

void slShadow_draw(slShadow* me, slShader* shader, slWindow* win)
{
    float near = 0.1f;
    float far  = 100.f;
    mat4 ortho;
    mat4 view;
    mat4 model;
    glm_ortho(-1.f, 1.f, -1.f, 1.f, near, far, ortho);
    glm_lookat((vec3){0.f, 30.f, 30.f}, (vec3){0.f, 0.f, 0.f}, (vec3){0.f, 1.f, 0.f}, view);
    glm_mat4_identity(model);
    glm_scale(model, (vec3){10.f, 10.f, 10.f});
    
    slShader_use(shader);
    glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "projection"), 1, GL_FALSE, *(win->perspective));
    
    glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "view"), 1, GL_FALSE, *(win->view));
    
    glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "lightProj"), 1, GL_FALSE, *(ortho));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "lightView"), 1, GL_FALSE, *(view));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(shader), "model"), 1, GL_FALSE, *(model));

    // Verrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, me->color);
    
	slMesh_draw(me->mesh);
	
	// Deverrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, 0);
    slShader_stop();
}

unsigned int slShadow_getID(slShadow* me)
{
	return me->id;
}

unsigned int slShadow_getColorID(slShadow* me)
{
	return me->color;
}

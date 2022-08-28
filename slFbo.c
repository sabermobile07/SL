#include "SL.h"

struct slFbo
{
	GLuint id;
    int w;
    int h;
    slVector colorBuffers; // textures
    GLuint depthBufferID;
    bool needStencilBuffer;
    slMesh* mesh;
    slShader shader;
};

slFbo* slFbo_init(char* dir, char* shaderName, int w, int h, bool needStencilBuffer)
{
	slFbo* me = malloc(sizeof(slFbo));
	me->id = 0;
	me->w = w;
	me->h = h;
	me->colorBuffers = slVector_init(sizeof(slTexture));
	me->depthBufferID = 0;
	me->needStencilBuffer = needStencilBuffer;
	char s[256] = "";
	sprintf(s, "assets/objs/%s/model.gltf", dir);
	me->mesh = slMesh_init(s);
	slShader_init(&me->shader, shaderName);
	
	slFbo_setup(me);
	
	return me;
}

void slFbo_free(slFbo* me)
{
    // Destruction des buffers
    glDeleteFramebuffers(1, &me->id);
    glDeleteRenderbuffers(1, &me->depthBufferID);
    slVector_free(&me->colorBuffers);
    slMesh_free(me->mesh);
    slShader_free(&me->shader);
}

void slFbo_clear(slFbo* me)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //glClearDepthf(1.0f); // = to zfar
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, me->w, me->h);
}

void slFbo_draw(slFbo* me, slWindow* win)
{
	glDisable(GL_DEPTH_TEST);
    mat4 ortho;
	glm_mat4_identity(ortho);
    glm_ortho(-1.f, 1.f, -1.f, 1.f, 0.1f, 100.f, ortho);
	mat4 model;
	glm_mat4_identity(model);
    
	slShader_use(&me->shader);
    glUniformMatrix4fv(glGetUniformLocation(slShader_getID(&me->shader), "projection"), 1, GL_FALSE, *(ortho));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(&me->shader), "view"), 1, GL_FALSE, *(win->view));
	glUniformMatrix4fv(glGetUniformLocation(slShader_getID(&me->shader), "model"), 1, GL_FALSE, *(model));
	
	
	// Verrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, slFbo_getColorBufferID(me, 0));
    
	slMesh_draw(me->mesh);
	
	// Deverrouillage de la texture
    glBindTexture(GL_TEXTURE_2D, 0);
    slShader_stop();
}

void slFbo_copy(slFbo* dst, slFbo* src)
{
    dst->w = src->w;
    dst->h = src->h;
    dst->needStencilBuffer = src->needStencilBuffer;
    
    slFbo_setup(dst);
}

void slFbo_createRenderBuffer(slFbo* me, GLenum format)
{
    // Destruction d'un eventuel ancien Render Buffer
    if(glIsRenderbuffer(me->depthBufferID) == GL_TRUE)
    {
        glDeleteRenderbuffers(1, &me->depthBufferID);
    }
    // Generation de l'identifiant
    glGenRenderbuffers(1, &me->depthBufferID);
    // Verrouillage
    glBindRenderbuffer(GL_RENDERBUFFER, me->depthBufferID);

    // Configuration du Render Buffer
    glRenderbufferStorage(GL_RENDERBUFFER, format, me->w, me->h);

    // Deverrouillage
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

bool slFbo_setup(slFbo* me)
{
    // Verification d'un eventuel ancien FBO
    if(glIsFramebuffer(me->id) == GL_TRUE)
    {
        glDeleteFramebuffers(1, &me->id);
        // Liberation des Color Buffers
        slVector_free(&me->colorBuffers);
    }
    // Generation d'un id
    glGenFramebuffers(1, &me->id);
    // Verrouillage du Frame Buffer
    glBindFramebuffer(GL_FRAMEBUFFER, me->id);

        // Creation du Color Buffer
        slTexture* colorBuffer = slTexture_initTexture(me->w, me->h, GL_RGBA, GL_RGBA, true);
        slTexture_chargerTextureVide(colorBuffer);
        // Ajout au tableau
        slVector_push(&me->colorBuffers, colorBuffer);
        // Creation du Depth Buffer et du Stencil Buffer (si besoin)
        if(me->needStencilBuffer == true)
        {
            //slFbo_createRenderBuffer(me, GL_DEPTH24_STENCIL8);
            slFbo_createRenderBuffer(me, GL_STENCIL_INDEX8);
        }
        else
        {
            //slFbo_createRenderBuffer(me, GL_DEPTH_COMPONENT24);
            slFbo_createRenderBuffer(me, GL_DEPTH_COMPONENT16);
            // My creation of depth buffer
            
        }

        // Association du Color Buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, slFbo_getColorBufferID(me, 0), 0);
        
        // Association du Depth Buffer et du Stencil Buffer (si besoin)
        if(me->needStencilBuffer == true)
        {
            //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, me->depthBufferID);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, me->depthBufferID);
        }
        else
        {
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, me->depthBufferID);
        }

        // Verification de l'integrite du FBO
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            // Liberation des buffers
            glDeleteFramebuffers(1, &me->id);
            glDeleteRenderbuffers(1, &me->depthBufferID);
            slVector_free(&me->colorBuffers);
            // Affichage d'un message d'erreur et retour de la valeur false
            printf("Erreur : le FBO est mal construit\n");
            SL_errorPrint(STRING, "Error : the FBO not created");
            return false;
        }

    // Deverrouillage du Frame Buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Si tout s'est bien passe, on renvoie la valeur true
    return true;
}

GLuint slFbo_getID(slFbo* me)
{
    return me->id;
}

GLuint slFbo_getColorBufferID(slFbo* me, unsigned int index)
{
    return slTexture_getID(slVector_getData(&me->colorBuffers, index));
}

GLuint slFbo_getDepthBufferID(slFbo* me)
{
	return me->depthBufferID;
}

int slFbo_getWidth(slFbo* me)
{
    return me->w;
}

int slFbo_getHeight(slFbo* me)
{
    return me->h;
}

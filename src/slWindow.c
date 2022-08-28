#include <slWindow.h>

// slWindow -------------------------------------------------
slWindow* slWindow_init(char* title, int w, int h)
{
    slWindow* me = malloc(sizeof(slWindow));
    me->windowSDL = 0;
    me->title = title;
    me->contextGL = 0;
    me->w = 0;
    me->h = 0;
    
    // Window creation
    if( w == 0 || h == 0)
    {
    	me->windowSDL= SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    }
    else
    {
    	me->windowSDL= SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    }
    
    if(me->windowSDL == 0)
    {
    	char s[200] = "";
        sprintf(s, "Error creationn of window : %s", SDL_GetError());
        SL_errorPrint(STRING, s);
        return NULL;
    }

    // OpenGL Context Creation
    me->contextGL = SDL_GL_CreateContext(me->windowSDL);
    if(me->contextGL == 0)
    {
        char s[200] = "";
        sprintf(s, "Error in creation of OpenGL context : %s", SDL_GetError());
        SL_errorPrint(STRING, s);
        SDL_DestroyWindow(me->windowSDL);
        return NULL;
    }

    // OpenGL Initialisation
    #ifdef WIN32
        // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
        if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress))
        {
        	SL_errorPrint(STRING, "Failed to initialize OpenGL context");
            return NULL;
        }

        /*
        // Alternative use the builtin loader, e.g. if no other loader function is available
        if (!gladLoadGL())
        {
            printf("Failed to initialize OpenGL context\n");
            return -1;
        }
        */
    #endif
    
    slWindow_update(me);
    slWindow_setStatus( me, TRUE );

    // Activation du Depth Buffer
    glEnable(GL_DEPTH_TEST);
    
    /* Enable blending, necessary for our alpha texture */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // FINISHED --------------------------------------------

    return me;
}

void slWindow_free(slWindow** me)
{
    SDL_GL_DeleteContext((*me)->contextGL);
    SDL_DestroyWindow((*me)->windowSDL);
    free(*me);
    *me = NULL;
}

void slWindow_setStatus(slWindow* me, int status)
{
    me->status = status;
}

int slWindow_getStatus(slWindow* me)
{
    return me->status;
}

int slWindow_getWidth(slWindow* me)
{
    return me->w;
}

int slWindow_getHeight(slWindow* me)
{
    return me->h;
}

void slWindow_copyRatio(slWindow* me, vec2 dest)
{
    dest[0] = me->ratio[0];
    dest[1] = me->ratio[1];
}

void slWindow_clear(slWindow* me)
{
    // Nettoyage de la vue
    glClearColor(0.31f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void slWindow_update(slWindow* me)
{
	//SDL_GetDesktopDisplayMode(0, &me->DM);
    SDL_GetWindowSize(me->windowSDL, &me->DM.w, &me->DM.h);
    me->w = me->DM.w;
    me->h = me->DM.h;
    
    // Calculate Ratio
    if(me->w < me->h)
    {
    	me->ratio[0] = 1.f;
    	me->ratio[1] = (float) me->h / (float) me->w;
    }
    else
    {
    	me->ratio[0] = (float)me->w / (float)me->h;
    	me->ratio[1] = 1.f;
    }
    // Calculate pixel in OpenGL
    me->px[0] =  2.f / (float) me->w;
    me->px[1] = 2.f / (float) me->h;
    
    // Définition de la zone d'affichage
    glViewport(0, 0, me->w, me->h);
}

void slWindow_draw(slWindow* me)
{
    // Actualisation de la vue
    SDL_GL_SwapWindow(me->windowSDL);
}

void slWindow_hide(slWindow* window)
{
    SDL_HideWindow(window->windowSDL);
}

void slWindow_show(slWindow* window)
{
    SDL_ShowWindow(window->windowSDL);
}
// End slWindow ___________________________________

#include <SL.h>

struct slWindow
{
	SDL_Window* win;
	char title[64];
	int w;
	int h;
	SDL_GLContext glContext;
	bool status;
};

slWindow* slWindow_init(char* title, int w, int h)
{
	slWindow* me = calloc(1, sizeof(slWindow));
	snprintf(me->title, sizeof(me->title), title);
	me->w = w;
	me->h = h;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
    	SL_printErrors("\nSDL init failed: ", SDL_GetError(), "\n");
        return -1;
    }

    // نطلب OpenGL ES 3.0
     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    me->win = SDL_CreateWindow(
        me->title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        me->w, me->h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!me->win)
    {
    	SL_printErrors("\nWindow creation failed: ", SDL_GetError(), "\n");
        SDL_Quit();
        return -1;
    }

    me->glContext = SDL_GL_CreateContext(me->win);
    if (!me->glContext)
    {
    	SL_printErrors("\nOpenGL context failed: ", SDL_GetError(), "\n");
        SDL_DestroyWindow(me->win);
        SDL_Quit();
        return -1;
    }

    SDL_GL_SetSwapInterval(1); // vsync
    //glViewport(0, 0, 800, 600);
    
    me->status = true;
	
	return me;
}

void slWindow_free(slWindow* me)
{
	SDL_GL_DeleteContext(me->glContext);
    SDL_DestroyWindow(me->win);
    SDL_Quit();
	free(me);
}

bool slWindow_getStatus(slWindow* me)
{
	return me->status;
}

void slWindow_setStatus(slWindow* me, bool status)
{
	me->status = status;
}

void slWindow_draw(slWindow* me)
{
	SDL_GL_SwapWindow(me->win);
}

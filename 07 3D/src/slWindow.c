#include <SL.h>

struct slWindow
{
	SDL_Window* win;
	slStr* title;
	int w;
	int h;
	SDL_GLContext glContext;
	bool status;
};

slWindow* slWindow_new(char* title, int w, int h)
{
	slWindow* me = malloc(sizeof(slWindow));
	if(!me) {
		slStr_add(error, "Create window failed\n");
		SL_error();
		return NULL;
	}
	
	me->title = slStr_new(title);
	me->w = w;
	me->h = h;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
    	slStr_add(error, "SDL init failed: ");
    	slStr_add(error, SDL_GetError());
    	SL_error();
        return NULL;
    }

    // نطلب OpenGL ES 3.0
     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    me->win = SDL_CreateWindow(
        slStr_get(me->title),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        me->w, me->h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!me->win)
    {
    	slStr_add(error, "Window creation failed: ");
    	slStr_add(error, SDL_GetError());
    	SL_error();
        SDL_Quit();
        return NULL;
    }

    me->glContext = SDL_GL_CreateContext(me->win);
    if (!me->glContext)
    {
    	slStr_add(error, "OpenGL context failed: ");
    	slStr_add(error, SDL_GetError());
    	SL_error();
        SDL_DestroyWindow(me->win);
        SDL_Quit();
        return NULL;
    }

    SDL_GL_SetSwapInterval(1); // vsync
    //glViewport(0, 0, 800, 600);
    
    glEnable(GL_DEPTH_TEST);
    
    me->status = true;
	
	return me;
}

void slWindow_free(slWindow* me)
{
	slStr_free(&me->title);
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

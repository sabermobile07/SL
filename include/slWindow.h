#ifndef __SL_WINDOW_H
#define __SL_WINDOW_H

#include <SL.h>

// slWindow -------------------------------------------------
typedef struct slWindow slWindow;
struct slWindow
{
    SDL_Window* windowSDL;
    SDL_DisplayMode DM;
    SDL_GLContext contextGL;
    slInput* in;
    char* title;
    int w; // Width
    int h; // Height
    vec2 ratio; // Ratio of screen
    vec2 px; // Pixel in opengl
    int status;
};

slWindow* slWindow_init(char* title, int w, int h);
void slWindow_free(slWindow** window);
void slWindow_setStatus(slWindow* me, int status);
int slWindow_getStatus(slWindow* me);
int slWindow_getWidth(slWindow* me);
int slWindow_getHeight(slWindow* me);
void slWindow_copyRatio(slWindow* me, vec2 dest);
void slWindow_clear(slWindow* me);
void slWindow_update(slWindow* window);
void slWindow_draw(slWindow* me);
void slWindow_hide(slWindow* window);
void slWindow_show(slWindow* window);
void slWindow_print(slWindow* me, char* text, GLfloat* color, float x, float y);
// End slWindow _____________________

#endif
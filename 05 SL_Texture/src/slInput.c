#include <SL.h>

struct slInput
{
        SDL_Event ev;
        SL_STATE key[SDL_NUM_SCANCODES];
        SL_STATE mouse[8];
        int x;
        int y;
        int xRel;
        int yRel;
        bool status;
};

slInput* slInput_init()
{
	slInput* me = calloc(1, sizeof(slInput));
	
	return me;
}

void slInput_free(slInput* me)
{
	free(me);
	me = NULL;
}

void slInput_clear(slInput* me)
{
    me->x = IDLE;
    me->y = IDLE;
    me->xRel = IDLE;
    me->yRel = IDLE;
    me->status = IDLE;

    // Initialisation du tableau key[]
    for(int i=0; i < SDL_NUM_SCANCODES; i++)
    {
        me->key[i] = IDLE;
    }

    // Initialisation du tableau mouse[]
    for(int i=0; i < 8; i++)
    {
        me->mouse[i] = IDLE;
    }
}

void slInput_update(slInput * me)
{
    // Pour eviter des mouvements fictifs de la souris, on reinitialise les coordonnees relatives
    slInput_clear(me);

    // Boucle d'evenements
    while(SDL_PollEvent(&me->ev))
    {
        // Switch sur le type d'evenement
        switch(me->ev.type)
        {
            // Cas d'une key enfoncee
            case SDL_KEYDOWN:
                me->key[me->ev.key.keysym.scancode] = DOWN;
            break;

            // Cas d'une key relechee
            case SDL_KEYUP:
                me->key[me->ev.key.keysym.scancode] = UP;
            break;

            // Cas de pression sur un btn de la souris
            case SDL_MOUSEBUTTONDOWN:
                me->mouse[me->ev.button.button] = DOWN;
            break;

            // Cas du relechement d'un btn de la souris
            case SDL_MOUSEBUTTONUP:
                me->mouse[me->ev.button.button] = UP;
            break;

            // Cas d'un mouvement de souris
            case SDL_MOUSEMOTION:
                me->x = me->ev.motion.x;
                me->y = me->ev.motion.y;
                me->xRel = me->ev.motion.xrel;
                me->yRel = me->ev.motion.yrel;
            break;
            
            case SDL_FINGERDOWN:
            break;
            
            case SDL_FINGERUP:
            break;

            // Cas de la fermeture de la fenetre
            case SDL_WINDOWEVENT:
                if(me->ev.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    me->status = false;
                }
            break;

            default:
            break;
        }
    }
}

bool slInput_getStatus(slInput * me)
{
    return me->status;;
}

SL_STATE slInput_getKey(slInput * me, const SDL_Scancode key)
{
    return me->key[key];
}

SL_STATE slInput_getMouseBtn(slInput * me, const Uint8 btn)
{
    return me->mouse[btn];
}

// Getters concernant la position du curseur
int const slInput_getX(slInput * me)
{
    return me->x;
}

int const slInput_getY(slInput * me)
{
    return me->y;
}

int const slInput_getXRel(slInput * me)
{
    return me->xRel;
}

int const slInput_getYRel(slInput * me)
{
    return me->yRel;
}

bool slInput_testMouseMove(slInput * me)
{
    if(me->xRel == 0 && me->yRel == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void slInput_showMouse(slInput * me, bool response)
{
    if(response)
    {
        SDL_ShowCursor(SDL_ENABLE);
    }
    else
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
}

void slInput_catchMouse(slInput * me, bool response)
{
    if(response)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

#include <SL.h>

struct slInput
{
        SDL_Event m_evenements;
        int m_touches[SDL_NUM_SCANCODES]; // BOOL
        int m_boutonsSouris[8]; // BOOL
        int m_x;
        int m_y;
        int m_xRel;
        int m_yRel;
        int m_terminer; // BOOL
};

slInput* slInput_init()
{
	slInput* me = malloc(sizeof(slInput));
	
	return me;
}

void slInput_clear(slInput* me)
{
    me->m_x = IDLE;
    me->m_y = IDLE;
    me->m_xRel = IDLE;
    me->m_yRel = IDLE;
    me->m_terminer = IDLE;

    // Initialisation du tableau m_touches[]
    for(int i=0; i < SDL_NUM_SCANCODES; i++)
    {
        me->m_touches[i] = IDLE;
    }

    // Initialisation du tableau m_boutonsSouris[]
    for(int i=0; i < 8; i++)
    {
        me->m_boutonsSouris[i] = IDLE;
    }
    
    return me;
}

void slInput_free(slInput** me)
{
	free(*me);
	*me = NULL;
}

void slInput_update(slInput * me)
{
    // Pour �viter des mouvements fictifs de la souris, on r�initialise les coordonn�es relatives
    //slInput_clear(me);

    // Boucle d'�v�nements
    while(SDL_PollEvent(&me->m_evenements))
    {
        // Switch sur le type d'�v�nement
        switch(me->m_evenements.type)
        {
            // Cas d'une touche enfonc�e
            case SDL_KEYDOWN:
                me->m_touches[me->m_evenements.key.keysym.scancode] = DOWN;
            break;

            // Cas d'une touche rel�ch�e
            case SDL_KEYUP:
                me->m_touches[me->m_evenements.key.keysym.scancode] = UP;
            break;

            // Cas de pression sur un bouton de la souris
            case SDL_MOUSEBUTTONDOWN:
                me->m_boutonsSouris[me->m_evenements.button.button] = DOWN;
            break;

            // Cas du rel�chement d'un bouton de la souris
            case SDL_MOUSEBUTTONUP:
                me->m_boutonsSouris[me->m_evenements.button.button] = UP;
            break;

            // Cas d'un mouvement de souris
            case SDL_MOUSEMOTION:
                me->m_x = me->m_evenements.motion.x;
                me->m_y = me->m_evenements.motion.y;
                me->m_xRel = me->m_evenements.motion.xrel;
                me->m_yRel = me->m_evenements.motion.yrel;
            break;
            
            case SDL_FINGERDOWN:
            break;
            
            case SDL_FINGERUP:
            break;

            // Cas de la fermeture de la fen�tre
            case SDL_WINDOWEVENT:
                if(me->m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    me->m_terminer = 1;
                }
            break;

            default:
            break;
        }
    }
}

int const slInput_terminer(slInput * me)
{
    return me->m_terminer;
}

int const slInput_getTouche(slInput * me, const SDL_Scancode touche)
{
    return me->m_touches[touche];
}

int const slInput_getBoutonSouris(slInput * me, const Uint8 bouton)
{
    return me->m_boutonsSouris[bouton];
}

int const slInput_mouvementSouris(slInput * me)
{
    if(me->m_xRel == 0 && me->m_yRel == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Getters concernant la position du curseur
int const slInput_getX(slInput * me)
{
    return me->m_x;
}

int const slInput_getY(slInput * me)
{
    return me->m_y;
}

int const slInput_getXRel(slInput * me)
{
    return me->m_xRel;
}

int const slInput_getYRel(slInput * me)
{
    return me->m_yRel;
}

void slInput_afficherPointeur(slInput * me, int reponse)
{
    if(reponse)
    {
        SDL_ShowCursor(SDL_ENABLE);
    }
    else
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
}

void slInput_capturerPointeur(slInput * me, int reponse)
{
    if(reponse)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

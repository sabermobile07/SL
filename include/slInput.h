#ifndef __SL_INPUT_H
#define __SL_INPUT_H

    // Include
    #include <SL.h>

    // Classe
    typedef struct slInput slInput;

    slInput* slInput_init();
    void slInput_free(slInput** me);
    void slInput_update(slInput * me);
    int const slInput_terminer(slInput * me); // BOOL
    int const slInput_getTouche(slInput * me, const SDL_Scancode touche); // BOOL
    int const slInput_getBoutonSouris(slInput * me, const Uint8 bouton); // BOOL
    int const slInput_mouvementSouris(slInput * me); // BOOL
    int const slInput_getX(slInput * me);
    int const slInput_getY(slInput * me);
    int const slInput_getXRel(slInput * me);
    int const slInput_getYRel(slInput * me);
    void slInput_afficherPointeur(slInput * me, int reponse);
    void slInput_capturerPointeur(slInput * me, int reponse);

#endif

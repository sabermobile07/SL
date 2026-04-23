#ifndef __SL_INPUT_H
#define __SL_INPUT_H

    // Include
    #include <SL.h>

    // Classe
    typedef struct slInput slInput;

    slInput* slInput_init();
    void slInput_free(slInput* me);
    void slInput_clear(slInput* me);
    void slInput_update(slInput * me);
    bool slInput_getStatus(slInput * me);
    SL_STATE slInput_getKey(slInput * me, const SDL_Scancode key);
    SL_STATE slInput_getMouseBtn(slInput * me, const Uint8 btn);
    int const slInput_getX(slInput * me);
    int const slInput_getY(slInput * me);
    int const slInput_getXRel(slInput * me);
    int const slInput_getYRel(slInput * me);
    bool slInput_testMouseMove(slInput * me);
    void slInput_showMouse(slInput * me, bool response);
    void slInput_catchMouse(slInput * me, bool response);

#endif

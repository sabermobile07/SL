#ifndef __SL_CAMERA_H
#define __SL_CAMERA_H

    #include <SL.h>

    // Classe
    typedef struct slCamera slCamera;
    

    //void slCamera_init(slCamera * me);
    //void slCamera_init(slCamera * me, vec3 position, vec3 pointCible, vec3 axeVertical);
    slCamera* slCamera_init(vec3 position, vec3 pointCible, vec3 axeVertical, float sensibilite, float vitesse);
    void slCamera_free(slCamera** me);
    void slCamera_orienter(slCamera * me, int xRel, int yRel);
    void slCamera_deplacer(slCamera * me, slInput *input);
    void slCamera_lookat(slCamera * me, mat4 * view);
    void slCamera_getPos(slCamera* me, vec3 dest);
    void slCamera_getOrigin(slCamera* me, vec3 dest);
    void slCamera_getDir(slCamera* me, vec3 dest);
    void slCamera_setPointcible(slCamera * me, vec3 pointCible);
    void slCamera_setPosition(slCamera * me, vec3 position);
    // Getters et Setters
    float const slCamera_getSensibilite(slCamera * me);
    float const slCamera_getVitesse(slCamera * me);
    void slCamera_setSensibilite(slCamera * me, float sensibilite);
    void slCamera_setVitesse(slCamera * me, float vitesse);
    void slCamera_move(slCamera* me, vec3 distance);

#endif // CAMERA_H_INCLUDED

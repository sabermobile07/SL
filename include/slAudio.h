#ifndef  __SLAUDIO_H
#define  __SLAUDIO_H

#include <SL.h>

typedef struct slAudio slAudio;

slAudio* slAudio_init(char* path);
void slAudio_free(slAudio* me);
void slAudio_play(slAudio* me);
void slAudio_pause();
void slAudio_resume();
void slAudio_setVolume(unsigned int percent);

#endif

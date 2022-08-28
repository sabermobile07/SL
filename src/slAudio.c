#include <slAudio.h>

struct slAudio
{
	Mix_Music* music;
};

slAudio* slAudio_init(char* path)
{
	slAudio* me = malloc(sizeof(slAudio));
	me->music = Mix_LoadMUS(path);
	
	return me;
}

void slAudio_free(slAudio* me)
{
	free(me);
	me = NULL;
}

void slAudio_play(slAudio* me)
{
	Mix_PlayMusic(me->music, 0);
}

void slAudio_pause()
{
	Mix_PauseMusic();
}

void slAudio_resume()
{
	Mix_ResumeMusic();
}

void slAudio_setVolume(unsigned int percent)
{
	unsigned int v = (percent * 100) / 128;
	Mix_VolumeMusic(v);
}

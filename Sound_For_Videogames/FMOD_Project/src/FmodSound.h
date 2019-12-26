#ifndef __FMODSOUND_H__
#define __FMODSOUND_H__

#include <fmod.hpp>
#include <iostream>

class FmodSound
{
private:
	FMOD::System* _system;
	FMOD_RESULT _result;

	FMOD::Sound* _sound;
	FMOD::Channel* _channel;
	
	char* _soundPath;
	float _volume;
public:
	FmodSound(char* filename, FMOD::System* system);
	~FmodSound();
	void Play();
	void Pause();
	void Resume();
	void Stop();

	void setVolume(float volume);
	void setPan(float pan);

	void FadeIn(float miliSeconds);
	void FadeOut(float miliSeconds);
};

#endif // !__FMOD_H__ 

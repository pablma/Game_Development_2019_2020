#pragma once

#include "FMOD_System.h"
#include <chrono>

class FMOD_Sound
{
private:
	FMOD::Sound* _sound = nullptr;
	FMOD::Channel* _channel = nullptr;

	float _vol;
	float _pitch;
	float _pan;

	bool _fadeInActive = false;
	bool _fadeOutActive = false;
	float _delay;

	std::chrono::steady_clock::time_point _start;
	std::chrono::steady_clock::time_point _current;

	FMOD_RESULT _result;

	std::string _soundPath = "../res/";
public:
	FMOD_Sound();
	FMOD_Sound(std::string filename);
	~FMOD_Sound();

	void Play();
	void Pause();
	void Stop();
	void Tick();

	void FadeIn(float miliseconds);
	void FadeOut(float miliseconds);

	void setVolume(float vol) { _result = _channel->setVolume(vol); };
	void setPitch(float pitch) { _result = _channel->setPitch(pitch); };
	void setPan(float pan) { _result = _channel->setPan(_pan); };
};
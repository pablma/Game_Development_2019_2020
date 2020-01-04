#pragma once
#include <fmod.hpp>
#include <string>

class AudioSource
{
private:
	FMOD::System* _system;
	FMOD::Sound* _sound;
	FMOD::Channel* _channel;
	FMOD_RESULT _result;

	float _volume;
	float _pitch;
	float _pan;

	FMOD_VECTOR _sourcePos;	// Posición del listener
	FMOD_VECTOR _sourceVel;	// Velocidad del listener
public:
	AudioSource(std::string filename, FMOD::System* system, FMOD_VECTOR pos, FMOD_VECTOR vel);
	~AudioSource();
	void Play();
};


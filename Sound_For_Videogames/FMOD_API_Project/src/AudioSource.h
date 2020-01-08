#pragma once
#include <fmod.hpp>
#include "FMOD_System.h"

class AudioSource
{
private:
	FMOD_VECTOR _pos;	// posicion del source
	FMOD_VECTOR _vel;	// velocidad del source

	FMOD::Sound* _sound = nullptr;
	FMOD::Channel* _channel = nullptr;

	FMOD_RESULT _result;
public:
	AudioSource();
	AudioSource(FMOD_VECTOR pos, FMOD_VECTOR vel);
	~AudioSource();

	void setPosition(FMOD_VECTOR pos);
	FMOD_VECTOR getPosition();
};
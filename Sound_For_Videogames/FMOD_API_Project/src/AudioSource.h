#pragma once
#include <fmod.hpp>
#include "FMOD_System.h"

class AudioSource
{
private:
	FMOD_VECTOR _pos;	// posicion del source
	FMOD_VECTOR _vel;	// velocidad del source
	FMOD_VECTOR _up;	// vector up: hacia la ``coronilla''
	FMOD_VECTOR _at;	// vector at: hacia donde mira
public:
	AudioSource();
	AudioSource(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at);
	~AudioSource();

	void setPosition(FMOD_VECTOR pos) { _pos = pos; };
	FMOD_VECTOR getPosition() { return _pos; };
};
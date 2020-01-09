#pragma once

#include "FMOD_System.h"

class AudioListener
{
private:
	FMOD_VECTOR _pos;	// posicion del listener
	FMOD_VECTOR _vel;	// velocidad del listener
	FMOD_VECTOR _up;	// vector up: hacia la ``coronilla'', posición del listener
	FMOD_VECTOR _at;	// vector at: hacia donde mira, 

	FMOD_RESULT _result;
public:
	AudioListener();
	AudioListener(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at);
	~AudioListener();

	void setPosition(FMOD_VECTOR pos);
	FMOD_VECTOR getPosition();
};
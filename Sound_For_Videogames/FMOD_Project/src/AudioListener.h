#pragma once
#include <fmod.hpp>

class AudioListener
{
private:
	FMOD::System* _system;
	FMOD_RESULT _result;

	FMOD_VECTOR _listenerPos;	// Posición del listener
	FMOD_VECTOR _listenerVel;	// Velocidad del listener
	FMOD_VECTOR _up;	// Vector up
	FMOD_VECTOR _at;	// Vector at: hacia donde mira
public:
	AudioListener() {};
	AudioListener(FMOD::System* system, FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at);
	~AudioListener();
	
	void setPosition(FMOD_VECTOR pos) { _listenerPos = pos; }
	FMOD_VECTOR getPosition() { return _listenerPos; }
};


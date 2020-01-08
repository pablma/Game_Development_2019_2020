#pragma once
#include <fmod.hpp>
#include "FMOD_System.h"

class AudioSource
{
private:
	FMOD_VECTOR _pos;	// posicion del source
	FMOD_VECTOR _vel;	// velocidad del source
	FMOD_VECTOR _coneDir;	// dirección del cono
	
	float _externalConeAngle = 60.0f;
	float _internalConeAngle = 30.0f;

	FMOD::Sound* _sound = nullptr;
	FMOD::Channel* _channel = nullptr;

	FMOD_RESULT _result;
public:
	AudioSource();
	AudioSource(FMOD_VECTOR pos, FMOD_VECTOR vel);
	AudioSource(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR coneDir);
	~AudioSource();

	void setPosition(FMOD_VECTOR pos);
	FMOD_VECTOR getPosition();

	void increaseInternalConeAngle(float increase);
	void decreaseInternalConeAngle(float decrease);
	void increaseExternalConeAngle(float increase);
	void decreaseExternalConeAngle(float decrease);
};
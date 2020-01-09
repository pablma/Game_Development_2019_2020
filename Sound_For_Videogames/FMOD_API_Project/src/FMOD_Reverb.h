#pragma once
#include "FMOD_System.h"

class FMOD_Reverb
{
private:
	FMOD::Reverb3D* _reverb = nullptr;
	FMOD_REVERB_PROPERTIES _properties;

	FMOD_VECTOR _pos;
	float _minDistance;
	float _maxDistance;

	FMOD_RESULT _result;
public:
	FMOD_Reverb();
	FMOD_Reverb(FMOD_VECTOR pos, float minDist, float maxDist, FMOD_REVERB_PROPERTIES prop);
	~FMOD_Reverb();

	FMOD_VECTOR getPosition() { return _pos; };
};
#include "FMOD_Reverb.h"

FMOD_Reverb::FMOD_Reverb()
{
}

FMOD_Reverb::FMOD_Reverb(FMOD_VECTOR pos, float minDist, float maxDist, FMOD_REVERB_PROPERTIES prop) : _pos(pos), _minDistance(minDist),
	_maxDistance(maxDist), _properties(prop)
{
	_result = FMOD_System::getFMODSystem()->createReverb3D(&_reverb);
	FMOD_System::ERRCHECK(_result);

	_result = _reverb->setProperties(&_properties);
	FMOD_System::ERRCHECK(_result);

	_result = _reverb->set3DAttributes(&_pos, _minDistance, _maxDistance);
	FMOD_System::ERRCHECK(_result);
}

FMOD_Reverb::~FMOD_Reverb()
{
	_result = _reverb->release();
	FMOD_System::ERRCHECK(_result);
}

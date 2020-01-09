#include "FMOD_Reverb.h"

FMOD_Reverb::FMOD_Reverb()
{
}

FMOD_Reverb::FMOD_Reverb(FMOD_VECTOR pos, float minDist, float maxDist, FMOD_REVERB_PROPERTIES prop) : _pos(pos), _minDistance(minDist),
	_maxDistance(maxDist), _properties(prop)
{
	FMOD_System::getFMODSystem()->createReverb3D(&_reverb);
	FMOD_REVERB_PROPERTIES prop1 = FMOD_PRESET_CONCERTHALL;
	_reverb->setProperties(&_properties);
	FMOD_VECTOR pos1_ = { 0, 0, 0 };
	float mindist = 10, maxdist = 20;
	_reverb->set3DAttributes(&pos1_, mindist, maxdist);
	/*_result = FMOD_System::getFMODSystem()->createReverb3D(&_reverb);
	FMOD_System::ERRCHECK(_result);

	_result = _reverb->setProperties(&_properties);
	FMOD_System::ERRCHECK(_result);

	_result = _reverb->set3DAttributes(&_pos, _minDistance, _maxDistance);
	FMOD_System::ERRCHECK(_result);

	_result = _reverb->setActive(true);
	FMOD_System::ERRCHECK(_result);*/
}

FMOD_Reverb::~FMOD_Reverb()
{
	_result = _reverb->release();
	FMOD_System::ERRCHECK(_result);
}

#include "AudioListener.h"

AudioListener::AudioListener()
{
}

AudioListener::AudioListener(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at) : _pos(pos), _vel(vel), _up(up), _at(at)
{
	_result = FMOD_System::getFMODSystem()->set3DListenerAttributes(0, &_pos, &_vel, &_at, &_up);
	FMOD_System::ERRCHECK(_result);
}

AudioListener::~AudioListener()
{
}

void AudioListener::setPosition(FMOD_VECTOR pos)
{
	_pos = pos;
	_result = FMOD_System::getFMODSystem()->set3DListenerAttributes(0, &_pos, &_vel, &_at, &_up);
	FMOD_System::ERRCHECK(_result);
}

FMOD_VECTOR AudioListener::getPosition()
{
	return _pos;
}

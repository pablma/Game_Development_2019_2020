#include "AudioListener.h"

AudioListener::AudioListener()
{
}

AudioListener::AudioListener(FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at) : _pos(pos), _vel(vel), _up(up), _at(at)
{
	FMOD_System::getFMODSystem()->set3DListenerAttributes(0, &_pos, &_vel, &_up, &_at);
}

AudioListener::~AudioListener()
{
}
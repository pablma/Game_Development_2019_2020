#include "AudioListener.h"



AudioListener::AudioListener(FMOD::System* system, FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at)
{
	_system = system;

	_listenerPos = pos;
	_listenerVel = vel;
	_up = up;
	_at = at;

	_result = _system->set3DListenerAttributes(0, &_listenerPos, &_listenerVel, &_up, &_at);
}


AudioListener::~AudioListener()
{
}

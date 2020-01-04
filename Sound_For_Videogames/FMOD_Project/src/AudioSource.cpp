#include "AudioSource.h"



AudioSource::AudioSource(std::string filename, FMOD::System* system, FMOD_VECTOR pos, FMOD_VECTOR vel)
{
	_system = system;
	_result = _system->createSound(filename.c_str(), FMOD_3D | FMOD_LOOP_NORMAL, 0, &_sound);

	_sourcePos = pos;
	_sourceVel = vel;
	
	_volume = 1.0f;
	_pan = 1.0f;
	_pitch = 1.0f;
}


AudioSource::~AudioSource()
{
}


void AudioSource::Play()
{
	_result = _system->playSound(_sound, 0, false, &_channel);
	_result = _channel->set3DAttributes(&_sourcePos, &_sourceVel);
}

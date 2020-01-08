#include "AudioSource.h"

AudioSource::AudioSource()
{
}

AudioSource::AudioSource(FMOD_VECTOR pos, FMOD_VECTOR vel) : _pos(pos), _vel(vel)
{
	_result = FMOD_System::getFMODSystem()->createSound("../res/music.ogg", FMOD_3D | FMOD_LOOP_NORMAL, 0, &_sound);
	FMOD_System::ERRCHECK(_result);

	_result = FMOD_System::getFMODSystem()->playSound(_sound, 0, true, &_channel);
	FMOD_System::ERRCHECK(_result);

	_result = _channel->set3DAttributes(&_pos, &_vel);
	FMOD_System::ERRCHECK(_result);

	_result = _channel->setPaused(false);
	FMOD_System::ERRCHECK(_result);
}

AudioSource::~AudioSource()
{
}

void AudioSource::setPosition(FMOD_VECTOR pos)
{
	_pos = pos;
	_result = _channel->set3DAttributes(&_pos, &_vel);
	FMOD_System::ERRCHECK(_result);
}

FMOD_VECTOR AudioSource::getPosition()
{
	return _pos;
}

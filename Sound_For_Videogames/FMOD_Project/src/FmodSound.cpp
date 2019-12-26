#include "FmodSound.h"


FmodSound::FmodSound(char* filename, FMOD::System* system)
{
	_system = system;
	_result = _system->createSound("../res/piano.ogg", FMOD_DEFAULT, 0, &_sound);
	_volume = 1.0f;
}

FmodSound::~FmodSound()
{
	_result = _sound->release();
}

void FmodSound::Play()
{
	bool playing;
	_channel->isPlaying(&playing);
	
	if(playing)
		_channel->stop();
	
	_result = _system->playSound(_sound, 0, false, &_channel);
}

void FmodSound::Pause()
{
	_channel->setPaused(true);
}

void FmodSound::Resume()
{
	_channel->setPaused(false);
}

void FmodSound::Stop()
{
	_channel->stop();
}

void FmodSound::setVolume(float volume)
{
	_channel->setVolume(volume);
}

void FmodSound::setPan(float pan)
{
	_channel->setPan(pan);
}

void FmodSound::FadeIn(float miliSeconds)
{
}

void FmodSound::FadeOut(float miliSeconds)
{
	std::cout << _volume << std::endl;
	if (_volume > 0.0f)
	{
		_volume -= 0.05f;
		_channel->setVolume(_volume);
	}
		
	_system->update();
}

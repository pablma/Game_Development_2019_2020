#include "FMOD_Sound.h"

FMOD_Sound::FMOD_Sound()
{
}

FMOD_Sound::FMOD_Sound(std::string filename)
{
	_vol = 1.0f;

	_result = FMOD_System::getFMODSystem()->createSound((_soundPath + filename).c_str(), FMOD_DEFAULT, 0, &_sound);
	FMOD_System::ERRCHECK(_result);
}

FMOD_Sound::~FMOD_Sound()
{
	_result = _sound->release();
	FMOD_System::ERRCHECK(_result);
}

void FMOD_Sound::Play()
{
	_result = FMOD_System::getFMODSystem()->playSound(_sound, 0, false, &_channel);
	FMOD_System::ERRCHECK(_result);
}

void FMOD_Sound::Pause()
{
	_result = _channel->setPaused(true);
	FMOD_System::ERRCHECK(_result);
}

void FMOD_Sound::Stop()
{
	_result = _channel->stop();
	FMOD_System::ERRCHECK(_result);
}

void FMOD_Sound::Tick()
{
	if (_fadeInActive) {
		float time = std::chrono::duration_cast<std::chrono::milliseconds>(_current - _start).count();
		_vol = time / _delay;

		if (time >= _delay) {
			_fadeInActive = false;
			_vol = 1;
		}
		else
			_current = std::chrono::steady_clock::now();

		setVolume(_vol);
	}
	else if (_fadeOutActive) {
		float time = std::chrono::duration_cast<std::chrono::milliseconds>(_current - _start).count();
		_vol = 1 - time / _delay;

		if (time >= _delay) {
			_fadeOutActive = false;
			_vol = 0;
		}
		else
			_current = std::chrono::steady_clock::now();

		setVolume(_vol);
	}
}

void FMOD_Sound::FadeIn(float miliseconds)
{
	_delay = miliseconds;
	_fadeInActive = true;

	_start = std::chrono::steady_clock::now();
	_current = std::chrono::steady_clock::now();

	setVolume(0.0f);
}

void FMOD_Sound::FadeOut(float miliseconds)
{
	_delay = miliseconds;
	_fadeOutActive = true;

	_start = std::chrono::steady_clock::now();
	_current = std::chrono::steady_clock::now();

	setVolume(1.0f);
}

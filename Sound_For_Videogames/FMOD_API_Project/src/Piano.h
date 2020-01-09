#pragma once
#include "FMOD_Sound.h"
#include <math.h>

class Piano
{
private:
	FMOD::Sound* _CKeySound = nullptr;
	FMOD::Channel* _channel = nullptr;

	int _octave = 12;

	FMOD_RESULT _result;

	float calculatePitch(float i);
	void increaseOctave();
	void decreaseOctave();
	void Play(int frec);
public:
	Piano();
	~Piano();

	void input(char c);
	void update();
};
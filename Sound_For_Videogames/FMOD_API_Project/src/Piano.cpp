#include "Piano.h"

float Piano::calculatePitch(float i)
{
	return powf(2, i / _octave);
}

void Piano::increaseOctave()
{
	_octave += 12;
}

void Piano::decreaseOctave()
{
	_octave -= 12;
}

void Piano::Play(int frec)
{
	float pitch = calculatePitch(frec);
	FMOD::Channel* ch;

	FMOD_System::getFMODSystem()->playSound(_CKeySound, 0, true, &ch);
	ch->setPitch(pitch);
	ch->setPaused(false);
}

Piano::Piano()
{
	FMOD_System::getFMODSystem()->createSound("../res/piano.ogg", FMOD_DEFAULT, 0, &_CKeySound);
	FMOD_System::ERRCHECK(_result);
}

Piano::~Piano()
{
}

void Piano::input(char c)
{
	int i = _octave - 12;

	if (c == 'z') {
		i += 0;
		Play(i);
	}
	else if (c == 's') {
		i += 1;
		Play(i);
	}
	else if (c == 'x') {
		i += 2;
		Play(i);
	}
	else if (c == 'd') {
		i += 3;
		Play(i);
	}
	else if (c == 'c') {
		i += 4;
		Play(i);
	}
	else if (c == 'v') {
		i += 5;
		Play(i);
	}
	else if (c == 'g') {
		i += 6;
		Play(i);
	}
	else if (c == 'b') {
		i += 7;
		Play(i);
	}
	else if (c == 'h') {
		i += 8;
		Play(i);
	}
	else if (c == 'n') {
		i += 9;
		Play(i);
	}
	else if (c == 'j') {
		i += 10;
		Play(i);
	}
	else if (c == 'm') {
		i += 11;
		Play(i);
	}
	else if (c == ',') {
		i += 12;
		Play(i);
	}
	else if (c == 'i')
		decreaseOctave();
	else if (c == 'o')
		increaseOctave();
}

void Piano::update()
{
	FMOD_System::getFMODSystem()->update();
}
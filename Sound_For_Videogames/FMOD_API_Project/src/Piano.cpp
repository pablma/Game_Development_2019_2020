#include "Piano.h"

Piano::Piano()
{
	_CKeySound = FMOD_Sound("piano.ogg");
}

Piano::~Piano()
{
}

void Piano::input(char c)
{
	if (c == 'z')
		_CKeySound.Play();
	else if (c == 'x')
		_CKeySound.Play();
	else if (c == 'c')
		_CKeySound.Play();
	else if (c == 'v')
		_CKeySound.Play();
	else if (c == 'b')
		_CKeySound.Play();
	else if (c == 'n')
		_CKeySound.Play();
	else if (c == 'm')
		_CKeySound.Play();
	else if (c == ',')
		_CKeySound.Play();

	_CKeySound.Play();
}

void Piano::update()
{
	FMOD_System::getFMODSystem()->update();
}
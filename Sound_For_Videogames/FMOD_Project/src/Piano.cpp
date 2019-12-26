#include "Piano.h"
#include <conio.h>
#include <math.h>


Piano::Piano(FMOD::System * system)
{
	_system = system;
	_result = _system->createSound("../res/piano.ogg", FMOD_DEFAULT, 0, &_pianoSound);
}

Piano::~Piano()
{
	_result = _pianoSound->release();
}

void Piano::update()
{
	int c = _getch();

	if (c != NULL)
	{
		
		_result = _system->playSound(_pianoSound, 0, false, &_channel);

		if (c == 'z')
			_channel->setPitch(powf(2, 0) / 12);
		else if (c == 'x')
			_channel->setPitch(powf(2, 2) / 12);
		else if (c == 'c')
			_channel->setPitch(powf(2, 4) / 12);
		else if (c == 'v')
			_channel->setPitch(powf(2, 5) / 12);
		else if (c == 'b')
			_channel->setPitch(powf(2, 7) / 12);
		else if (c == 'n')
			_channel->setPitch(powf(2, 9) / 12);
		else if (c == 'm')
			_channel->setPitch(powf(2, 11) / 12);
		else if (c == ',')
			_channel->setPitch(powf(2, 12) / 12);
		else if (c == 's')
			_channel->setPitch(powf(2, 1) / 12);
		else if (c == 'd')
			_channel->setPitch(powf(2, 3) / 12);
		else if (c == 'g')
			_channel->setPitch(powf(2, 6) / 12);
		else if (c == 'h')
			_channel->setPitch(powf(2, 8) / 12);
		else if (c == 'j')
			_channel->setPitch(powf(2, 10) / 12);

	}

	_system->update();
}
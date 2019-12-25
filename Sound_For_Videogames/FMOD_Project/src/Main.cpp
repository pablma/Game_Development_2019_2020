#include <conio.h>

#include "FmodSystem.h"
#include "FmodSound.h"
#include "Piano.h"


int main()
{
	// INITIALIZE FMOD
	FmodSystem::init();

	Piano piano = Piano(FmodSystem::getFmodSystem());

	while (true)
	{
		piano.update();
	}

	return 0;
}
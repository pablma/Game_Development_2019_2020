#include <fmod.hpp>			// para utilizar el wrapper de C++
#include <fmod_errors.h>	// para manejo de errores
#include <iostream>
#include <conio.h>

#include "FmodSound.h"
#include "Piano.h"


void init(FMOD::System* system, FMOD_RESULT result);
void ERRCHECK(FMOD_RESULT result);


int main()
{
	// INITIALIZE FMOD
	FMOD::System* system;
	FMOD_RESULT result;

	result = FMOD::System_Create(&system);	// Creamos objeto system
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializamos FMOD
	ERRCHECK(result);

	/*FmodSound pianoSound = FmodSound("piano", system);
	
	while (true)
	{
		int c = _getch();
		
		if (c == 'p')
			pianoSound.Play();
		else if (c == 's')
			pianoSound.Stop();
		else if (c == 'e')
			pianoSound.Pause();
		else if (c == 'r')
			pianoSound.Resume();
	}*/

	Piano piano = Piano(system);

	while (true)
	{
		piano.update();
	}

	return 0;
}


void init(FMOD::System* system, FMOD_RESULT result)
{
	result = FMOD::System_Create(&system);	// Creamos objeto system
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializamos FMOD
	ERRCHECK(result);
}


void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}
#include <fmod.hpp>			// para utilizar el wrapper de C++
#include <fmod_errors.h>	// para manejo de errores
#include <iostream>


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

	// LOAD SOUND
	FMOD::Sound* sound;
	char* soundPath = "../res/piano.ogg";
	result = system->createSound(soundPath, FMOD_DEFAULT, 0, &sound);

	// PLAY SOUND
	FMOD::Channel* channel;
	result = system->playSound(sound, 0, false, &channel);
	
	int n;
	std::cin >> n;

	return 1;
}


void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}
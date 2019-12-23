#include <fmod.hpp>			// para utilizar el wrapper de C++
#include <fmod_errors.h>	// para manejo de errores
#include <iostream>


void ERRCHECK(FMOD_RESULT result);


int main()
{
	FMOD::System* system;
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);	// Creamos objeto system
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializamos FMOD
	ERRCHECK(result);

	std::cout << "Everything was correctly initialised";

	return 1;
}


void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}
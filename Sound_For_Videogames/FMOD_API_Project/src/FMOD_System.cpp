#include "FMOD_System.h"

FMOD::System* FMOD_System::_system = nullptr;
FMOD_RESULT FMOD_System::_result;

void FMOD_System::init()
{
	_result = FMOD::System_Create(&_system);	// Creamos el objeto system
	ERRCHECK(_result);

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	_result = _system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializacion de FMOD
	ERRCHECK(_result);
}

void FMOD_System::update()
{
	_result = _system->update();
	ERRCHECK(_result);
}

void FMOD_System::release()
{
	_result = _system->release();
	ERRCHECK(_result);
}

void FMOD_System::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

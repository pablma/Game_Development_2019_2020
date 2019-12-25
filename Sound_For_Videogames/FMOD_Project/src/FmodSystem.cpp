#include "FmodSystem.h"

FMOD::System* FmodSystem::_system = nullptr;
FMOD_RESULT FmodSystem::_result;

void FmodSystem::init()
{
	_result = FMOD::System_Create(&_system);	// Creamos objeto system
	ERRCHECK(_result);

	_result = _system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializamos FMOD
	ERRCHECK(_result);
}

void FmodSystem::update()
{
	_system->update();
}

void FmodSystem::release()
{
	_result = _system->release();
	ERRCHECK(_result);
}

FMOD::System* FmodSystem::getFmodSystem()
{
	return _system;
}

void FmodSystem::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

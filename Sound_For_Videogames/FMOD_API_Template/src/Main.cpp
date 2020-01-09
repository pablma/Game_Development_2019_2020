#include <iostream>
#include <conio.h>
#include <fmod.hpp>
#include <fmod_errors.h>


// Atributos System
FMOD::System* _system;
FMOD_RESULT _result;

// Atributos Sonido
FMOD::Sound* _sound;
FMOD::Channel* _channel;


// Declaración de funciones
void initSystem();
void updateSystem();
void release();
void ERRCHECK(FMOD_RESULT result);

void clear();

int main()
{
	// Inicializaci�n FMOD 
	initSystem();


	// Creación sonido
	_result = _system->createSound("../res/footstep.wav", FMOD_3D | FMOD_LOOP_NORMAL, 0, &_sound);
	ERRCHECK(_result);

	// Creación channel
	_result = _system->playSound(_sound, 0, true, &_channel);
	ERRCHECK(_result);

	// Reproducimos sonido
	_result = _channel->setPaused(false);
	ERRCHECK(_result);

	// Bucle ppal
	char c;
	while (true)
	{
		if (_kbhit())
		{
			c = _getch();
			
			if (c == 'q')
				break;
		}
		updateSystem();
	}
	
	release();
	return 0;
}

void initSystem()
{
	_result = FMOD::System_Create(&_system);	// Creamos el objeto system
	ERRCHECK(_result);

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	_result = _system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializacion de FMOD
	ERRCHECK(_result);
}

void updateSystem()
{
	_result = _system->update();
	ERRCHECK(_result);
}

void release()
{
	_result = _sound->release();
	ERRCHECK(_result);

	_result = _system->release();
	ERRCHECK(_result);
}

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void clear()
{
	system("CLS");
}

#include "FmodSound.h"
#include <fmod.hpp>


FmodSound::FmodSound(char * filename)
{
	// LOAD SOUND
	FMOD::Sound* sound;
	char* soundPath = "../res/piano.ogg";
	//result = system->createSound(soundPath, FMOD_DEFAULT, 0, &sound);
}

FmodSound::~FmodSound()
{
}

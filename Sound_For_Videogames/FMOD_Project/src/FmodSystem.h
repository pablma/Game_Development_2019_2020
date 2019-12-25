#ifndef __FMODSYSTEM_H__
#define __FMODSYSTEM_H__

#include <fmod.hpp>			// para utilizar el wrapper de C++
#include <fmod_errors.h>	// para manejo de errores
#include <iostream>

class FmodSystem
{
private:
	static FMOD::System* _system;
	static FMOD_RESULT _result;
public:
	static void init();
	static void update();
	static void release();
	static FMOD::System* getFmodSystem();
	static void ERRCHECK(FMOD_RESULT result);
};

#endif
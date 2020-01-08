#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

class FMOD_System 
{
private:
	static FMOD::System* _system;
	static FMOD_RESULT _result;
public:
	static void init();
	static void update();
	static void release();
	static void ERRCHECK(FMOD_RESULT result);
	
	static FMOD::System* getFMODSystem() { return _system; };
};
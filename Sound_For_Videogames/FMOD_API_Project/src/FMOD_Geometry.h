#pragma once
#include "FMOD_System.h"

class FMOD_Geometry
{
private:
	FMOD::Geometry* _geometry = nullptr;

	FMOD_RESULT _result;
public:
	FMOD_Geometry();
	~FMOD_Geometry();

};
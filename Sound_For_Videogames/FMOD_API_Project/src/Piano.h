#pragma once
#include "FMOD_Sound.h"

class Piano
{
private:
	FMOD_Sound _CKeySound;
public:
	Piano();
	~Piano();

	void input(char c);
	void update();
};
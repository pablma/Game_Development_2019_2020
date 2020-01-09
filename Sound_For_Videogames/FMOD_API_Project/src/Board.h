#pragma once
#include <iostream>
#include "AudioListener.h"
#include "AudioSource.h"
#include "FMOD_Geometry.h"
#include "FMOD_Reverb.h"

class Board
{
private:
	int _rows = 20;
	int _cols = 34;

	AudioListener _listener;
	AudioSource _source;

	FMOD_Geometry _geometry;

	FMOD_Reverb _reverb1;
	FMOD_Reverb _reverb2;
public:
	Board();
	~Board();

	void input(char c);
	void update();
	void render();
	void clear();
};
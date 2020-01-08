#pragma once
#include <iostream>
#include "AudioListener.h"
#include "AudioSource.h"

class Board
{
private:
	int _rows = 20;
	int _cols = 34;

	AudioListener _listener;
	AudioSource _source;

public:
	Board();
	~Board();

	void input(char c);
	void update();
	void render();
	void clear();
};
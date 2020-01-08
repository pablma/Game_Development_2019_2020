#pragma once
#include <iostream>
#include "AudioListener.h"

class Board
{
private:
	int _rows = 20;
	int _cols = 34;

	AudioListener _listener;

	int _listenerX = 4;
	int _listenerY = 4;

	int _sourceX = 6;
	int _sourceY = 6;

public:
	Board();
	~Board();

	void input(char c);
	void update();
	void render();
	void clear();
};
#pragma once
#include <iostream>

class Board
{
private:
	int _rows = 20;
	int _cols = 34;

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
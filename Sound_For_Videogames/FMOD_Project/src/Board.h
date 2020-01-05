#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <fstream>
#include <string>
#include <fmod.hpp>
#include "AudioListener.h"
#include "AudioSource.h"
#include "FmodSystem.h"

class Board
{
private:
	int rows;
	int cols;
	char** _board = nullptr;

	void ReadFromTextFile(std::string filename);
	void CreateBoard(int rows, int cols);

	AudioListener _listener;
	AudioSource _source;
public:
	Board();
	~Board();

	void render();
	void clear();
	void Input(char c);
};

#endif
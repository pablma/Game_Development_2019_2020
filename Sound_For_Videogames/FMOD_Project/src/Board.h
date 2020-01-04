#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <fstream>
#include <string>

class Board
{
private:
	int rows;
	int cols;
	char** _board = nullptr;

	void ReadFromTextFile(std::string filename);
	void CreateBoard(int rows, int cols);

	int _listenerPos[2];
	int _sourcePos[2];
public:
	Board();
	~Board();

	void render();
	void clear();
	void Input(char c);
};

#endif
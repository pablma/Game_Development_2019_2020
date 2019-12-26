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
public:
	Board();
	~Board();

	void render();
	void clear();
};

#endif
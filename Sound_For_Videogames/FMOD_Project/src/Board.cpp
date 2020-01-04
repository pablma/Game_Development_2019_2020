#include "Board.h"
#include <stdlib.h>


Board::Board()
{
	ReadFromTextFile("../res/board.txt");
}


Board::~Board()
{
}

void Board::render()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			
			if (_board[i][j] == ' ')
				std::cout << ' ';
			else if (_board[i][j] == 'L')
			{
				std::cout << 'L';
				_listenerPos[0] = i;
				_listenerPos[1] = j;
			}				
			else if (_board[i][j] == 'S')
			{
				std::cout << 'S';
				_sourcePos[0] = i;
				_sourcePos[1] = j;
			}
			else if (_board[i][j] == '1')
				std::cout << '1';
			else if (_board[i][j] == '2')
				std::cout << '2';
			else if (_board[i][j] == '=')
				std::cout << '=';
			else
				std::cout << '.';
		}

		std::cout << std::endl;
	}
}

void Board::clear()
{
	system("CLS");
}

void Board::Input(char c)
{
	_board[_listenerPos[0]][_listenerPos[1]] = '.';
	_board[_sourcePos[0]][_sourcePos[1]] = '.';

	if (c == 'a')
		_listenerPos[1] = _listenerPos[1] - 2;
	else if (c == 'd')
		_listenerPos[1] = _listenerPos[1] + 2;
	else if (c == 'w')
		_listenerPos[0] = _listenerPos[0] - 1;
	else if (c == 's')
		_listenerPos[0] = _listenerPos[0] + 1;
	else if (c == 'j')
		_sourcePos[1] = _sourcePos[1] - 2;
	else if (c == 'l')
		_sourcePos[1] = _sourcePos[1] + 2;
	else if (c == 'i')
		_sourcePos[0] = _sourcePos[0] - 1;
	else if (c == 'k')
		_sourcePos[0] = _sourcePos[0] + 1;

	_board[_listenerPos[0]][_listenerPos[1]] = 'L';
	_board[_sourcePos[0]][_sourcePos[1]] = 'S';

	clear();
	render();
}


void Board::ReadFromTextFile(std::string filename)
{
	std::string line;
	std::ifstream file(filename);

	if (file.is_open())
	{
		std::getline(file, line);
		rows = stoi(line);
		std::getline(file, line);
		cols = stoi(line);
		
		CreateBoard(rows, cols);

		for (int i = 0; i < rows; i++)
		{
			std::getline(file, line);
			for (int j = 0; j < cols; j++)			
				_board[i][j] = line[j];			
		}

		file.close();
	}
	else
		std::cout << "Unable to open file";
}

void Board::CreateBoard(int rows, int cols)
{
	_board = new char*[rows];
	
	for (int i = 0; i < rows; i++)
		_board[i] = new char[cols];
}

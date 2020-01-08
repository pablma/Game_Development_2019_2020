#include "Board.h"

Board::Board()
{

}

Board::~Board()
{
}

void Board::input(char c)
{
	if (c == 'a')
		_listenerX -= 1;
	else if (c == 'd')
		_listenerX += 1;
	else if (c == 'w')
		_listenerY -= 1;
	else if (c == 's')
		_listenerY += 1;
	else if (c == 'j')
		_sourceX -= 1;
	else if (c == 'l')
		_sourceX += 1;
	else if (c == 'i')
		_sourceY -= 1;
	else if (c == 'k')
		_sourceY += 1;
}

void Board::update()
{
}

void Board::render()
{
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			if (_listenerX == j && _listenerY == i)
				std::cout << "L ";
			else if (_sourceX == j && _sourceY == i)
				std::cout << "S ";
			else
				std::cout << ". ";
		}
		std::cout << "\n";
	}
}

void Board::clear()
{
	system("CLS");
}

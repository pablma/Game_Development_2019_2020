#include "Board.h"
#include <stdlib.h>


Board::Board()
{
	_listener = AudioListener(FmodSystem::getFmodSystem(), { 0, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0, 0 });
	_source = AudioSource("../res/Robert Miles - Children.ogg", FmodSystem::getFmodSystem(), { 1, 0, 0 }, { 0, 0, 0 });
	_source.Play();
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
				_listener.setPosition({(float)i , (float)j, 0});
			}				
			else if (_board[i][j] == 'S')
			{
				std::cout << 'S';
				_source.setPosition({ (float)i, (float)j, 0 });
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
	_board[(int)_listener.getPosition().x][(int)_listener.getPosition().y] = '.';
	_board[(int)_source.getPosition().x][(int)_source.getPosition().y] = '.';

	if (c == 'a')
		_listener.setPosition({ _listener.getPosition().x, _listener.getPosition().y - 2, 0 });
	else if (c == 'd')
		_listener.setPosition({ _listener.getPosition().x, _listener.getPosition().y + 2, 0 });
	else if (c == 'w')
		_listener.setPosition({ _listener.getPosition().x - 1, _listener.getPosition().y, 0 });
	else if (c == 's')
		_listener.setPosition({ _listener.getPosition().x + 1, _listener.getPosition().y, 0 });
	else if (c == 'j')
		_source.setPosition({ _source.getPosition().x, _source.getPosition().y - 2, 0});
	else if (c == 'l')
		_source.setPosition({ _source.getPosition().x, _source.getPosition().y + 2, 0 });
	else if (c == 'i')
		_source.setPosition({ _source.getPosition().x - 1, _source.getPosition().y, 0 });
	else if (c == 'k')
		_source.setPosition({ _source.getPosition().x + 1, _source.getPosition().y, 0 });

	_board[(int)_listener.getPosition().x][(int)_listener.getPosition().y] = 'L';
	_board[(int)_source.getPosition().x][(int)_source.getPosition().y] = 'S';

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

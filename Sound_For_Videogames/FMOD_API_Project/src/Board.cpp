#include "Board.h"

Board::Board()
{
	_listener = AudioListener({ 4, 4, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, {0, 0, -1});
	_source = AudioSource({ 14, 15, 0 }, { 0, 0, 0 }, {1, 0, 0});
}

Board::~Board()
{
}

void Board::input(char c)
{
	if (c == 'a')
		_listener.setPosition({ _listener.getPosition().x - 1,  _listener.getPosition().y, 0 });
	else if (c == 'd')
		_listener.setPosition({ _listener.getPosition().x + 1,  _listener.getPosition().y, 0 });
	else if (c == 'w')
		_listener.setPosition({ _listener.getPosition().x,  _listener.getPosition().y - 1, 0 });
	else if (c == 's')
		_listener.setPosition({ _listener.getPosition().x,  _listener.getPosition().y + 1, 0 });
	else if (c == 'j')
		_source.setPosition({ _source.getPosition().x - 1,  _source.getPosition().y, 0 });
	else if (c == 'l')
		_source.setPosition({ _source.getPosition().x + 1,  _source.getPosition().y, 0 });
	else if (c == 'i')
		_source.setPosition({ _source.getPosition().x,  _source.getPosition().y - 1, 0 });
	else if (c == 'k')
		_source.setPosition({ _source.getPosition().x,  _source.getPosition().y + 1, 0 });
	else if (c == 'z')
		_source.increaseInternalConeAngle(1);
	else if (c == 'x')
		_source.decreaseInternalConeAngle(1);
	else if (c == 'c')
		_source.increaseExternalConeAngle(1);
	else if (c == 'v')
		_source.decreaseExternalConeAngle(1);
	else if (c == 'q')
		_source.increaseMinDistance(0.5);
	else if (c == 'e')
		_source.decreaseMinDistance(0.5);
	else if (c == 'r')
		_source.increaseMaxDistance(0.5);
	else if (c == 't')
		_source.decreaseMaxDistance(0.5);

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
			if (_listener.getPosition().x == j && _listener.getPosition().y == i)
				std::cout << "L ";
			else if (_source.getPosition().x == j && _source.getPosition().y == i)
				std::cout << "S ";
			else if (i == 10 && j > 7 && j < 25)
				std::cout << "==";	
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

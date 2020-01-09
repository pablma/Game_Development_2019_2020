#include "Board.h"

Board::Board()
{
	_listener = AudioListener({ 4, 4, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, {0, 0, 1});
	_source = AudioSource({ 14, 15, 0 }, { 0, 0, 0 }, {0, -1, 0});
	_geometry.init();
	
	//FMOD::Reverb3D* reverb1;
	//FMOD_System::getFMODSystem()->createReverb3D(&reverb1);
	//FMOD_REVERB_PROPERTIES prop1 = FMOD_PRESET_CONCERTHALL;
	//reverb1->setProperties(&prop1);
	//FMOD_VECTOR pos1_ = { 0, 0, 0 };
	//float mindist = 10, maxdist = 20;
	//reverb1->set3DAttributes(&pos1_, mindist, maxdist);

	//FMOD::Reverb3D* reverb2;
	//FMOD_System::getFMODSystem()->createReverb3D(&reverb2);
	//FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_BATHROOM;
	//reverb2->setProperties(&prop2);
	//FMOD_VECTOR pos2_ = { 12, 13, 0 };
	//reverb2->set3DAttributes(&pos2_, mindist, maxdist);

	_reverb1 = FMOD_Reverb({0, 0, 0}, 10.0f, 20.0f, FMOD_PRESET_BATHROOM);
	//_reverb2 = FMOD_Reverb({ 12, 13, 0 }, 10.0f, 20.0f, FMOD_PRESET_CITY);
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
			else if (_reverb1.getPosition().x == j && _reverb1.getPosition().y == i)
				std::cout << "1 ";
			else if (_reverb2.getPosition().x == j && _reverb2.getPosition().y == i)
				std::cout << "2 ";
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

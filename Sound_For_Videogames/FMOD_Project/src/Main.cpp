#include <conio.h>

#include "FmodSystem.h"
#include "FmodSound.h"
#include "Piano.h"
#include "Board.h"
#include "AudioListener.h"
#include "AudioSource.h"


int main()
{
	// INITIALIZE FMOD
	FmodSystem::init();

	//Piano piano = Piano(FmodSystem::getFmodSystem());
	//FmodSound sound = FmodSound("piano.ogg", FmodSystem::getFmodSystem());

	//while (true)
	//{
	//	//piano.update();

	//	int c = _getch();

	//	if (c != NULL)
	//	{
	//		sound.Play();
	//		if (c == 'v')
	//			sound.FadeOut(1);
	//	}
	//}

	Board board = Board();
	board.render();

	AudioSource _source = AudioSource("../res/Robert Miles - Children.ogg", FmodSystem::getFmodSystem(), { 1, 0, 0 }, { 0, 0, 0 });
	_source.Play();
	

	AudioListener _listener = AudioListener(FmodSystem::getFmodSystem(), { 100, 0, 0 }, { 0, 0, 0 }, {0, 1, 0}, {1, 0, 0});


	while (true)
	{		
		board.Input(_getch());
	}


	system("pause");
	return 0;
}
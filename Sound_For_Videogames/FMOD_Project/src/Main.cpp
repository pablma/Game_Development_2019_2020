#include <conio.h>

#include "FmodSystem.h"
#include "FmodSound.h"
#include "Piano.h"
#include "Board.h"


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

	while (true)
	{
		board.clear();
		board.render();
	}


	system("pause");
	return 0;
}
#include <conio.h>
#include "Piano.h"
#include "Board.h"

int main()
{
	// Inicialización FMOD
	FMOD_System::init();
	
	// Ejericio 1
	/*FMOD_Sound sound = FMOD_Sound("music.ogg");

	sound.Play();
	sound.FadeOut(5000);

	while (true)
	{
		sound.Tick();			
	}*/
	
	// Ejercicio Piano
	//Piano piano = Piano();

	//while (true)
	//{
	//	piano.input(_getch());
	//	piano.update();
	//}

	Board board = Board();
	
	board.clear();
	board.render();

	while (true)
	{
		if (_kbhit())
		{
			board.input(_getch());
			board.clear();
			board.render();
		}
	}

	return 0;
}
#include <conio.h>
#include "Piano.h"

int main()
{
	FMOD_System::init();
	FMOD_Sound sound = FMOD_Sound("music.ogg");

	sound.Play();
	sound.FadeOut(5000);

	while (true)
	{
		sound.Tick();			
	}
	
	
	//Piano piano = Piano();

	//while (true)
	//{
	//	piano.input(_getch());
	//	piano.update();
	//}

	system("pause");
	return 0;
}
#include <conio.h>
#include "FMOD_Sound.h"

int main()
{
	// Inicializaci�n FMOD 
	FMOD_System::init();

	// ----------- FMOD 2D -----------
	FMOD_Sound sound = FMOD_Sound("music.ogg");

	sound.Play();
	
	system("pause");
	return 0;
}
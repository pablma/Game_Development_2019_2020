#ifndef __PIANO_H__
#define __PIANO_H__

#include <fmod.hpp>

class Piano
{
private:
	FMOD::System* _system;
	FMOD_RESULT _result;

	FMOD::Sound* _pianoSound;
	FMOD::Channel* _channel;

	char* _soundPath;
public:
	Piano(FMOD::System* system);
	~Piano();

	void update();

};

#endif // __PIANO_H__

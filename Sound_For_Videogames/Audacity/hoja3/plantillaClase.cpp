#include <stdlib.h> // para el exit
#include <stdio.h>
#include <iostream> // para min y max

#include "/usr/include/AL/al.h"
#include "/usr/include/AL/alut.h"
#include "/usr/include/AL/alc.h"

using namespace std;

int main(int argc, char *argv[]) {

  // INICIALIZACIÓN DE AUDIO
  alutInit(NULL, 0);
  alutGetError(); 

  // CARGA DE BUFFER
  ALuint buffer=alutCreateBufferFromFile("...");
  if(alGetError() != AL_NO_ERROR) exit(-1);


  // Generamos 2 sources (mono) para control independiente
  ALuint left, right;
  alGenSources(1, &left);
  alGenSources(1, &right);
  if(alGetError() != AL_NO_ERROR) exit(-1);

  // ASOCIAMOS EL MISMO BUFFER A AMBOS SOURCES
  alSourcei (left,  AL_BUFFER,  buffer );
  alSourcei (right, AL_BUFFER,  buffer );

  // UN SOURCE A LA IZDA Y OTRO A LA DERECHA
  ALfloat posL[] = { -1.0, 0.0, 0.0 },   // izda
          posR[] = {  1.0, 0.0, 0.0 };   // dcha
  alSourcefv(left,  AL_POSITION, posL);
  alSourcefv(right, AL_POSITION, posR);


  // INICIALIZACIÓN DE GANANCIAS DE CADA SOURCE
  ALfloat gainL = 0.5f, gainR = 0.5f;
  alSourcef (left,  AL_GAIN, gainL );
  alSourcef (right, AL_GAIN, gainR );
  if(alGetError() != AL_NO_ERROR) exit(-1);

  // REPRODUCCIÓN EN LOOP DE AMBOS SOURCES
  alSourcei (left,  AL_LOOPING,  1 );
  alSourcei (right, AL_LOOPING,  1 );


  // ARRANCAMOS AMBOS SOURCES
  alSourcePlay(left);
  alSourcePlay(right);

  // Loop para JUGAR CON LA GANANCIA DE SOURCES
  
  while (...) {
    // modificar la ganancia de los canales izdo y derecho, gainL, gainR
    // ...

    alSourcef (left,  AL_GAIN, gainL);
    alSourcef (right, AL_GAIN, gainR);
    
  }
  // eliminamos buffers y sources
  alutExit();
}

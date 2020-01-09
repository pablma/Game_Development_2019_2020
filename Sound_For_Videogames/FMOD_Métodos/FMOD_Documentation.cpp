// INCLUDES
#include "fmod.hpp" // para utilizar el wrapper C++
#include "fmod_errors.h" // para manejo de errores

// SYSTEM

//---------- Creación e inicialización ----------
System *_system;
FMOD_RESULT _result;

_result = FMOD::System_Create(&_system);	// Creamos el objeto system
ERRCHECK(_result);

// 128 canales (numero maximo que podremos utilizar simultaneamente)
_result = _system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializacion de FMOD
ERRCHECK(_result);

//---------- Update ----------
_result = _system->update();
ERRCHECK(_result);

//---------- Release ----------
_result = _system->release();
ERRCHECK(_result);

//--------- ERRCHECK ---------
if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}

// SOUNDS
//--------- Carga de sonidos ---------
Sound *sound1;
result = system->createSound(
"Battle.wav", // path al archivo de sonido
FMOD_DEFAULT, // valores (por defecto en este caso: sin loop, 2D)
0, // informacion adicional (nada en este caso)
&sound1); // handle al buffer de sonido

//--------- Asignación a canal y reproducción de sonidos ---------
Channel *channel;
result = system->playSound(
sound, // buffer que se "engancha" a ese canal
0 // grupo de canales, 0 sin agrupar (agrupado en el master)
false, // arranca sin "pause" (se reproduce directamente)
&channel); // devuelve el canal que asigna
// el sonido ya se esta reproduciendo

// --------- Información útil ---------
La variable channel permite modificar los parámetros de ese canal:
result = channel->setVolume(0.7f);

Para hacerlo efectivo,EN CADA VUELTA DEL BUCLE PPAL.:
result = system->update();

// --------- Información Loops ---------
system->createSound(..., FMOD_DEFAULT,...)
Esto significa que lo cargamos con la primera de las siguientes alternativas:
FMOD_LOOP_OFF, FMOD_LOOP_NORMAL, FMOD_LOOP_BIDI: sin o con loop.
FMOD_2D y FMOD_3D: posicionamiento 2D o 3D
FMOD_3D_INVERSEROLLOFF, FMOD_3D_LINEARROLLOFF,
FMOD_3D_CUSTOMROLLOF, etc

FMOD_DEFAULT: sonido 2D, sin loop

// --------- Información Channel ---------
Channel *channel;
result = system->playSound(
sound, // buffer que se "engancha" a ese canal
0 // grupo de canales, 0 sin agrupar (agrupado en el master)
false, // arranca sin "pause" (se reproduce directamente)
&channel); // devuelve el canal que asigna

“0” indica el grupo de canales (en este caso sin agrupar) FMOD
permite el agrupamiento de canales (ChannelGroup) en un canal
Virtual: permite modificar parámetros de todo el grupo de
manera conjunta.
Arrancar el sonido con pause lo deja disponible en memoria para:
modificar parámetros antes de la reproducción.
evitar latencias (por ejemplo, para sincronizar pistas).

Puede pausarse la reproducción (sin liberar el canal) con
channel->setPaused(true)
y reiniciarse con channel->setPaused(false)
También hay un método channel->getPaused(&paused)

// --------- Toggle Paused ---------
void TogglePaused(FMOD::Channel* channel) {
bool paused;
channel->getPaused(&paused);
channel->setPaused(!paused);
}

// --------- Más Información Channel ---------
Es posible comenzar la reproducción de un canal en un instante de
tiempo (o sample) dado:
channel->setPosition(500, FMOD_TIMEUNIT_MS);
Comienza medio segundo después del instante inicial (también pueden
utilzarse samples PCM, bytes, etc).

También podemos definir de antemano el número de repeticiones de
un sonido en loop:
// se repite indefinidamente
channel->setLoop(-1)
// Se repite una sola vez
channel->setLoopCount(0);
// Tres veces
channel->setLoopCount(2);

// --------- Formato de los Buffers ---------
Los sonidos pueden cargarse de tres modos en los buffers:
Samples: se cargan las muestras (PCM) en memoria tal cual. Útil para
los efectos de sonido que utilizan poca memoria.
Streams: muestras grandes que ocuparían mucha memoria. Se cargan
un buffer circular (como hacíamos en OpenAL). Los streams se
reproducen de manera secuencial: no se puede hacer reproducción
múltiple (simultáneo) del sonido de un stream. Útiles para música,
pistas de voz, sonidos de ambiente, etc.
Samples comprimidos (mp3, vorbis, etc): se dejan comprimidos en
memoria. No tienen las limitaciones de los streams, ocupan menos en
memoria, pero hay que descomprimir en tiempo real!
Por defecto, System::createSound los carga como samples (sin
compresión).
Pueden cargarse como streams con System::createStream (o con
System::createSound y el valor FMOD_CREATESTREAM). Se puede hacer
streaming incluso desde sonidos de internet.
Pueden cargarse como samples comprimidos con
System::createSound y el valor FMOD_CREATECOMPRESSEDSAMPLE

// --------- Modificando el channel en tiempo real ---------
Volumen: channel->setVolume(val);
val (float) en el intervalo [0,1] (silencio, volumen normal).
Silencio: channel->setMute(true); y channel->setMute(false);
Silencia el canal. Cuando se reactiva conserva el volumen que tuviese
previamente.
Modificación del volumen en sonidos multicanal. Por ejemplo, en para
un sonido estéreo:

channel->setMixLevelsOutput(frontleft,frontright,center,...,backleft,backright);
Modificación del pitch: channel->setPicth(2.0f);
También existe channel->setFrequency(rateHz); (frecuencia de
reproducción en Hz.)

// --------- Panorama ---------
Para sonidos en 2D, tanto en mono como en estéreo manejo de panorama
con:
channel->setPan(-1.0f);
-1.0 a la izquierda; 0 centrado (por defecto); 1 a la derecha

// GRUPOS DE CANALES

// --------- Agrupando canales ---------
// creamos un grupo de canales ``channelGroup''
FMOD::ChannelGroup* channelGroup;
system->createChannelGroup("grupo1", &channelGroup);
// aniadimos un canal existente, channel, al grupo
channel->setChannelGroup(channelGroup);
// se puede anidir un canal a un grupo directamente con
// playSound(...,group,...,...) mas eficiente!
// aniadimos este grupo como hijo de otro grupo ``anotherGroup''
channelGroup->addGroup(anotherGroup);
// hay un ``master'' (raiz del arbol de grupos) que se puede acceder asi:
ChannelGroup* masterGroup;
system->getMasterChannelGroup(&masterGroup);

// --------- Manejando grupos de canales ---------
// Parar todos los canales del grupo
channelGroup->stop();
// Silenciar, pausar
channelGroup->setMute(true);
channelGroup->setPaused(true);
// ajustar volumen
channelGroup->setVolume(0.5f);
// duplicar pitch
channelGroup->setPitch(2.0f);

Todos estos cambios se propagan en la jerarquía hacia abajo (en el árbol de
grupos y canales), sin sobreescribir los valores de cada canal individual.
La aplicación de parámetros sigue distintas políticas:
Mute, pause: el valor (negativo) del grupo prevalece sobre el de los
hijos. Si el padre está en pausa, los hijos también; pero si el canal no
está pausado, se considera el valor de los hijos.
Volumen, pitch: los valores del grupo se multiplican por los de los
hijos. Por ejemplo, un canal con volumen 0.8 en un grupo con volumen
0.5 sonará a volumen 0.4

// SONIDO 3D

// LISTENER

// --------- Colocando el Listener ---------
FMOD_VECTOR
listenerPos = {0,0,0}, // posicion del listener
listenerVel = {0,0,0}, // velocidad del listener
up = {0,1,0}, // vector up: hacia la ``coronilla''
at = {1,0,0}; // vector at: hacia donde mira
// colocamos listener
system->set3DListenerAttributes(0, &listenerPos, &listenerVel, &up, &at);

El primer parámetro indica el listener (FMOD puede trabajar con
varios p.e. en juegos con pantalla partida). Se pueden crear con
set3DNumListeners

Para que FMOD pueda operar en 3D, la carga de sonido ya debe
indicarlo:

Sound *sound;
ERRCHECK(
system-createSound(
"siren08.wav", // arhivo de sonido
FMOD 3D | FMOD LOOP NORMAL, // para REPRODUCIR en 3D y en loop
0,
&sound1));

// SOURCE

// --------- Creando sonidos ---------
Channel *canalSirena;
ERRCHECK(
system->playSound(
sound, // sonido
0 // grupo (master)
true, // arrancamos en pause
&canalSirena)); // handle al canal

Creamos canal y arrancamos en pause:
// situamos canal en 3D
FMOD_VECTOR
pos={19,0,0}, // posicion
vel={0,0,0}; // velocidad
canalSirena->set3DAttributes(&pos, &vel);
// por que pasan por referencia? ...

// CONOS
// --------- Creando Conos ---------
FMOD_VECTOR dir = { 1.0f, 2.0f, 3.0f }; // vector de direccion de los conos
channel->set3DConeOrientation(&dir);
channel->set3DConeSettings(30.0f, 60.0f, 0.5f); // angulos en grados

Los ángulos corresponden a:
insideconeangle: ángulo del cono interior, donde no hay
atenuación por la dirección (por defecto 360º)
outsideconeangle: ángulo del cono exterior, donde el sonido se
atenúa. La atenuación se calcula por interpolación (por defecto
360º)
outsidevolume: volumen fuera del cono exterior (por defecto 1.0)

// ATENUACIÓN
// --------- Definiendo distancia de atenuación ---------
float minDistance = 1.0f, maxDistance = 10000.0f;
channel->set3DMinMaxDistance(minDistance, maxDistance);

minDistance: distancia a partir de la cual el sonido comienza a
atenuarse
maxDistance: distancia a partir de la cual el sonido no se atenúa más
(el volumen no es necesariamente 0.0)


// REVERB
// --------- Creando una Reverb ---------
Reverb3D *reverb;
result = system->createReverb3D(&reverb);
FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
reverb->setProperties(&prop2);
FMOD_VECTOR pos = { -10.0f, 0.0f, 0.0f };
float mindist = 10.0f, maxdist = 20.0f;
reverb->set3DAttributes(&pos, mindist, maxdist);

Las reverb pueden activarse o desactivarse con reverb->setActive(false)

// GEOMETRÍAS
// --------- Creando una Geometría ---------
FMOD::Geometry* geometry;
system->createGeometry(maxPoligons, maxVertices, &geometry);

// --------- Ubicando la Geometría ---------
int polygonIndex; // Indice al poligono para referenciarlo despues
geometry->addPolygon(
float directocclusion, // 0.0 no atenua, 1.0 atenua totalmente
float reverbOcclusion, // atenuacion de la reverberacion
bool doubleSided, // atenua por ambos lados o no
int numVertices, // numero de vertices (>=3)
const FMOD_VECTOR *vertices, // vector de numVertices vertices
int *polygonindex); // indice del poligono generado

Todos los vértices deben estar en el mismo plano.
Tienen que ir ordenados en sentido antihorario
Los polígonos deben ser convexos y con área positiva.
Posición de los vértices relativa a la posición (o centro) del objeto, utilizada en
setPosition:
setPosition(FMOD_VECTOR pos): sitúa el objeto geometry en pos, relativa al
espacio del listener y los canales.
setRotation(FMOD_VECTOR *forward, FMOD_VECTOR *up): orientación del
objeto
setScale(FMOD_VECTOR scale): escala relativa de geometry en las 3
dimensiones por separado

// --------- Ejemplo Geometría ---------
// Ficero.h
	FMOD::Geometry* _geometry = nullptr;

	int _polygonIndex;
	float _directOcclusion = 1.0f;
	float _reverbOcclusion;
	const int _numVertices = 4;
	bool _doubleSided = true;
	FMOD_VECTOR _vertices[4];

	FMOD_VECTOR _vA = {24, 10, -1};
	FMOD_VECTOR _vB = {24, 10, 1};
	FMOD_VECTOR _vC = {8, 10, 1};
	FMOD_VECTOR _vD = {8, 10, -1};

	FMOD_RESULT _result;
	
// Fichero.cpp
	void FMOD_Geometry::init()
{
	_result = FMOD_System::getFMODSystem()->createGeometry(4, 4, &_geometry);
	FMOD_System::ERRCHECK(_result);

	_vertices[0] = _vA;
	_vertices[1] = _vB;
	_vertices[2] = _vC;
	_vertices[3] = _vD;


	_geometry->addPolygon(_directOcclusion, _reverbOcclusion, _doubleSided, _numVertices, _vertices, &_polygonIndex);
}

// BANCOS DE SONIDO

// --------- Cargando la SoundBank ---------
// No olvidar incluir #include <fmod_studio.hpp>
// Meter el evento en el Master Bank
// En la pestaña Events poner el evento sin carpetas ni nada

FMOD::Studio::System* system = NULL;
	FMOD::Studio::System::create(&system);

	// The example Studio project is authored for 5.1 sound, so set up the system output mode to match
	FMOD::System* coreSystem = NULL;
	system->getCoreSystem(&coreSystem);
	coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

	FMOD::Studio::Bank* masterBank = NULL;
	system->loadBankFile("../res/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

	FMOD::Studio::Bank* stringsBank = NULL;
	system->loadBankFile("../res/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);

	// Get the Looping Ambience event
	FMOD::Studio::EventDescription* pasos = NULL;
	_result = system->getEvent("event:/Pasos", &pasos);
	ERRCHECK(_result);

	FMOD::Studio::EventInstance* pasosInstance = NULL;
	pasos->createInstance(&pasosInstance);

	pasosInstance->start();

	pasosInstance->setParameterByName("Velocidad", 0.5);

	do
	{
		system->update();
	} while (true);

	stringsBank->unload();
	masterBank->unload();

	system->release();

	return 0;
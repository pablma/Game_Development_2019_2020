#include <iostream>
#include <conio.h>
#include <fmod.hpp>
#include <fmod_errors.h>

// Atributos System
FMOD::System* _system;
FMOD_RESULT _result;


// Atributos Listener
FMOD_VECTOR _listenerPos = { 0, 0, -1 };
FMOD_VECTOR _listenerVel = { 0, 0, 0 };
FMOD_VECTOR _listenerUp = { 0, 1, 0 };
FMOD_VECTOR _listenerAt = { 0, 0, 1 };


// Atributos AudioSource
FMOD::Sound* _sourceSound;
FMOD::Channel* _sourceChannel;
FMOD_VECTOR _sourcePos = { 0, 0, 4 };
FMOD_VECTOR _sourceVel = { 0, 0, 0 };
float _sourcePitch = 1.0f;


// Atributos Reverb
FMOD::Reverb3D* _reverb;
FMOD_REVERB_PROPERTIES _reverbProperties = FMOD_PRESET_BATHROOM;
FMOD_VECTOR _reverbPos = { 2, 0, 6 };
float _reverbMinDist = 1.0f;
float _reverbMaxDist = 10.0f;
bool _reverbActive = true;

// Atributos Geometría
FMOD::Geometry* _geometry;
int _polygonIndex;
float _directOcclusion = 1.0f;
float _reverbOcclusion;
const int _numVertices = 4;
bool _doubleSided = true;
bool _geometryActive = true;

FMOD_VECTOR _vertices[4];
FMOD_VECTOR _vA = { 200, 1, 0 };
FMOD_VECTOR _vB = { -200, 1, 0 };
FMOD_VECTOR _vC = { -200, -1, 0 };
FMOD_VECTOR _vD = { 200, -1, 0 };


// Declaración de Funciones
void SetListenerPos(FMOD_VECTOR pos); 
void IncreaseSourcePitch(float increase);
void DecreaseSourcePitch(float decrease);

void initSystem();
void updateSystem();
void release();
void ERRCHECK(FMOD_RESULT result);

void ShowDebug();
void clear();

int main()
{
	// Inicialización FMOD 
	initSystem();
	
	// Colocación Listener
	_result = _system->set3DListenerAttributes(0, &_listenerPos, &_listenerVel, &_listenerAt, &_listenerUp);
	ERRCHECK(_result);
	

	// Colocación AudioSource
	_result = _system->createSound("../res/footstep.wav", FMOD_3D | FMOD_LOOP_NORMAL,	0, &_sourceSound);
	ERRCHECK(_result);

	_result = _system->playSound(_sourceSound, 0, true, &_sourceChannel);
	ERRCHECK(_result);

	_result = _sourceChannel->set3DAttributes(&_sourcePos, &_sourceVel);
	ERRCHECK(_result);

	_result = _sourceChannel->setPaused(false);
	ERRCHECK(_result);


	// Colocación Reverb
	_result = _system->createReverb3D(&_reverb);
	ERRCHECK(_result);

	_result = _reverb->setProperties(&_reverbProperties);
	ERRCHECK(_result);

	_result = _reverb->set3DAttributes(&_reverbPos, _reverbMinDist, _reverbMaxDist);
	ERRCHECK(_result);


	// Colocación Geometría
	_result = _system->createGeometry(4, 4, &_geometry);
	ERRCHECK(_result);

	_vertices[0] = _vA;
	_vertices[1] = _vB;
	_vertices[2] = _vC;
	_vertices[3] = _vD;

	_result = _geometry->addPolygon(_directOcclusion, _reverbOcclusion, _doubleSided, _numVertices, _vertices, &_polygonIndex);
	ERRCHECK(_result);


	// Debug Inicial
	ShowDebug();


	// Bucle ppal
	char c;
	while (true)
	{
		if (_kbhit()) {
			c = _getch();

			if (c == 'q')
				break;
			else if (c == 'a')
				SetListenerPos({ _listenerPos.x -= 0.1f, _listenerPos.y, _listenerPos.z });
			else if (c == 'd')
				SetListenerPos({ _listenerPos.x += 0.1f, _listenerPos.y, _listenerPos.z });
			else if (c == 'w')
				SetListenerPos({ _listenerPos.x, _listenerPos.y, _listenerPos.z += 0.1f });
			else if (c == 's')
				SetListenerPos({ _listenerPos.x, _listenerPos.y, _listenerPos.z -= 0.1f });
			else if (c == 'P')
				IncreaseSourcePitch(0.01f);
			else if (c == 'p')
				DecreaseSourcePitch(0.01f);
			else if (c == 'R') {
				_result = _reverb->setActive(true);
				ERRCHECK(_result);

				_reverbActive = true;
			}
			else if (c == 'r') {
				_result = _reverb->setActive(false);
				ERRCHECK(_result);

				_reverbActive = false;
			}
			else if (c == 'O') {
				_result = _geometry->setActive(true);
				ERRCHECK(_result);

				_geometryActive = true;
			}
			else if (c == 'o') {
				_result = _geometry->setActive(false);
				ERRCHECK(_result);

				_geometryActive = false;
			}

			// Debug
			clear();
			ShowDebug();
			
		}
		updateSystem();
	}
	
	release();
	return 0;
}

void SetListenerPos(FMOD_VECTOR pos) {
	_listenerPos = pos;

	_result = _system->set3DListenerAttributes(0, &_listenerPos, &_listenerVel, &_listenerAt, &_listenerUp);
	ERRCHECK(_result);
}

void IncreaseSourcePitch(float increase)
{
	_sourcePitch += increase;

	_result = _sourceChannel->setPitch(_sourcePitch);
	ERRCHECK(_result);
}

void DecreaseSourcePitch(float decrease)
{
	_sourcePitch -= decrease;

	_result = _sourceChannel->setPitch(_sourcePitch);
	ERRCHECK(_result);
}

void initSystem()
{
	_result = FMOD::System_Create(&_system);	// Creamos el objeto system
	ERRCHECK(_result);

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	_result = _system->init(128, FMOD_INIT_NORMAL, 0);	// Inicializacion de FMOD
	ERRCHECK(_result);
}

void updateSystem()
{
	_result = _system->update();
	ERRCHECK(_result);
}

void release()
{
	_result = _geometry->release();
	ERRCHECK(_result);

	_result = _reverb->release();
	ERRCHECK(_result);

	_result = _sourceSound->release();
	ERRCHECK(_result);

	_result = _system->release();
	ERRCHECK(_result);
}

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		std::cout << FMOD_ErrorString(result) << std::endl;
		// printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void ShowDebug()
{
	std::cout << "Listener Position: " << "(" << _listenerPos.x << ", " << _listenerPos.y << ", " << _listenerPos.z << ")\n";
	std::cout << "Source Position: " << "(" << _sourcePos.x << ", " << _sourcePos.y << ", " << _sourcePos.z << ")\n";
	std::cout << "Source Pitch: " << _sourcePitch << "\n";
	std::cout << "Reverb Active: " << _reverbActive << "\n";
	std::cout << "Occlusion Active: " << _geometryActive << "\n";
}

void clear()
{
	system("CLS");
}

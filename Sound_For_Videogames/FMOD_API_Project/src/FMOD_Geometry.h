#pragma once
#include "FMOD_System.h"

class FMOD_Geometry
{
private:
	FMOD::Geometry* _geometry = nullptr;

	int _polygonIndex;
	float _directOcclusion = 1f;
	float _reverbOcclusion;
	const int _numVertices = 4;
	bool _doubleSided = true;
	FMOD_VECTOR _vertices[4];

	FMOD_VECTOR _vA = {24, 10, -1};
	FMOD_VECTOR _vB = {24, 10, 1};
	FMOD_VECTOR _vC = {8, 10, 1};
	FMOD_VECTOR _vD = {8, 10, -1};

	FMOD_RESULT _result;
public:
	FMOD_Geometry();
	void init();
	~FMOD_Geometry();
};
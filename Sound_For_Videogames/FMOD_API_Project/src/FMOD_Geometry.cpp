#include "FMOD_Geometry.h"

FMOD_Geometry::FMOD_Geometry()
{
	_result = FMOD_System::getFMODSystem()->createGeometry(4, 4, &_geometry);
	FMOD_System::ERRCHECK(_result);
}

FMOD_Geometry::~FMOD_Geometry()
{
}
#include "FMOD_Geometry.h"

FMOD_Geometry::FMOD_Geometry()
{

}

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

FMOD_Geometry::~FMOD_Geometry()
{
}
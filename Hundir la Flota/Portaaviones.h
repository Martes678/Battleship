#pragma once
#include "Barco.h"
class Portaaviones : public Barco{
public:
	Portaaviones(const Coordenada& ini, const Coordenada& fin);
	~Portaaviones();
};
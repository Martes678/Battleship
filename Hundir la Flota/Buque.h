#pragma once
#include "Barco.h"
class Buque : public Barco{
public:
	Buque(const Coordenada& inicio, const Coordenada& fin);
	~Buque();
};
#pragma once
#include "Barco.h"
class Acorazado : public Barco{
public:
	Acorazado(const Coordenada& inicio, const Coordenada& fin);
	~Acorazado();
};
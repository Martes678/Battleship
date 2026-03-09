#pragma once
#include "Barco.h"
class Patrullero : public Barco{
public:
	Patrullero(const Coordenada& inicio, const Coordenada& fin);
	~Patrullero();
};
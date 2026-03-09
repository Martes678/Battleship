#pragma once
#include "Barco.h"
class Submarino : public Barco{
public:
	Submarino(const Coordenada& inicio, const Coordenada& fin);
	~Submarino();
};
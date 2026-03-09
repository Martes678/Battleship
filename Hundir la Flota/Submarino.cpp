#include "Submarino.h"
Submarino::Submarino(const Coordenada& inicio, const Coordenada& fin) : Barco(3, inicio, fin) {
	this->letra = 'S';
}
Submarino::~Submarino() {
}
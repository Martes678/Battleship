#include "Patrullero.h"
Patrullero::Patrullero(const Coordenada& inicio, const Coordenada& fin) : Barco(2, inicio, fin) {
	this->letra = 'P';
}
Patrullero::~Patrullero() {
}
#include "Acorazado.h"
Acorazado::Acorazado(const Coordenada& inicio, const Coordenada& fin) : Barco(4, inicio, fin) {
	this->letra = 'A';
}
Acorazado::~Acorazado() {
}
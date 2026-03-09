#include "Buque.h"
Buque::Buque(const Coordenada& inicio, const Coordenada& fin) : Barco(1, inicio, fin) {
	this->letra = 'B';
}
Buque::~Buque() {
}
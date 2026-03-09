#include "Portaaviones.h"
Portaaviones::Portaaviones(const Coordenada& inicio, const Coordenada& fin) : Barco(5, inicio, fin) {
	this->letra = 'V';
}
Portaaviones::~Portaaviones() {
}
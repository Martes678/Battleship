#include "Tablero.h"
Tablero::Tablero() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->matriz[i][j] = '~';
		}
	}
}
Tablero::~Tablero() {

}
bool Tablero::esValida(const Coordenada& c) const {
	Coordenada inicio('A', 0);
	Coordenada fin('J', 9);
	if (c >= inicio && c <= fin) {
		return true;
	}
	else {
		return false;
	}
}
char Tablero::getCelda(const Coordenada& c) const{
	if (this->esValida(c) == true) {
		return this->matriz[c.getFila()][c.getColumna()];
	}
	return '\0';
}
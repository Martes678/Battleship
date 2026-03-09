#include "Coordenada.h"
Coordenada::Coordenada() {
	this->columna = 0;
	this->fila = 'A';
}
Coordenada::Coordenada(char fila, int columna) {
	this->fila = fila;
	this->columna = columna;
}
Coordenada::~Coordenada() {

}
int Coordenada::getColumna() const{
	return this->columna;
}
int Coordenada::getFila() const{
	return this->fila - 'A';
}
bool Coordenada::operator!=(const Coordenada& otra) const {
    if (this->getFila() != otra.getFila() || this->getColumna() != otra.getColumna()) {
        return true;
    }
    else {
        return false;
    }
}
bool Coordenada::operator==(const Coordenada& otra) const {
    if (this->getFila() == otra.getFila() && this->getColumna() == otra.getColumna()) {
        return true;
    }
    else {
        return false;
    }
}
bool Coordenada::operator<(const Coordenada& otra) const {
    if (this->getFila() < otra.getFila()) {
        return true;
    }
    else if (this->getFila() == otra.getFila()) {
        if (this->getColumna() < otra.getColumna()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
bool Coordenada::operator<=(const Coordenada& otra) const {
    if (this->getFila() < otra.getFila()) {
        return true;
    }
    else if (this->getFila() == otra.getFila()) {
        if (this->getColumna() <= otra.getColumna()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
bool Coordenada::operator>=(const Coordenada& otra) const {
    if (this->getFila() > otra.getFila()) {
        return true;
    }
    else if (this->getFila() == otra.getFila()) {
        if (this->getColumna() >= otra.getColumna()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
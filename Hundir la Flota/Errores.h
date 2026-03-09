#pragma once
#include <iostream>
#include <string>
using namespace std;
class Errores {
protected:
	string mensaje;
public:
	Errores(string mensaje) {
		this->mensaje = mensaje;
	}
	virtual string what() { 
		return this->mensaje; 
	}
};
class CoordenadaInvalida : public Errores {
public:
	CoordenadaInvalida() : Errores("La coordenada esta fuera del tablero, de A0-J9") {}
};
class ErrorBarco : public Errores {
public:
	ErrorBarco(string mensaje) : Errores(mensaje) {}
};
class ErrorArchivo : public Errores {
public:
	ErrorArchivo(string mensaje = "Error al cargar la partida, se inicia una nueva") : Errores(mensaje) {}
};
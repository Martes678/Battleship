#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Jugador.h"
using namespace std;
class Partida{
private:
	vector <Jugador*> jugadores;
	bool acabada;
	bool turno;
public:
	Partida();
	~Partida();
	void agregarJugador(Jugador* j);//Agregar un jugador nuevo
	Jugador* getJugadorActual() const;//Obtener el jugador actual
	Jugador* getJugadorEnemigo() const;//Obtener el jugador enemigo
	void cambiarTurno(const string& resultado);//Cambio de turno
	bool estaAcabada() const;//Verificador de partida acabada
	void finalizar();//Función para cambiar el valor de acabada
	void guardar(const string& nombreArchivo);//Guardar
	bool cargar(const string& nombreArchivo);//Cargar
};
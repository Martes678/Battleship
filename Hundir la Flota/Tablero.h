#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Coordenada.h"
#include "Barco.h"
using namespace std;
class Tablero{
protected:
    char matriz[10][10];
public:
    Tablero();
    virtual ~Tablero();
    virtual void mostrar() const = 0;//Mostrar tablero, cada hijo implementará el suyo
    virtual bool colocarBarco(Barco* b) = 0;
    virtual string ponerDisparo(const Coordenada& c) = 0;
    virtual void registrarResultado(const Coordenada& c, const string& resultado) = 0;
    bool esValida(const Coordenada& c) const;//Verificador de validez de coordenada
    char getCelda(const Coordenada& c) const;//Obtener la casilla
    virtual void guardarEstado(ofstream& archivo) const = 0;//Guardar
    virtual void cargarEstado(ifstream& archivo) = 0;//Cargar
};
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Tablero.h"
#include "T_Propio.h"
#include "T_Ataque.h"
#include "Barco.h"
#include "Portaaviones.h"
#include "Acorazado.h"
#include "Submarino.h"
#include "Patrullero.h"
#include "Buque.h"
#include "Errores.h"
using namespace std;
class Tablero;
class Jugador{
public:
    string nombre;
    Tablero* tableroPropio;
    Tablero* tableroAtaque;
    vector<Barco*> flota;
public:
    Jugador(const string& nombre);
    ~Jugador();
    void colocarFlota(const vector<Barco*>& barcos);//Función para colocar la flota
    void colocarFlotaManual();//Obtener los parámetros de la flota para ponerla manualmente
    void colocarFlotaAleatoria();//Obtener los parámetros de la flota para ponerla automáticamente
    string disparar(Jugador* jugadorEnemigo, const Coordenada& c);//Función para simular el disparo
    bool estaHundida() const;//Verificador de fin
    void mostrarTableros() const;//Función para mostrar los dos tableros
    void guardarEstado(ofstream& archivo);//Guardar
    void cargarEstado(ifstream& archivo);//Cargar
    string getNombre() const;//Obtener nombre
};
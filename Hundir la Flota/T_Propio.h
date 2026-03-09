#pragma once
#include "Tablero.h"
class T_Propio:public Tablero{
private:
    bool estaAdyacente(const Coordenada& inicio, const Coordenada& fin);//Comprobar si hay barcos adyacentes
    bool estaVacio(int fila, int columna);//Ver si está vacía la coordenada
    void obtenerBarco(const Coordenada& inicio, const Coordenada& fin, vector<Coordenada>& coords);//Obtener el barco
public:
    T_Propio();
    ~T_Propio();
    void mostrar() const override;//Mostrar el tablero propio
    bool colocarBarco(Barco* b) override;//Colocar el barco
    void registrarResultado(const Coordenada& c, const string& resultado) override;
    string ponerDisparo(const Coordenada& c) override;//Poner el disparo
    void guardarEstado(ofstream& archivo) const override;//Guardar
    void cargarEstado(ifstream& archivo) override;//Cargar
};
#pragma once
#include "Tablero.h"
#include "Coordenada.h"
using namespace std;
class T_Ataque:public Tablero {
private:
    vector<Coordenada> tiros;//Vector de tiros
public:
    T_Ataque();
    ~T_Ataque();
    void mostrar() const override;//Mostrar tablero de ataque
    bool colocarBarco(Barco* b) override;
    string ponerDisparo(const Coordenada& c) override;
    void registrarResultado(const Coordenada& c, const string& resultado) override;//Poner el disparo en el tablero
    bool disparada(const Coordenada& c) const;//Comprobador
    void guardarEstado(ofstream& archivo) const override;//Guardar
    void cargarEstado(ifstream& archivo) override;//Cargar
};
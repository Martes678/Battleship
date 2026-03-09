#include "Partida.h"
Partida::Partida() {
    this->acabada = false;
    this->turno = true;
}
Partida::~Partida() {
    for (Jugador* j : this->jugadores) {
        delete j;
    }
    this->jugadores.clear();
}
void Partida::agregarJugador(Jugador* j) {
    if (this->jugadores.size() < 2) {
        this->jugadores.push_back(j);
    }
}
Jugador* Partida::getJugadorActual() const {
    if (this->jugadores.size() < 2) {
        return nullptr;
    }
    if (turno) {
        return this->jugadores[0];
    }
    else {
        return this->jugadores[1];
    }
}
Jugador* Partida::getJugadorEnemigo() const {
    if (this->jugadores.size() < 2) {
        return nullptr;
    }
    if (turno) {
        return this->jugadores[1];
    }
    else {
        return this->jugadores[0];
    }
}
void Partida::cambiarTurno(const string& resultado) {
    if (resultado == "Agua") {
        this->turno = !this->turno;
    }
}
bool Partida::estaAcabada() const {
    return this->acabada;
}
void Partida::finalizar() {
    this->acabada = true;
}
void Partida::guardar(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open() == true) {
        archivo << this->turno << endl;
        archivo << this->acabada << endl;
        for (int i = 0; i < this->jugadores.size(); i++) {
            this->jugadores[i]->guardarEstado(archivo);
        }
        archivo.close();
        cout << "Partida guardada con exito en " << nombreArchivo << endl;
    }
    else {
        cout << "No se pudo abrir el archivo para guardar" << endl;
    }
}
bool Partida::cargar(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        throw ErrorArchivo();
    }
    int turnoAux;
    int acabadaAux;
    archivo >> turnoAux;
    if (turnoAux == 1) {
        this->turno = true;
    }
    else {
        this->turno = false;
    }
    archivo >> acabadaAux;
    if (acabadaAux == 1) {
        this->acabada = true;
    }
    else {
        this->acabada = false;
    }
    for (Jugador* j : this->jugadores) {
        delete j;
    }
    this->jugadores.clear();

    for (int i = 0; i < 2; i++) {
        Jugador* j = new Jugador("Temp");
        j->cargarEstado(archivo);
        this->jugadores.push_back(j);
    }
    archivo.close();
    return true;
}
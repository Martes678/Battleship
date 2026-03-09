#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "Partida.h"
#include "Jugador.h"
#include "Errores.h"
using namespace std;
int main() {
    bool fin = false;
    while (fin == false) {
        Partida partida;
        Jugador* j1 = nullptr;
        Jugador* j2 = nullptr;
        char resp;
        cout << "Cargar partida (C) nueva partida (N): ";
        cin >> resp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        resp = toupper(resp);
        if (resp == 'C') {
            string nombreArchivo;
            cout << "Nombre del archivo a cargar: ";
            cin >> nombreArchivo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            try {
                if (partida.cargar(nombreArchivo) == false) {
                    throw ErrorArchivo();
                }
                else {
                    cout << "Partida cargada" << endl;
                    cout << "Presione ENTER para continuar";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            catch (Errores& e) {
                cout << e.what() << endl;
                resp = 'N';
                cout << "Presione ENTER para continuar";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            system("cls");
        }
        if (resp == 'N' || partida.getJugadorActual() == nullptr) {
            string nombre;
            cout << "Introduce nombre para el jugador 1: " << endl;
            cin >> nombre;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            j1 = new Jugador(nombre);
            bool nombreValido = false;
            while (nombreValido == false) {
                cout << "Introduce nombre para el jugador 2: " << endl;
                cin >> nombre;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (nombre == j1->getNombre()) {
                    cout << "Los nombres del jugador 1 y jugador 2 no pueden ser iguales" << endl;
                }
                else {
                    j2 = new Jugador(nombre);
                    nombreValido = true;
                }
            }
            cout << j1->getNombre() << " barcos automaticos (A) o manual (M):";
            char op1;
            cin >> op1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (toupper(op1) == 'M') {
                j1->colocarFlotaManual();
                system("cls");
            }
            else {
                j1->colocarFlotaAleatoria();
            }
            cout << j2->getNombre() << " barcos automaticos (A) o manual (M):";
            char resp2;
            cin >> resp2;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (toupper(resp2) == 'M') {
                j2->colocarFlotaManual();
                system("cls");
            }
            else {
                j2->colocarFlotaAleatoria();
            }
            partida.agregarJugador(j1);
            partida.agregarJugador(j2);
            cout << "Flotas colocadas" << endl;
        }
        system("cls");
        while (partida.estaAcabada() == false) {
            try {
                Jugador* jugadorActual = partida.getJugadorActual();
                Jugador* jugadorEnemigo = partida.getJugadorEnemigo();
                if (jugadorActual == nullptr || jugadorEnemigo == nullptr) {
                    cout << "Jugadores no encontrados" << endl;
                    break;
                }
                cout << "Turno: " << jugadorActual->getNombre() << endl;
                jugadorActual->mostrarTableros();
                string coord;
                char fila;
                int columna;
                Coordenada c;
                bool coordenadaValida = false;
                bool repetida = false;
                while (coordenadaValida == false || repetida == true) {
                    repetida = false;
                    cout << "Ingrese coordenada de ataque (Formato: A5, J9):";
                    getline(cin, coord);
                    if (coord.length() == 2) {
                        fila = toupper(coord[0]);
                        char columnaChar = coord[1];
                        if (isdigit(columnaChar)) {
                            columna = columnaChar - '0';
                            c = Coordenada(fila, columna);
                            if (jugadorActual->tableroAtaque->esValida(c) == true) {
                                coordenadaValida = true;
                                T_Ataque* tableroAtaque = dynamic_cast<T_Ataque*>(jugadorActual->tableroAtaque);
                                if (tableroAtaque != nullptr && tableroAtaque->disparada(c)) {
                                    cout << "Coordenada " << coord << " ya disparada" << endl;
                                    repetida = true;
                                    coordenadaValida = false;
                                }
                            }
                            else {
                                throw CoordenadaInvalida();
                            }
                        }
                        else {
                            coordenadaValida = false;
                            throw Errores("Formato incorrecto");
                        }
                    }
                    else {
                        coordenadaValida = false;
                        throw Errores("Formato incorrecto");
                    }
                }
                string resultado = jugadorActual->disparar(jugadorEnemigo, c);
                cout << "Resultado del disparo: " << resultado << endl;
                if (jugadorEnemigo->estaHundida() == true) {
                    partida.finalizar();
                }
                else {
                    partida.cambiarTurno(resultado);
                    cout << "Desea guardar la partida (S/N): ";
                    char guardar;
                    cin >> guardar;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (toupper(guardar) == 'S') {
                        string nombreArchivo;
                        cout << "Nombre del archivo a guardar: ";
                        cin >> nombreArchivo;
                        partida.guardar(nombreArchivo);
                    }
                    if (partida.estaAcabada() == false) {
                        cout << "Presione ENTER para continuar";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    system("cls");
                }
            }
            catch (Errores& e) {
                cout << e.what() << endl;
                cout << "Presione ENTER para volver a disparar";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
            }
        }
        cout << "Flota de " << partida.getJugadorEnemigo()->getNombre() << " hundida\nGanador: " << partida.getJugadorActual()->getNombre() << "\nPartida acabada" << endl;
        char letra;
        cout << "Otra partida? (S/N)";
        cin >> letra;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(letra) == 'N') {
            fin = true;
        }
        system("cls");
    }
    return 0;
}
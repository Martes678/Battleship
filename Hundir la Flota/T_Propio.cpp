#include "T_Propio.h"
T_Propio::T_Propio() {

}
T_Propio::~T_Propio(){

}
void T_Propio::mostrar() const {
    cout << "Tablero Propio:" << endl;
    cout << "____";
    for (int i = 0; i < 10; i++) {
        cout << i << "_";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << (char)('A' + i) << " |";
        for (int j = 0; j <= 10; j++) {
            if (j != 10) {
                cout << " " << this->matriz[i][j];
            }
            else {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
    cout << "-V = Portaaviones\n-A = Acorazado\n-S = Submarino\n-P = Patrullero\n-B = Buque\n-X = Tocado\n-* = Agua disparada" << endl;
}
bool T_Propio::estaVacio(int fila, int columna) {
    if (this->matriz[fila][columna] == '~' || this->matriz[fila][columna] == '*') {
        return true;
    }
    else {
        return false;
    }
}
void T_Propio::obtenerBarco(const Coordenada& inicio, const Coordenada& fin, vector<Coordenada>& coords) {
    if (inicio.getFila() == fin.getFila()) {
        char filaChar = (char)('A' + inicio.getFila());
        for (int j = inicio.getColumna(); j <= fin.getColumna(); j++) {
            coords.push_back(Coordenada(filaChar, j));
        }
    }
    else if (inicio.getColumna() == fin.getColumna()) {
        for (int i = inicio.getFila(); i <= fin.getFila(); i++) {
            char filaChar = (char)('A' + i);
            coords.push_back(Coordenada(filaChar, inicio.getColumna()));
        }
    }
}
bool T_Propio::estaAdyacente(const Coordenada& inicio, const Coordenada& fin) {
    vector<Coordenada> coord;
    this->obtenerBarco(inicio, fin, coord);
    int desplazamientos[9][2] = {
        {-1, -1},
        {-1, 0}, 
        {-1, 1},
        { 0, -1},
        { 0, 0}, 
        { 0, 1},
        { 1, -1},
        { 1, 0},
        { 1, 1}
    };
    for (const Coordenada& c : coord) {
        for (int i = 0; i < 9; i++) {
            int filaAdy = c.getFila() + desplazamientos[i][0];
            int colAdy = c.getColumna() + desplazamientos[i][1];
            Coordenada comprobador(('A' + filaAdy), colAdy);
            if (c != comprobador) {
                if (this->esValida(comprobador) == true) {
                    if (this->estaVacio(filaAdy, colAdy) == false) {
                        return true;
                    }
                }
            } 
        }
    }
    return false;
}
bool T_Propio::colocarBarco(Barco* b) {
    int longitud;
    if (b->horizontal() == true) {
        longitud = abs(b->getInicio().getColumna() - b->getFinal().getColumna()) + 1;
    }
    else {
        longitud = abs(b->getInicio().getFila() - b->getFinal().getFila()) + 1;
    }
    if (longitud != b->getTam()) {
        throw ErrorBarco("El tamanio o el formato no es el correcto");
    }
    vector<Coordenada> coords;
    this->obtenerBarco(b->getInicio(), b->getFinal(), coords);
    for (const Coordenada& c : coords) {
        if (this->esValida(c) == false) {
            throw CoordenadaInvalida();
        }
    }
    if (this->estaAdyacente(b->getInicio(), b->getFinal()) == true) {
        throw ErrorBarco("Solapamiento o adyacencia");
    }
    for (const Coordenada& c : coords) {
        this->matriz[c.getFila()][c.getColumna()] = b->getLetraBarco();
    }
    return true;
}
void T_Propio::registrarResultado(const Coordenada& c, const string& resultado){

}
string T_Propio::ponerDisparo(const Coordenada& c) {
    if (this->esValida(c) == false) {
        throw CoordenadaInvalida();
    }
    string resultado;
    if (this->matriz[c.getFila()][c.getColumna()] == '~' || this->matriz[c.getFila()][c.getColumna()] == '*') {
        this->matriz[c.getFila()][c.getColumna()] = '*';
        resultado = "Agua";
    }
    else {
        this->matriz[c.getFila()][c.getColumna()] = 'X';
        resultado = "Tocado";
    }
    return resultado;
}
void T_Propio::guardarEstado(ofstream& archivo) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            archivo << this->matriz[i][j];
        }
        archivo << "\n";
    }
}
void T_Propio::cargarEstado(ifstream& archivo) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            archivo >> this->matriz[i][j];
        }
    }
}
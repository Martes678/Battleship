#include "T_Ataque.h"
T_Ataque::T_Ataque() {

}
T_Ataque::~T_Ataque(){

}
void T_Ataque::mostrar() const {
    cout << "Tablero de Ataque:" << endl;
    cout << "____";
    for (int i = 0; i < 10; i++) {
        cout << i << "_";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << (char)('A' + i) << " |";
        for (int j = 0; j <= 10; j++) {
            if(j != 10){
                cout << " " << this->matriz[i][j];
            }
            else {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
    cout << "-F = Agua\n-O = Tocado\n-~ = Sin disparar" << endl;

}
bool T_Ataque::colocarBarco(Barco* b){
    return false;
}
string T_Ataque::ponerDisparo(const Coordenada& c){
    return "No se puede disparar en el de ataque\n";
}
void T_Ataque::registrarResultado(const Coordenada& c, const string& resultado) {
    if (this->esValida(c)==true && this->disparada(c) == false) {
        this->tiros.push_back(c);//Se añaden los tiros en el vector
        if (resultado == "Agua") {
            this->matriz[c.getFila()][c.getColumna()] = 'F';
        }
        else if (resultado == "Tocado" || resultado == "Tocado y hundido") {
            this->matriz[c.getFila()][c.getColumna()] = 'O';
        }
    }
}
bool T_Ataque::disparada(const Coordenada& c) const {
    for (const Coordenada& disparo : this->tiros) {
        if (disparo == c) {
            return true;
        }
    }
    return false;
}
void T_Ataque::guardarEstado(ofstream& archivo) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            archivo << this->matriz[i][j];
        }
        archivo << "\n";
    }
    archivo << this->tiros.size() << "\n";
    for (const Coordenada& c : this->tiros) {
        archivo << (char)(c.getFila() + 'A') << " " << c.getColumna() << "\n";
    }
}
void T_Ataque::cargarEstado(ifstream& archivo) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            archivo >> this->matriz[i][j];
        }
    }
    int numTiros;
    archivo >> numTiros;
    this->tiros.clear();
    char fila;
    int col;
    for (int i = 0; i < numTiros; i++) {
        archivo >> fila >> col;
        this->tiros.push_back(Coordenada(fila, col));
    }
}
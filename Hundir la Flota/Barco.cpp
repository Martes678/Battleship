#include "Barco.h"
Barco::Barco(int tam, const Coordenada& ini, const Coordenada& fin) {
	this->tam = tam;
	this->vida = tam;
	if (fin < ini) {
		this->inicio = fin;
		this->fin = ini;
	}
	else {
		this->inicio = ini;
		this->fin = fin;
	}
	this->letra = '\0';
}
Barco::~Barco() {
}
int Barco::getVida() const {
	return this->vida;
}
int Barco::getTam() const {
	return this->tam;
}
bool Barco::horizontal(){
	if (this->inicio.getFila() == this->fin.getFila()) {//Si la fila de inicio es igual que la final,
		return 1;//Entonces barco en horizontal
	}
	else {//Si no barco en vertical
		return 0;
	}
}
Coordenada Barco::getInicio() const {
	return this->inicio;
}
Coordenada Barco::getFinal() const {
	return this->fin;
}
void Barco::recibirDisparo() {
	if (this->vida > 0) {
		this->vida--;
	}
}
char Barco::getLetraBarco() const {
	return this->letra;
}
void Barco::guardarEstado(ofstream& archivo) const {
	archivo << letra << " " << (char)(inicio.getFila() + 'A') << " " << inicio.getColumna() << " " << (char)(fin.getFila() + 'A') << " " << fin.getColumna() << " " << vida << "\n";
}
void Barco::setVida(int vida){
	this->vida = vida;
}
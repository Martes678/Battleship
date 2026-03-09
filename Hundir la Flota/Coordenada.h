#pragma once
class Coordenada{
private:
	int columna;
	char fila;
public:
	Coordenada();
	Coordenada(char fila, int columna);
	~Coordenada();
	int getColumna() const;//Obtener la columna
	int getFila() const;//Obtener la fila
	bool operator!=(const Coordenada& otra) const;//No solapamiento de coordenadas
	bool operator==(const Coordenada& otra) const;//Verificador de coordenadas
	bool operator<(const Coordenada& otra) const;//Comprobador de coordenadas
	bool operator<=(const Coordenada& otra) const;//Comprobador de coordenadas
	bool operator>=(const Coordenada& otra) const;//Comprobador de coordenadas
};
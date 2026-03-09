#pragma once
#include "Coordenada.h"
#include "Errores.h"
#include <fstream>
using namespace std;
class Barco{
protected:
	int tam;//Tamaño del barco
	int vida;//Vida del barco
	char letra;//Letra del barco
	Coordenada inicio;//Coordenada de inicio del barco
	Coordenada fin;//Coordenada de fin del barco
public:
	Barco(int tam, const Coordenada& ini, const Coordenada& fin);
	virtual ~Barco();//Destructor tanto para el padre como para el hijo
	virtual bool horizontal();//Verificador de horizontal
	int getVida() const;//Obtener vida
	int getTam() const;//Obtener tamaño
	Coordenada getInicio() const;//Obtener casilla de inicio
	Coordenada getFinal() const;//Obtener casilla de final
	void recibirDisparo();//Recibir un disparo
	virtual char getLetraBarco() const;
	virtual void guardarEstado(ofstream& archivo) const;//Guardar el estado de los barcos
	void setVida(int vida);//Cargar la vida del barco
};
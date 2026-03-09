#include "Jugador.h"
Jugador::Jugador(const string& nombre) {
	this->nombre = nombre;
	this->tableroPropio = new T_Propio();
	this->tableroAtaque = new T_Ataque();
}
Jugador::~Jugador() {
	delete this->tableroPropio;
	delete this->tableroAtaque;
	for (Barco* b : this->flota) {
		delete b;
	}
	this->flota.clear();
}
void Jugador::colocarFlota(const vector<Barco*>& barcos) {
	for (Barco* b : this->flota) {
		delete b;
	}
	this->flota.clear();
	for (Barco* b : barcos) {
		flota.push_back(b);
	}
	for (Barco* b : this->flota) {
		try {
			if (this->tableroPropio->colocarBarco(b) == false) {
				throw ErrorBarco("Solapamiento o adyacencia");
			}
		}
		catch (Errores& e) {
			cout << e.what() << endl;
		}
	}
}
string Jugador::disparar(Jugador* jugadorEnemigo, const Coordenada& c) {
	char celda = jugadorEnemigo->tableroPropio->getCelda(c);
	string resultado;
	resultado = jugadorEnemigo->tableroPropio->ponerDisparo(c);
	if (celda != '~' && celda != '*' && celda != 'X' && jugadorEnemigo->tableroPropio->esValida(c) == true) {
		resultado = "Tocado";
		Barco* barcoTocado = nullptr;
		for (Barco* b : jugadorEnemigo->flota) {
			if (b->getLetraBarco() == celda) {
				barcoTocado = b;
				break;
			}
		}
		if (barcoTocado != nullptr) {
			barcoTocado->recibirDisparo();
			if (barcoTocado->getVida() == 0) {
				resultado = "Tocado y hundido";
			}
		}
	}
	dynamic_cast<T_Ataque*>(this->tableroAtaque)->registrarResultado(c, resultado);
	return resultado;
}
bool Jugador::estaHundida() const {
	for (const Barco* b : this->flota) {
		if (b->getVida() > 0) {
			return false;
		}
	}
	return true;
}
void Jugador::mostrarTableros() const {
	this->tableroPropio->mostrar();
	this->tableroAtaque->mostrar();
}
string Jugador::getNombre() const {
	return this->nombre;
}
void Jugador::colocarFlotaManual() {
	string tipos[] = { "Portaaviones", "Acorazado", "Submarino", "Patrullero", "Buque" };
	int tam[] = { 5, 4, 3, 2, 1 };

	for (int i = 0; i < 5; i++) {
		bool colocado = false;
		while (!colocado) {
			try {
				this->tableroPropio->mostrar();
				cout << "Colocando " << tipos[i] << " de tamanio " << tam[i] << endl;
				string c1, c2;
				cout << "Coordenada inicio (A0, J9): ";
				cin >> c1;
				cout << "Coordenada fin (A0, J9): ";
				cin >> c2;
				char filaLetraIni = c1[0];
				char filaNormalizadaIni = toupper(filaLetraIni);
				char columnaCharIni = c1[1];
				int columnaIntIni = columnaCharIni - '0';
				Coordenada inicio(filaNormalizadaIni, columnaIntIni);
				char filaLetraFin = c2[0];
				char filaNormalizadaFin = toupper(filaLetraFin);
				char columnaCharFin = c2[1];
				int columnaIntFin = columnaCharFin - '0';
				if (filaLetraIni != filaLetraFin && columnaIntIni != columnaIntFin) {
					throw ErrorBarco("NO barcos en diagonal");
				}
				Coordenada fin(filaNormalizadaFin, columnaIntFin);
				Barco* nuevo = nullptr;
				switch (tam[i]) {
				case 5:
					nuevo = new Portaaviones(inicio, fin); 
					break;
				case 4: 
					nuevo = new Acorazado(inicio, fin); 
					break;
				case 3: 
					nuevo = new Submarino(inicio, fin);
					break;
				case 2:
					nuevo = new Patrullero(inicio, fin);
					break;
				case 1: 
					nuevo = new Buque(inicio, fin);
					break;
				}

				if (this->tableroPropio->colocarBarco(nuevo)) {
					this->flota.push_back(nuevo);
					colocado = true;
					system("cls");
				}
				else {
					delete nuevo;
					throw ErrorBarco("Solapamiento o adyacencia");
				}
			}
			catch (Errores& e) {
				cout << e.what() << endl;
				cout << "Intentalo de nuevo" << endl;
			}
		}
	}
}
void Jugador::colocarFlotaAleatoria() {
	srand(time(NULL));
	int tam[] = { 5, 4, 3, 2, 1 };
	for (int i = 0; i < 5; i++) {
		bool colocado = false;
		while (!colocado) {
			int fila = rand() % 10;
			int col = rand() % 10;
			int orientacion = rand() % 2;//0 horizontal, 1 vertical
			Coordenada inicio('A' + fila, col);
			Coordenada fin;
			if (orientacion == 0) {
				fin = Coordenada('A' + fila, col + tam[i] - 1);
			}
			else {
				fin = Coordenada('A' + fila + tam[i] - 1, col);
			}
			Barco* nuevo = nullptr;
			if (this->tableroPropio->esValida(fin)) {
				switch (tam[i]) {
				case 5:
					nuevo = new Portaaviones(inicio, fin);
					break;
				case 4: 
					nuevo = new Acorazado(inicio, fin);
					break;
				case 3: 
					nuevo = new Submarino(inicio, fin);
					break;
				case 2: 
					nuevo = new Patrullero(inicio, fin);
					break;
				case 1: 
					nuevo = new Buque(inicio, fin); 
					break;
				}
				try {
					if (this->tableroPropio->colocarBarco(nuevo)) {
						this->flota.push_back(nuevo);
						colocado = true;
					}
					else {
						delete nuevo;
					}
				}
				catch (...) {
					delete nuevo;
				}
			}
		}
	}
}
void Jugador::guardarEstado(ofstream& archivo) {
	archivo << this->nombre << "\n";
	this->tableroPropio->guardarEstado(archivo);
	this->tableroAtaque->guardarEstado(archivo);
	archivo << this->flota.size() << "\n";
	for (Barco* b : this->flota) {
		b->guardarEstado(archivo);
	}
}
void Jugador::cargarEstado(ifstream& archivo) {
	archivo >> this->nombre;
	this->tableroPropio->cargarEstado(archivo);
	this->tableroAtaque->cargarEstado(archivo);
	for (Barco* b : this->flota) {
		delete b;
	}
	this->flota.clear();
	int numBarcos;
	archivo >> numBarcos;
	char letra, filaIni, filaFin;
	int colIni, colFin, vida;
	for (int i = 0; i < numBarcos; i++) {
		archivo >> letra >> filaIni >> colIni >> filaFin >> colFin >> vida;
		Coordenada inicio(filaIni, colIni);
		Coordenada fin(filaFin, colFin);
		Barco* nuevoBarco = nullptr;
		if (letra == 'V') {
			nuevoBarco = new Portaaviones(inicio, fin);
		}
		else if (letra == 'A') {
			nuevoBarco = new Acorazado(inicio, fin);
		}
		else if (letra == 'S') {
			nuevoBarco = new Submarino(inicio, fin);
		}
		else if (letra == 'P') {
			nuevoBarco = new Patrullero(inicio, fin);
		}
		else if (letra == 'B') {
			nuevoBarco = new Buque(inicio, fin);
		}
		if (nuevoBarco != nullptr) {
			nuevoBarco->setVida(vida);
			this->flota.push_back(nuevoBarco);
		}
	}
}
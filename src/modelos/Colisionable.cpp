#include "Colisionable.h"

Colisionable::Colisionable() {}


Encuadre* Colisionable::obtenerInsercion() {
	return &insercion;
}


bool Colisionable::estaAtacando() {
	return false;
}


int Colisionable::obtenerDanio() {
	return 0;
}


int Colisionable::obtenerPuntosDeGolpe() {
	return 0;
}


int Colisionable::recibirDanioDe(Colisionable* colisionable) {
	return 0;
}


Colisionable::~Colisionable() {}


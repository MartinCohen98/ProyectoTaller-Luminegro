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


void Colisionable::recibirDanioDe(Colisionable* colisionable) {}


Colisionable::~Colisionable() {}


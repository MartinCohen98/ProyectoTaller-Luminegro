#include "Colisionable.h"

Colisionable::Colisionable() {}


void Colisionable::agregarEnColisionador(Colisionador* colisionador) {
	colisionador->agregarEncuadre(&insercion);
}


Colisionable::~Colisionable() {}


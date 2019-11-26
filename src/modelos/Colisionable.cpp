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


tipoDeSprite Colisionable::obtenerTipo() {
	return tipo;
}


int Colisionable::obtenerPuntosDeGolpe() {
	return 0;
}


tipoDeArma Colisionable::obtenerTipoDeArma() {
	return desarmado;
}


int Colisionable::recibirDanioDe(Colisionable* colisionable) {
	return 0;
}

void Colisionable::sumarPuntos(int puntos){

}


void Colisionable::desaparecer() {}


tipoDeSprite Colisionable::consultarTipo(){
	return tipo;
}

Colisionable::~Colisionable() {}


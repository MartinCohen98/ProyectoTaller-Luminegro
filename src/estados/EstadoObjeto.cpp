#include "EstadoObjeto.h"

EstadoObjeto::EstadoObjeto() {}

EstadoObjeto* EstadoObjeto::romperse(tipoDeSprite tipo){
	return NULL;
}


bool EstadoObjeto::estaRoto() {
	return false;
}


bool EstadoObjeto::terminado() {
	return false;
}


Encuadre* EstadoObjeto::obtenerEncuadre() {
	return &frameActual;
}


EstadoObjeto::~EstadoObjeto() {}


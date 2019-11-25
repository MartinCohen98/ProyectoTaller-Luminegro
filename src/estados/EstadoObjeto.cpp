#include "EstadoObjeto.h"

EstadoObjeto::EstadoObjeto() {
	alto = 0;
	ancho = 0;
	tipo = MensajeInvalido;
}


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


EstadoObjeto::~EstadoObjeto() {
	// TODO Auto-generated destructor stub
}


#include "EstadoJugador.h"

EstadoJugador::EstadoJugador() {
	alto = 0;
	ancho = 0;
}

Encuadre EstadoJugador::obtenerSprite() {
	return frameActual;
}

EstadoJugador* EstadoJugador::avanzar() {
	return NULL;
}

EstadoJugador* EstadoJugador::parar() {
	return NULL;
}

EstadoJugador* EstadoJugador::agacharse() {
	return NULL;
}

EstadoJugador* EstadoJugador::pegar() {
	return NULL;
}

EstadoJugador* EstadoJugador::saltar() {
	return NULL;
}

bool EstadoJugador::estaSaltando() {
	return false;
}

int EstadoJugador::obtenerElevacion() {
	return 0;
}

int EstadoJugador::obtenerAlto() {
	return alto;
}

int EstadoJugador::obtenerAncho() {
	return ancho;
}

bool EstadoJugador::puedeMoverse() {
	return true;
}

EstadoJugador::~EstadoJugador() {}
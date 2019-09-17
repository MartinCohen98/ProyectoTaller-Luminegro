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

int EstadoJugador::obtenerAlto() {
	return alto;
}

int EstadoJugador::obtenerAncho() {
	return ancho;
}

EstadoJugador::~EstadoJugador() {}

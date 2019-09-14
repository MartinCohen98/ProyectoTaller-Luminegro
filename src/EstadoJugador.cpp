#include "EstadoJugador.h"

EstadoJugador::EstadoJugador() {}

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

EstadoJugador::~EstadoJugador() {}

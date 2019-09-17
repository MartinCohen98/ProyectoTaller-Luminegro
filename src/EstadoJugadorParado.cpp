#include "EstadoJugadorParado.h"

EstadoJugadorParado::EstadoJugadorParado() {
	frameActual.modificar(0, 100, 50, 100);
}

EstadoJugador* EstadoJugadorParado::parar() {
	return (this);
}

EstadoJugador* EstadoJugadorParado::avanzar() {
	delete this;
	return (new EstadoJugadorAvanzando());
}

EstadoJugador* EstadoJugadorParado::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}

EstadoJugador* EstadoJugadorParado::pegar() {
	delete this;
	return (new EstadoJugadorParado());
}

EstadoJugadorParado::~EstadoJugadorParado() {}


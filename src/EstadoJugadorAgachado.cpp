#include "EstadoJugadorAgachado.h"

EstadoJugadorAgachado::EstadoJugadorAgachado() {
	frameActual.modificar(100, 100, 50, 100);
}

EstadoJugador* EstadoJugadorAgachado::parar() {
	delete this;
	return (new EstadoJugadorParado());
}

EstadoJugador* EstadoJugadorAgachado::avanzar() {
	delete this;
	return (new EstadoJugadorAvanzando());
}

EstadoJugador* EstadoJugadorAgachado::agacharse() {
	return this;
}

EstadoJugador* EstadoJugadorAgachado::pegar() {
	delete this;
	return (new EstadoJugadorPegando());
}

EstadoJugadorAgachado::~EstadoJugadorAgachado() {}


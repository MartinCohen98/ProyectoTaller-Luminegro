#include "EstadoJugadorFrenado.h"

EstadoJugadorFrenado::EstadoJugadorFrenado() {
	frameActual.modificar(0, 100, 50, 100);
}

EstadoJugador* EstadoJugadorFrenado::parar() {
	return (this);
}

EstadoJugador* EstadoJugadorFrenado::avanzar() {
	delete this;
	return (new EstadoJugadorAvanzando());
}

EstadoJugador* EstadoJugadorFrenado::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}

EstadoJugadorFrenado::~EstadoJugadorFrenado() {}


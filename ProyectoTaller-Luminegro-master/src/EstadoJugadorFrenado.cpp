#include "EstadoJugadorFrenado.h"

EstadoJugadorFrenado::EstadoJugadorFrenado() {
	frameActual.modificar(0, 100, 50, 100);
}

EstadoJugadorFrenado::EstadoJugadorFrenado(int x, int y, int ancho, int alto) {
	frameActual.modificar(x,y,ancho,alto);
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


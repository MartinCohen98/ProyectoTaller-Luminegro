#include "EstadoJugadorParado.h"

EstadoJugadorParado::EstadoJugadorParado() {
	alto = 100;
	ancho = 50;
	frameActual.modificar(0, 100, ancho, alto);
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
	return (new EstadoJugadorPegando());
}

EstadoJugador* EstadoJugadorParado::saltar() {
	delete this;
	return (new EstadoJugadorSaltando());
}

EstadoJugadorParado::~EstadoJugadorParado() {}

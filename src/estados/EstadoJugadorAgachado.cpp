#include "EstadoJugadorAgachado.h"

EstadoJugadorAgachado::EstadoJugadorAgachado() {
	alto = 100;
	ancho = 50;
	frameActual.modificar(100, 100, ancho, alto);
}

EstadoJugador* EstadoJugadorAgachado::parar() {
	delete this;
	return (new EstadoJugadorParado());
}

EstadoJugador* EstadoJugadorAgachado::avanzar() {
	return this;
}

EstadoJugador* EstadoJugadorAgachado::agacharse() {
	return this;
}

EstadoJugador* EstadoJugadorAgachado::pegar() {
	delete this;
	return (new EstadoJugadorPegando());
}

EstadoJugador* EstadoJugadorAgachado::saltar() {
	delete this;
	return (new EstadoJugadorSaltando());
}

bool EstadoJugadorAgachado::puedeMoverse() {
	return false;
}

EstadoJugadorAgachado::~EstadoJugadorAgachado() {}


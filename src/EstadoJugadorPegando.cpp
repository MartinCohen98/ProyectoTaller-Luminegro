#include "EstadoJugadorPegando.h"

EstadoJugadorPegando::EstadoJugadorPegando() {

}

EstadoJugador* EstadoJugadorPegando::avanzar() {
	return (pegar());
}

EstadoJugador* EstadoJugadorPegando::parar() {
	return (pegar());
}

EstadoJugador* EstadoJugadorPegando::agacharse() {
	return (pegar());
}

EstadoJugador* EstadoJugadorPegando::pegar() {
	if (!terminado()) {
		return (this);
	} else {
		delete this;
		return (new EstadoJugadorParado());
	}
}

bool EstadoJugadorPegando::terminado() {
	return (true);
}

EstadoJugadorPegando::~EstadoJugadorPegando() {}


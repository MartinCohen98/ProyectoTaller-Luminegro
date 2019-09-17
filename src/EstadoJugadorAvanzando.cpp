#include "EstadoJugadorAvanzando.h"

EstadoJugadorAvanzando::EstadoJugadorAvanzando() {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	frameActual.modificar(0, 0, 50, 100);
}

EstadoJugador* EstadoJugadorAvanzando::parar() {
	delete this;
	return (new EstadoJugadorParado());
}

EstadoJugador* EstadoJugadorAvanzando::avanzar() {
	framesTranscurridas++;
	if (framesTranscurridas == 4) {
		framesTranscurridas = 0;
		cambiarFrame();
	}
	return (this);
}

EstadoJugador* EstadoJugadorAvanzando::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}

EstadoJugador* EstadoJugadorAvanzando::pegar() {
	delete this;
	return (new EstadoJugadorPegando());
}

void EstadoJugadorAvanzando::cambiarFrame() {
	if (numeroDeFrame == 5) {
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((50 * numeroDeFrame), 0, 50, 100);
}

EstadoJugadorAvanzando::~EstadoJugadorAvanzando() {
}


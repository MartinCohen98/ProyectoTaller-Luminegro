#include "EstadoJugadorSaltando.h"

EstadoJugadorSaltando::EstadoJugadorSaltando() {
	alto = 110;
	ancho = 60;
	frameActual.modificar(0, 210, ancho, alto);
	numeroDeFrame = 0;
	framesTranscurridas = 0;
	elevacion = 0;
}

EstadoJugador* EstadoJugadorSaltando::avanzar() {
	return saltar();
}

EstadoJugador* EstadoJugadorSaltando::parar() {
	return saltar();
}

EstadoJugador* EstadoJugadorSaltando::agacharse() {
	return saltar();
}

EstadoJugador* EstadoJugadorSaltando::pegar() {
	return saltar();
}

EstadoJugador* EstadoJugadorSaltando::saltar() {
	if ((numeroDeFrame != 8) || (framesTranscurridas != 2)) {
		elevacion += ((4 - numeroDeFrame) * 10);
		framesTranscurridas++;
		if (framesTranscurridas == 3) {
			framesTranscurridas = 0;
			cambiarFrame();
		}
		return (this);
	} else {
		delete this;
		return (new EstadoJugadorParado());
	}
}

int EstadoJugadorSaltando::obtenerElevacion() {
	return elevacion;
}

void EstadoJugadorSaltando::cambiarFrame() {
	numeroDeFrame++;
	if (numeroDeFrame < 8) {
		frameActual.modificar((ancho * numeroDeFrame), 210, ancho, alto);
	} else {
		frameActual.modificar((ancho * 2), 210, ancho, alto);
	}
}

EstadoJugadorSaltando::~EstadoJugadorSaltando() {}

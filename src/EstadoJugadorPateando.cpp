#include "EstadoJugadorPateando.h"

EstadoJugadorPateando::EstadoJugadorPateando(int elNumeroDeFrame,
					int lasFramesTranscurridas, int laElevacion) {
	alto = 100;
	ancho = 80;
	frameActual.modificar(0, 320, ancho, alto);
	numeroDeFrame = elNumeroDeFrame;
	framesTranscurridas = lasFramesTranscurridas;
	elevacion = laElevacion;
	frameCambiada = false;
}

EstadoJugador* EstadoJugadorPateando::avanzar() {
	return pegar();
}

EstadoJugador* EstadoJugadorPateando::parar() {
	return pegar();
}

EstadoJugador* EstadoJugadorPateando::agacharse() {
	return pegar();
}

EstadoJugador* EstadoJugadorPateando::pegar() {
	if ((numeroDeFrame != 8) || (framesTranscurridas != 2)) {
		elevacion += ((4 - numeroDeFrame) * 10);
		framesTranscurridas++;
		if (framesTranscurridas == 3) {
			framesTranscurridas = 0;
			numeroDeFrame++;
		}
		if (!frameCambiada) {
			cambiarFrame();
		}
		return (this);
	} else {
		delete this;
		return (new EstadoJugadorParado());
	}
}

EstadoJugador* EstadoJugadorPateando::saltar() {
	return pegar();
}

void EstadoJugadorPateando::cambiarFrame() {
	frameCambiada = true;
	frameActual.modificar(ancho, 320, ancho, alto);
}

int EstadoJugadorPateando::obtenerElevacion() {
	return elevacion;
}

EstadoJugadorPateando::~EstadoJugadorPateando() {}


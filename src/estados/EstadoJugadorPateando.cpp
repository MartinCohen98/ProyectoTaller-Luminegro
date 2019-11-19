#include "EstadoJugadorPateando.h"

EstadoJugadorPateando::EstadoJugadorPateando(int elNumeroDeFrame,
					int lasFramesTranscurridas, int laElevacion, tipoDeArma tipoArma) {
	alto = 100;
	ancho = 80;
	arma = tipoArma;
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
		return (new EstadoJugadorParado(arma));
	}
}

EstadoJugador* EstadoJugadorPateando::saltar() {
	return pegar();
}

EstadoJugador* EstadoJugadorPateando::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorPateando::acuchillar(){
    return pegar();
}

EstadoJugador* EstadoJugadorPateando::apalear(){
    return pegar();
}

EstadoJugador* EstadoJugadorPateando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado(arma));
}

void EstadoJugadorPateando::cambiarFrame() {
	frameCambiada = true;
	frameActual.modificar(0, 320, ancho, alto);
}

int EstadoJugadorPateando::obtenerElevacion() {
	return elevacion;
}

bool EstadoJugadorPateando::estaSaltando() {
	return true;
}

EstadoJugadorPateando::~EstadoJugadorPateando() {}

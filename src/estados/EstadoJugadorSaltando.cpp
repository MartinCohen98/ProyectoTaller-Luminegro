#include "EstadoJugadorSaltando.h"

EstadoJugadorSaltando::EstadoJugadorSaltando(tipoDeArma tipoArma) {
	alto = 110;
	ancho = 60;
	arma=tipoArma;
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
	EstadoJugadorPateando* nuevoEstado = new EstadoJugadorPateando(numeroDeFrame,
			framesTranscurridas, elevacion, arma);
	delete this;
	return nuevoEstado;
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
		return (new EstadoJugadorParado(arma));
	}
}

EstadoJugador* EstadoJugadorSaltando::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorSaltando::acuchillar(){
    return saltar();
}

EstadoJugador* EstadoJugadorSaltando::apalear(){
    return saltar();
}

EstadoJugador* EstadoJugadorSaltando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado(arma));
}

int EstadoJugadorSaltando::obtenerElevacion() {
	return elevacion;
}

bool EstadoJugadorSaltando::estaSaltando() {
	return true;
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


#include "EstadoJugadorPegando.h"

EstadoJugadorPegando::EstadoJugadorPegando(tipoDeArma tipoArma) {
	alto = 100;
	ancho = 70;
	arma=tipoArma;
	frameActual.modificar(0, 410, ancho, alto);
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	golpeTerminado = false;
	frameDeDanio = true;
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

EstadoJugador* EstadoJugadorPegando::saltar() {
	return (pegar());
}

EstadoJugador* EstadoJugadorPegando::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorPegando::acuchillar(){
    return (pegar());
}

EstadoJugador* EstadoJugadorPegando::apalear(){
    return (pegar());
}

EstadoJugador* EstadoJugadorPegando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado(arma));
}

EstadoJugador* EstadoJugadorPegando::serGolpeado() {
	delete this;
	return (new EstadoJugadorGolpeado(arma));
}

bool EstadoJugadorPegando::puedeMoverse() {
	return false;
}


bool EstadoJugadorPegando::estaAtacando() {
	bool retorno = frameDeDanio;
	frameDeDanio = false;
	return retorno;
}


int EstadoJugadorPegando::obtenerDanio() {
	return 20;
}


int EstadoJugadorPegando::obtenerPuntosDeGolpe() {
	return 100;
}


bool EstadoJugadorPegando::terminado() {
	return ((numeroDeFrame == 0) && (framesTranscurridas == 1) && golpeTerminado);
}

void EstadoJugadorPegando::cambiarFrame() {
	if (numeroDeFrame == 1) {
		golpeTerminado = true;
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((70 * numeroDeFrame), 410, ancho, alto);
}

EstadoJugadorPegando::~EstadoJugadorPegando() {}


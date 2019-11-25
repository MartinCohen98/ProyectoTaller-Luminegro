#include "EstadoJugadorApaleando.h"

EstadoJugadorApaleando::EstadoJugadorApaleando(tipoDeArma tipoArma) {
    alto = 100;
    ancho = 90;
    arma=tipoArma;
    frameActual.modificar(0, 610, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    golpeTerminado = false;
    frameDeDanio = true;
}


EstadoJugador* EstadoJugadorApaleando::avanzar() {
    return (apalear());
}


EstadoJugador* EstadoJugadorApaleando::parar() {
    return (apalear());
}


EstadoJugador* EstadoJugadorApaleando::agacharse() {
    return (apalear());
}


EstadoJugador* EstadoJugadorApaleando::pegar() {
    return (apalear());
}


EstadoJugador* EstadoJugadorApaleando::saltar() {
    return (apalear());
}


EstadoJugador* EstadoJugadorApaleando::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}


EstadoJugador* EstadoJugadorApaleando::acuchillar(){
    return (apalear());
}


EstadoJugador* EstadoJugadorApaleando::apalear(){
    if (!terminado()) {
        framesTranscurridas++;
        if (framesTranscurridas == 2) {
            framesTranscurridas = 0;
            cambiarFrame();
        }
        return (this);
    } else {
        delete this;
        return (new EstadoJugadorParado(arma));
    }
}


EstadoJugador* EstadoJugadorApaleando::serGolpeado() {
	delete this;
	return (new EstadoJugadorGolpeado());
}


EstadoJugador* EstadoJugadorApaleando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado(arma));
}


bool EstadoJugadorApaleando::puedeMoverse() {
    return false;
}


bool EstadoJugadorApaleando::estaAtacando() {
	bool retorno = frameDeDanio;
	frameDeDanio = false;
	return retorno;
}


int EstadoJugadorApaleando::obtenerDanio() {
	return 35;
}


int EstadoJugadorApaleando::obtenerPuntosDeGolpe() {
	return 200;
}


bool EstadoJugadorApaleando::terminado() {
    return ((numeroDeFrame == 0) && (framesTranscurridas == 1) && golpeTerminado);
}

void EstadoJugadorApaleando::cambiarFrame() {
    if (numeroDeFrame == 1) {
        golpeTerminado = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((90 * numeroDeFrame), 610, ancho, alto);
}

EstadoJugadorApaleando::~EstadoJugadorApaleando() {}

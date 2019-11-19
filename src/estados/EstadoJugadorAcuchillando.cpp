//
// Created by julio on 12/11/19.
//

#include "EstadoJugadorAcuchillando.h"

EstadoJugadorAcuchillando::EstadoJugadorAcuchillando(tipoDeArma tipoArma) {
    alto = 100;
    ancho = 90;
    frameActual.modificar(0, 510, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    golpeTerminado = false;
    arma=tipoArma;
}

EstadoJugador* EstadoJugadorAcuchillando::avanzar() {
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::parar() {
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::agacharse() {
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::pegar() {
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::saltar() {
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorAcuchillando::acuchillar(){
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

EstadoJugador* EstadoJugadorAcuchillando::apalear(){
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado(arma));
}

bool EstadoJugadorAcuchillando::puedeMoverse() {
    return false;
}

bool EstadoJugadorAcuchillando::terminado() {
    return ((numeroDeFrame == 0) && (framesTranscurridas == 1) && golpeTerminado);
}

int EstadoJugadorAcuchillando::obtenerDanio() {
	return 50;
}

void EstadoJugadorAcuchillando::cambiarFrame() {
    if (numeroDeFrame == 1) {
        golpeTerminado = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((90 * numeroDeFrame), 510, ancho, alto);
}

EstadoJugadorAcuchillando::~EstadoJugadorAcuchillando() {}

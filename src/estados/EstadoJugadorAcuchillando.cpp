//
// Created by julio on 12/11/19.
//

#include "EstadoJugadorAcuchillando.h"

EstadoJugadorAcuchillando::EstadoJugadorAcuchillando() {
    alto = 100;
    ancho = 70;
    frameActual.modificar(0, 510, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    golpeTerminado = false;
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
    return (new EstadoEnemigoMuriendo());
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
        return (new EstadoJugadorParado());
    }
}

EstadoJugador* EstadoJugadorAcuchillando::apalear(){
    return (acuchillar());
}

EstadoJugador* EstadoJugadorAcuchillando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado());
}

bool EstadoJugadorAcuchillando::puedeMoverse() {
    return false;
}

bool EstadoJugadorAcuchillando::terminado() {
    return ((numeroDeFrame == 0) && (framesTranscurridas == 1) && golpeTerminado);
}

void EstadoJugadorAcuchillando::cambiarFrame() {
    if (numeroDeFrame == 1) {
        golpeTerminado = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((70 * numeroDeFrame), 510, ancho, alto);
}

EstadoJugadorAcuchillando::~EstadoJugadorAcuchillando() {}
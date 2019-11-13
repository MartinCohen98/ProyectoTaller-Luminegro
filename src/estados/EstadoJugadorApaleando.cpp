//
// Created by julio on 12/11/19.
//

#include "EstadoJugadorApaleando.h"

EstadoJugadorApaleando::EstadoJugadorApaleando() {
    alto = 100;
    ancho = 70;
    frameActual.modificar(0, 610, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    golpeTerminado = false;
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
    return (new EstadoEnemigoMuriendo());
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
        return (new EstadoJugadorParado());
    }
}

EstadoJugador* EstadoJugadorApaleando::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado());
}

bool EstadoJugadorApaleando::puedeMoverse() {
    return false;
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
    frameActual.modificar((70 * numeroDeFrame), 610, ancho, alto);
}

EstadoJugadorApaleando::~EstadoJugadorApaleando() {}
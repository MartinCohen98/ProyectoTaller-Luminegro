//
// Created by julio on 1/11/19.
//

#include "EstadoEnemigoPegando.h"

EstadoEnemigoPegando::EstadoEnemigoPegando() {
    ancho=47;
    alto=78;
    frameActual.modificar(0, 410, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    golpeTerminado = false;
}

EstadoJugador* EstadoEnemigoPegando::avanzar() {
    return (pegar());
}

EstadoJugador* EstadoEnemigoPegando::parar() {
    return (pegar());
}

EstadoJugador* EstadoEnemigoPegando::agacharse() {
    return (pegar());
}

EstadoJugador* EstadoEnemigoPegando::pegar() {
    if (!terminado()) {
        framesTranscurridas++;
        if (framesTranscurridas == 2) {
            framesTranscurridas = 0;
            cambiarFrame();
        }
        return (this);
    } else {
        delete this;
        return (new EstadoEnemigoParado());
    }
}

EstadoJugador* EstadoEnemigoPegando::saltar() {
    return (pegar());
}

bool EstadoEnemigoPegando::puedeMoverse() {
    return false;
}

bool EstadoEnemigoPegando::terminado() {
    return ((numeroDeFrame == 0) && (framesTranscurridas == 1) && golpeTerminado);
}

void EstadoEnemigoPegando::cambiarFrame() {
    if (numeroDeFrame == 1) {
        golpeTerminado = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((70 * numeroDeFrame), 410, ancho, alto);
}

EstadoEnemigoPegando::~EstadoEnemigoPegando() {}

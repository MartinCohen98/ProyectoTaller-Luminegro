//
// Created by julio on 1/11/19.
//

#include "EstadoEnemigoPegando.h"

EstadoEnemigoPegando::EstadoEnemigoPegando() {
    ancho=70;
    alto=78;
    frameActual.modificar(0, 82, ancho, alto);
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

EstadoJugador* EstadoEnemigoPegando::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo());
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
    frameActual.modificar((70 * numeroDeFrame), 82, ancho, alto);
}

EstadoEnemigoPegando::~EstadoEnemigoPegando() {}

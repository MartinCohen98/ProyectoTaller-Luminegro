//
// Created by julio on 10/11/19.
//

#include "EstadoEnemigoMuriendo.h"

EstadoEnemigoMuriendo::EstadoEnemigoMuriendo() {
    ancho=65;
    alto=78;
    frameActual.modificar(65, 164, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    caidaTerminada = false;
}

EstadoJugador* EstadoEnemigoMuriendo::avanzar() {
    return (morir());
}

EstadoJugador* EstadoEnemigoMuriendo::parar() {
    return (morir());
}

EstadoJugador* EstadoEnemigoMuriendo::pegar() {
    return (morir());
}

EstadoJugador* EstadoEnemigoMuriendo::morir() {
    if (!terminado()) {
       framesTranscurridas++;
       if (framesTranscurridas == 4) {
           framesTranscurridas = 0;
           cambiarFrame();
     }
    return (this);
    } else {
        delete this;
        return (new EstadoEnemigoParado());
    }
}

bool EstadoEnemigoMuriendo::terminado() {
    return ((numeroDeFrame == 0) && (framesTranscurridas == 3) && caidaTerminada);
}

void EstadoEnemigoMuriendo::cambiarFrame(){
    if (numeroDeFrame == 3) {
        caidaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar(((ancho * numeroDeFrame) + 65), 164, ancho, alto);

}

EstadoEnemigoMuriendo::~EstadoEnemigoMuriendo() {

}
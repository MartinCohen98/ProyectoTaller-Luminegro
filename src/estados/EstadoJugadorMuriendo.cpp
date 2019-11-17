//
// Created by julio on 10/11/19.
//

#include "EstadoJugadorMuriendo.h"


EstadoJugadorMuriendo::EstadoJugadorMuriendo(tipoDeArma tipoArma) {
    alto = 110;
    ancho = 60;
    arma=tipoArma;
    frameActual.modificar(0, 510, ancho, alto);
    numeroDeFrame = 0;
    framesTranscurridas = 0;
}

EstadoJugador* EstadoJugadorMuriendo::avanzar() {
    delete this;
    return (new EstadoJugadorAvanzando(arma));
}

EstadoJugador* EstadoJugadorMuriendo::parar() {
    delete this;
    return (new EstadoJugadorParado(arma));
}

EstadoJugador* EstadoJugadorMuriendo::pegar() {
    delete this;
    return (new EstadoJugadorPegando(arma));
}

EstadoJugador* EstadoJugadorMuriendo::morir() {
    framesTranscurridas++;
    if (framesTranscurridas == 4) {
        framesTranscurridas = 0;
        cambiarFrame();
    }
    return (this);
}

void EstadoJugadorMuriendo::cambiarFrame(){
    if (numeroDeFrame == 5) {
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame), 0, ancho, alto);

}

EstadoJugadorMuriendo::~EstadoJugadorMuriendo() {

}

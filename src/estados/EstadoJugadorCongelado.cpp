//
// Created by julio on 27/10/19.
//

#include "EstadoJugadorCongelado.h"

EstadoJugadorCongelado::EstadoJugadorCongelado() {
    alto=100;
    ancho=50;
    frameActual.modificar(150,100,ancho,alto);
    printf("Desconectado");
}

EstadoJugador* EstadoJugadorCongelado::parar() {
    return this;
}

EstadoJugador* EstadoJugadorCongelado::avanzar() {
    return this;
}

EstadoJugador* EstadoJugadorCongelado::agacharse() {
    return this;
}

EstadoJugador* EstadoJugadorCongelado::pegar() {
    delete this;
    return (new EstadoJugadorPegando());
}

EstadoJugador* EstadoJugadorCongelado::saltar() {
    delete this;
    return (new EstadoJugadorSaltando());
}


bool EstadoJugadorCongelado::puedeMoverse() {
    return true;
}

EstadoJugadorCongelado::~EstadoJugadorCongelado() {

}


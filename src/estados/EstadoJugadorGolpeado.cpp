/*
 * EstadoJugadorGolpeado.cpp
 *
 *  Created on: 18 nov. 2019
 *      Author: julio
 */

#include "EstadoJugadorGolpeado.h"

EstadoJugadorGolpeado::EstadoJugadorGolpeado() {
	// TODO Auto-generated constructor stub
	ancho=47;
   alto=78;
   frameActual.modificar(0, 0, ancho, alto);

}

EstadoJugador* EstadoJugadorGolpeado::avanzar() {
    return (serGolpeado());
}

EstadoJugador* EstadoJugadorGolpeado::parar() {
    return (serGolpeado());
}

EstadoJugador* EstadoJugadorGolpeado::serGolpeado() {
	int framesLimite=2;
    if (!terminado()) {
        framesTranscurridas++;
        if (framesTranscurridas == framesLimite) {
            framesTranscurridas = 0;
            cambiarFrame();
        }
        return (this);
    } else {
        delete this;
        return (new EstadoJugadorParado(arma));
    }
}

EstadoJugador* EstadoJugadorGolpeado::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

bool EstadoJugadorGolpeado::puedeMoverse() {
    return false;
}

bool EstadoJugadorGolpeado::terminado() {
	int framesLimite=1;
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && palizaTerminada);
}

void EstadoJugadorGolpeado::cambiarFrame() {
	int framesLimite=1;
    if (numeroDeFrame == framesLimite) {
        palizaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame), alto, ancho, alto);
}

EstadoJugadorGolpeado::~EstadoJugadorGolpeado() {
	// TODO Auto-generated destructor stub
}


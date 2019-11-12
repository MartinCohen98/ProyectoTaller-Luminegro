/*
 * EstadoEnemigoFrenado.cpp
 *
 *  Created on: 16 sep. 2019
 *      Author: julio
 */

#include "EstadoEnemigoParado.h"

EstadoEnemigoParado::EstadoEnemigoParado() {
    ancho=47;
    alto=78;
    frameActual.modificar(0, 0, ancho, alto);
}

EstadoJugador* EstadoEnemigoParado::parar() {
	return (this);
}

EstadoJugador* EstadoEnemigoParado::avanzar() {
	delete this;
	return (new EstadoEnemigoAvanzando());
}

EstadoJugador* EstadoEnemigoParado::pegar() {
    delete this;
    return (new EstadoEnemigoPegando());
}

EstadoJugador* EstadoEnemigoParado::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo());
}

EstadoEnemigoParado::~EstadoEnemigoParado() {
	// TODO Auto-generated destructor stub
}


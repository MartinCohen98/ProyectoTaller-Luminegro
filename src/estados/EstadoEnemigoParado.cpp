/*
 * EstadoEnemigoFrenado.cpp
 *
 *  Created on: 16 sep. 2019
 *      Author: julio
 */

#include "EstadoEnemigoParado.h"

EstadoEnemigoParado::EstadoEnemigoParado() {
    frameActual.modificar(0, 0, 47, 78);
}

EstadoEnemigoParado::EstadoEnemigoParado(int x, int y, int ancho, int alto) {
	frameActual.modificar(x,y,ancho,alto);
}

EstadoJugador* EstadoEnemigoParado::parar() {
	return (this);
}

EstadoJugador* EstadoEnemigoParado::avanzar() {
	delete this;
	return (new EstadoEnemigoAvanzando());
}

EstadoJugador* EstadoEnemigoParado::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}

EstadoEnemigoParado::~EstadoEnemigoParado() {
	// TODO Auto-generated destructor stub
}


/*
 * EstadoEnemigoFrenado.cpp
 *
 *  Created on: 16 sep. 2019
 *      Author: julio
 */

#include "EstadoEnemigoFrenado.h"


EstadoEnemigoFrenado::EstadoEnemigoFrenado(int x, int y, int ancho, int alto) {
	frameActual.modificar(x,y,ancho,alto);
}

EstadoJugador* EstadoEnemigoFrenado::parar() {
	return (this);
}

EstadoJugador* EstadoEnemigoFrenado::avanzar() {
	delete this;
	return (new EstadoEnemigoAvanzando());
}

EstadoJugador* EstadoEnemigoFrenado::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}


EstadoEnemigoFrenado::~EstadoEnemigoFrenado() {
	// TODO Auto-generated destructor stub
}


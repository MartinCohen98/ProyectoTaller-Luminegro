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

EstadoEnemigoParado::EstadoEnemigoParado(tipoDeSprite tipoNuevo){
	ancho=47;
	alto=78;
	tipo=tipoNuevo;
    switch (tipo){
    case EnemigoJefe:{
    	ancho=90;
    	alto=150;
     }
    }
	frameActual.modificar(0, 0, ancho, alto);
}

EstadoJugador* EstadoEnemigoParado::parar() {
	return (this);
}

EstadoJugador* EstadoEnemigoParado::avanzar() {
	delete this;
	return (new EstadoEnemigoAvanzando(tipo));
}

EstadoJugador* EstadoEnemigoParado::pegar() {
    delete this;
    return (new EstadoEnemigoPegando(tipo));
}

EstadoJugador* EstadoEnemigoParado::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}

bool EstadoEnemigoParado::puedeMoverse() {
    return true;
}

EstadoJugador* EstadoEnemigoParado::serGolpeado() {
	delete this;
	return (new EstadoEnemigoGolpeado(tipo));
}

EstadoEnemigoParado::~EstadoEnemigoParado() {
	// TODO Auto-generated destructor stub
}


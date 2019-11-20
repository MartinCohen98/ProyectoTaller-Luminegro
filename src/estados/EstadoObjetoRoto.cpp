/*
 * EstadoObjetoRoto.cpp
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#include "EstadoObjetoRoto.h"

EstadoObjetoRoto::EstadoObjetoRoto(tipoDeSprite tipoNuevo) {
	// TODO Auto-generated constructor stub
	tipo=tipoNuevo;
	switch (tipo){
		case Barril:{
			ancho = 150;
			alto = 300;
		  }
		case Caja:{
			ancho = 120;
			alto = 250;
		  }
		}
	frameActual.modificar(ancho, 0, ancho, alto);
	framesTranscurridas = 0;
	numeroDeFrame = 0;
    roturaTerminada = false;
}

EstadoObjeto* EstadoObjetoRoto::romperse(tipoDeSprite tipoNuevo) {
	int framesLimite=2;
	tipo = tipoNuevo;
    if (!terminado()) {
        framesTranscurridas++;
        if (framesTranscurridas == framesLimite) {
            framesTranscurridas = 0;
            cambiarFrame();
        }
        return (this);
    } else {
        delete this;
        return NULL;
    }
}

bool EstadoObjetoRoto::terminado() {
	return ((numeroDeFrame == 0) && (framesTranscurridas == 1) && roturaTerminada);
}

void EstadoObjetoRoto::cambiarFrame() {
	if (numeroDeFrame == 1) {
		roturaTerminada = true;
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((ancho * numeroDeFrame) + ancho, 0, ancho, alto);
}

EstadoObjetoRoto::~EstadoObjetoRoto() {
	// TODO Auto-generated destructor stub
}


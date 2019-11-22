#include "EstadoObjetoRoto.h"

EstadoObjetoRoto::EstadoObjetoRoto(tipoDeSprite tipoNuevo) {
	tipo = tipoNuevo;
	switch (tipo){
		case Barril:
			ancho = 80;
			alto = 170;
			break;
		case Caja:
			ancho = 105;
			alto = 170;
			break;
	}
	frameActual.modificar(ancho, 0, ancho, alto);
	framesTranscurridas = 0;
	numeroDeFrame = 0;
    roturaTerminada = false;
}

EstadoObjeto* EstadoObjetoRoto::romperse(tipoDeSprite tipoNuevo) {
	int framesLimite = 5;
	tipo = tipoNuevo;
    framesTranscurridas++;
    if (framesTranscurridas == framesLimite) {
    	framesTranscurridas = 0;
        cambiarFrame();
    }
    return (this);
}


bool EstadoObjetoRoto::terminado() {
	return roturaTerminada;
}


bool EstadoObjetoRoto::estaRoto() {
	return true;
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

EstadoObjetoRoto::~EstadoObjetoRoto() {}


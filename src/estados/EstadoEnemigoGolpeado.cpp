#include "EstadoEnemigoGolpeado.h"

EstadoEnemigoGolpeado::EstadoEnemigoGolpeado(tipoDeSprite tipoNuevo){

	tipo = tipoNuevo;

	switch (tipo){
	case EnemigoJefe:{
    	ancho = 90;
    	alto = 130;
    	frameActual.modificar(50, 270, ancho, alto);
    	break;
	}
	case Enemigo1:
	case Enemigo2:
	case Enemigo3:{
		ancho = 50;
		alto = 80;
		frameActual.modificar(60, 170, ancho, alto);
		break;
	}
	}
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	palizaTerminada = false;
}

EstadoJugador* EstadoEnemigoGolpeado::avanzar() {
    return (serGolpeado());
}

EstadoJugador* EstadoEnemigoGolpeado::parar() {
    return (serGolpeado());
}

EstadoJugador* EstadoEnemigoGolpeado::serGolpeado() {
	int framesLimite = 20;
    if (framesTranscurridas < framesLimite) {
        framesTranscurridas++;
        return (this);
    } else {
        delete this;
        return (new EstadoEnemigoParado(tipo));
    }
}

EstadoJugador* EstadoEnemigoGolpeado::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}


bool EstadoEnemigoGolpeado::puedeMoverse() {
    return false;
}


EstadoEnemigoGolpeado::~EstadoEnemigoGolpeado() {}


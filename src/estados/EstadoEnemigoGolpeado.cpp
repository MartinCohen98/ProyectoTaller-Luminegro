#include "EstadoEnemigoGolpeado.h"

EstadoEnemigoGolpeado::EstadoEnemigoGolpeado() {
	  ancho = 50;
	  alto = 80;
	  frameActual.modificar(60, 170, ancho, alto);
	  palizaTerminada = false;
	  framesTranscurridas = 0;
	  numeroDeFrame = 0;
}

EstadoEnemigoGolpeado::EstadoEnemigoGolpeado(tipoDeSprite tipoNuevo){
	ancho = 50;
	alto = 80;
	tipo = tipoNuevo;
	frameActual.modificar(60, 170, ancho, alto);
	if (tipo == EnemigoJefe){
    	ancho=115;
    	alto=125;
    	frameActual.modificar(0, 140, ancho, alto);
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


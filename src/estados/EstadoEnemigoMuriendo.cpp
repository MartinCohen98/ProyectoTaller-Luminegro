#include "EstadoEnemigoMuriendo.h"

EstadoEnemigoMuriendo::EstadoEnemigoMuriendo(tipoDeSprite tipoNuevo) {
    tipo = tipoNuevo;
	ancho = 105;
	alto = 80;
	frameActual.modificar(0, 170, ancho, alto);
    if (tipo == EnemigoJefe) {
       	  ancho = 135;
       	  alto = 130;
       	  frameActual.modificar(0, 270, ancho, alto);
	}
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    caidaTerminada = false;
}


EstadoJugador* EstadoEnemigoMuriendo::parar() {
    return (morir());
}


EstadoJugador* EstadoEnemigoMuriendo::avanzar() {
    return (morir());
}


EstadoJugador* EstadoEnemigoMuriendo::pegar() {
    return (morir());
}


EstadoJugador* EstadoEnemigoMuriendo::serGolpeado() {
	return (morir());
}


EstadoJugador* EstadoEnemigoMuriendo::morir() {
	int framesLimite = 4;
	if (tipo == EnemigoJefe) {
		framesLimite = 6;
	}
	if (!terminado()) {
    	framesTranscurridas++;
    	if (framesTranscurridas == framesLimite) {
    		framesTranscurridas = 0;
    		cambiarFrame();
    	}
	}
	return (this);
}


bool EstadoEnemigoMuriendo::puedeMoverse() {
    return false;
}


bool EstadoEnemigoMuriendo::terminado() {
	return caidaTerminada;
}


void EstadoEnemigoMuriendo::cambiarFrame() {
	int framesLimite = 3;
	if (tipo == EnemigoJefe) {
		framesLimite = 5;
	}
	if (numeroDeFrame == framesLimite) {
		numeroDeFrame = 10;
        caidaTerminada = true;
    } else {
        numeroDeFrame++;
    }
	frameActual.modificar((ancho * numeroDeFrame), 170, ancho, alto);
    if (tipo == EnemigoJefe) {
    	int posY = 270;
    	int corrimiento = 0;
    	if (framesLimite == 3) {
    		posY = 400;
    		corrimiento = 3;
    	}
    	frameActual.modificar((ancho * (numeroDeFrame - corrimiento)),
    							posY, ancho, alto);
	}
}


bool EstadoEnemigoMuriendo::estaMuerto(){
	return true;
}


EstadoEnemigoMuriendo::~EstadoEnemigoMuriendo() {}


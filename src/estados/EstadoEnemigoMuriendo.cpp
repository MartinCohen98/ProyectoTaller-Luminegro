#include "EstadoEnemigoMuriendo.h"

EstadoEnemigoMuriendo::EstadoEnemigoMuriendo(tipoDeSprite tipoNuevo) {
    tipo = tipoNuevo;
	ancho = 100;
	alto = 78;
	frameActual.modificar(30, 164, ancho, alto);
    if (tipo == EnemigoJefe) {
       	  ancho = 110;
       	  alto = 125;
       	  frameActual.modificar(115, 310, ancho, alto);
	}
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    caidaTerminada = false;
}

EstadoJugador* EstadoEnemigoMuriendo::avanzar() {
    return (morir(tipo));
}

EstadoJugador* EstadoEnemigoMuriendo::parar() {
    return (morir(tipo));
}

EstadoJugador* EstadoEnemigoMuriendo::pegar() {
    return (morir(tipo));
}

EstadoJugador* EstadoEnemigoMuriendo::serGolpeado() {
	return (morir(tipo));
}

EstadoJugador* EstadoEnemigoMuriendo::morir(tipoDeSprite tipoNuevo) {
	tipo = tipoNuevo;
	int framesLimite = 4;
	if (tipo == EnemigoJefe){
		framesLimite = 6;
	}
	if (!terminado()) {
    	framesTranscurridas++;
    	if (framesTranscurridas == framesLimite) {
    		framesTranscurridas = 0;
    		cambiarFrame();
    	}
    	return (this);
    } else {
        delete this;
        return (new EstadoEnemigoParado(tipo));
    }
}


bool EstadoEnemigoMuriendo::puedeMoverse() {
    return false;
}


bool EstadoEnemigoMuriendo::terminado() {
	int framesLimite = 3;
	if (tipo == EnemigoJefe) {
		framesLimite=5;
	}
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && caidaTerminada);
}

void EstadoEnemigoMuriendo::cambiarFrame(){
	int framesLimite = 3;
	if (tipo == EnemigoJefe) {
		framesLimite = 5;
	}
	if (numeroDeFrame == framesLimite) {
		numeroDeFrame = 0;
        caidaTerminada = true;
    } else {
        numeroDeFrame++;
    }
	frameActual.modificar(((ancho * numeroDeFrame) + 30), 164, ancho, alto);
    if (tipo == EnemigoJefe) {
    	frameActual.modificar((ancho * numeroDeFrame) + 115, 310, ancho, alto);
	}
}

bool EstadoEnemigoMuriendo::estaMuerto(){
	return true;
}

EstadoEnemigoMuriendo::~EstadoEnemigoMuriendo() {

}

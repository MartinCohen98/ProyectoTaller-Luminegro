#include "EstadoEnemigoMuriendo.h"

EstadoEnemigoMuriendo::EstadoEnemigoMuriendo() {
    ancho=100;
    alto=78;
    frameActual.modificar(65, 164, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    caidaTerminada = false;
}


EstadoEnemigoMuriendo::EstadoEnemigoMuriendo(tipoDeSprite tipoNuevo) {
    ancho=100;
    alto=78;
    tipo=tipoNuevo;
    frameActual.modificar(65, 164, ancho, alto);
    switch (tipo){
       case EnemigoJefe:{
       	ancho=115;
       	alto=125;
       	frameActual.modificar(65, 310, ancho, alto);
        }
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

EstadoJugador* EstadoEnemigoMuriendo::morir(tipoDeSprite tipoNuevo) {
	int framesLimite=4;
		tipo = tipoNuevo;
		switch (tipo){
	    case EnemigoJefe:{
	    	framesLimite=6;
	     }
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

EstadoJugador* EstadoEnemigoMuriendo::serGolpeado() {
	return (morir(tipo));
}

bool EstadoEnemigoMuriendo::terminado() {
	int framesLimite=3;
			switch (tipo){
		    case EnemigoJefe:{
		    	framesLimite=5;
		     }
			}
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && caidaTerminada);
}

void EstadoEnemigoMuriendo::cambiarFrame(){
	int framesLimite=3;
			switch (tipo){
			case EnemigoJefe:{
			   framesLimite=5;
			 }
		    }
	if (numeroDeFrame == framesLimite) {
        caidaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar(((ancho * numeroDeFrame) + 65), 164, ancho, alto);
    switch (tipo){
        		case EnemigoJefe:{
        			frameActual.modificar((ancho * numeroDeFrame) + 65, 310, ancho, alto);
        		 }
        	    }
}

bool EstadoEnemigoMuriendo::estaMuerto(){
	return true;
}

EstadoEnemigoMuriendo::~EstadoEnemigoMuriendo() {

}

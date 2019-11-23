#include "EstadoEnemigoMuriendo.h"

EstadoEnemigoMuriendo::EstadoEnemigoMuriendo(tipoDeSprite tipoNuevo) {

    tipo=tipoNuevo;
    switch (tipo){
       case EnemigoJefe:{
       	  ancho=115;
       	  alto=125;
       	  frameActual.modificar(65, 310, ancho, alto);
        }
       case Enemigo1:
       case Enemigo2:
       case Enemigo3:{
    	  ancho=100;
    	  alto=78;
    	  frameActual.modificar(50, 164, ancho, alto);
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
	tipo = tipoNuevo;
	int framesLimite;
	switch (tipo){
	    case EnemigoJefe:{
	    	framesLimite=6;
	    	break;
	     }
	    case Enemigo1:
	    case Enemigo2:
	    case Enemigo3:{
	    	framesLimite=4;
	    	break;
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
	int framesLimite;
	switch (tipo){
		  case EnemigoJefe:{
		    	framesLimite=5;
		    	break;
		       }
		  case Enemigo1:
		  case Enemigo2:
		  case Enemigo3:{
		    	framesLimite=3;
		    	break;
		       }
			}
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && caidaTerminada);
}

void EstadoEnemigoMuriendo::cambiarFrame(){
	int framesLimite;
	switch (tipo){
		case EnemigoJefe:{
			   framesLimite=5;
			   break;
			  }
		case Enemigo1:
		case Enemigo2:
		case Enemigo3:{
				framesLimite=3;
				break;
			  }
		    }
	if (numeroDeFrame == framesLimite) {
        caidaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }

    switch (tipo){
        		case EnemigoJefe:{
        			frameActual.modificar((ancho * numeroDeFrame) + 65, 310, ancho, alto);
        		    break;
        		}
        		case Enemigo1:
        		case Enemigo2:
        		case Enemigo3:{
        			frameActual.modificar(((ancho * numeroDeFrame) + 50), 164, ancho, alto);
        		    break;
        		}

        	    }
}

bool EstadoEnemigoMuriendo::estaMuerto(){
	return true;
}

EstadoEnemigoMuriendo::~EstadoEnemigoMuriendo() {

}

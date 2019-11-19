/*
 * EstadoEnemigoGolpeado.cpp
 *
 *  Created on: 18 nov. 2019
 *      Author: julio
 */

#include "EstadoEnemigoGolpeado.h"

EstadoEnemigoGolpeado::EstadoEnemigoGolpeado() {
	// TODO Auto-generated constructor stub
	  ancho=70;
	  alto=78;
	  frameActual.modificar(0, alto, ancho, alto);

}

EstadoEnemigoGolpeado::EstadoEnemigoGolpeado(tipoDeSprite tipoNuevo){
	ancho=70;
	alto=78;
	tipo=tipoNuevo;
	frameActual.modificar(0, alto, ancho, alto);
	switch (tipo){
    case EnemigoJefe:{
    	ancho=115;
    	alto=125;
    	frameActual.modificar(0, 140, ancho, alto);
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
	int framesLimite=2;
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

EstadoJugador* EstadoEnemigoGolpeado::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}

bool EstadoEnemigoGolpeado::puedeMoverse() {
    return false;
}

bool EstadoEnemigoGolpeado::terminado() {
	int framesLimite=1;
		switch (tipo){
	    case EnemigoJefe:{
	    	framesLimite=3;
	     }
		}
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && palizaTerminada);
}

void EstadoEnemigoGolpeado::cambiarFrame() {
	int framesLimite=1;
    if (numeroDeFrame == framesLimite) {
        palizaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame), (alto * numeroDeFrame) + alto, ancho, alto);
    switch (tipo){
    		case EnemigoJefe:{
    			frameActual.modificar((ancho * numeroDeFrame), 140, ancho, alto);
    		 }
    	    }
}


EstadoEnemigoGolpeado::~EstadoEnemigoGolpeado() {
	// TODO Auto-generated destructor stub
}


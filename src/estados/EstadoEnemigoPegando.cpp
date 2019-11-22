#include "EstadoEnemigoPegando.h"

EstadoEnemigoPegando::EstadoEnemigoPegando() {
    ancho=70;
    alto=78;
    frameActual.modificar(0, alto, ancho, alto);
    framesTranscurridas = 0;
    numeroDeFrame = 0;
    golpeTerminado = false;
}

EstadoEnemigoPegando::EstadoEnemigoPegando(tipoDeSprite tipoNuevo){
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
	golpeTerminado = false;
}

EstadoJugador* EstadoEnemigoPegando::avanzar() {
    return (pegar(tipo));
}

EstadoJugador* EstadoEnemigoPegando::parar() {
    return (pegar(tipo));
}

EstadoJugador* EstadoEnemigoPegando::pegar(tipoDeSprite tipoNuevo) {
	int framesLimite=2;
	tipo = tipoNuevo;
	switch (tipo){
    case EnemigoJefe:{
    	framesLimite=4;
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

EstadoJugador* EstadoEnemigoPegando::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}

EstadoJugador* EstadoEnemigoPegando::serGolpeado() {
	delete this;
	return (new EstadoEnemigoGolpeado(tipo));
}

bool EstadoEnemigoPegando::puedeMoverse() {
    return false;
}

bool EstadoEnemigoPegando::terminado() {
	int framesLimite=1;
		switch (tipo){
	    case EnemigoJefe:{
	    	framesLimite=3;
	     }
		}
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && golpeTerminado);
}

void EstadoEnemigoPegando::cambiarFrame() {
	int framesLimite=1;
	switch (tipo){
		case EnemigoJefe:{
		   framesLimite=3;
		 }
	    }
    if (numeroDeFrame == framesLimite) {
        golpeTerminado = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame), alto, ancho, alto);
    switch (tipo){
    		case EnemigoJefe:{
    			frameActual.modificar((ancho * numeroDeFrame), 140, ancho, alto);
    		 }
    	    }
}

EstadoEnemigoPegando::~EstadoEnemigoPegando() {}

#include "EstadoEnemigoAvanzando.h"

EstadoEnemigoAvanzando::EstadoEnemigoAvanzando() {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	ancho=47;
	alto=78;
	frameActual.modificar(0, 0, ancho, alto);
}

EstadoEnemigoAvanzando::EstadoEnemigoAvanzando(tipoDeSprite tipoNuevo){
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	tipo=tipoNuevo;
	ancho=47;
	alto=78;
	switch (tipo){
	    case EnemigoJefe:{
	    	ancho=90;
	    	alto=150;
	    }
	}
	frameActual.modificar(0, 0, ancho, alto);
}

EstadoJugador* EstadoEnemigoAvanzando::parar() {
	delete this;
	return (new EstadoEnemigoParado(tipo));
}

EstadoJugador* EstadoEnemigoAvanzando::avanzar() {
	framesTranscurridas++;
	if (framesTranscurridas == 2) {
		framesTranscurridas = 0;
		cambiarFrame();
	}
	return (this);
}

EstadoJugador* EstadoEnemigoAvanzando::pegar() {
    delete this;
    return (new EstadoEnemigoPegando(tipo));
}

EstadoJugador* EstadoEnemigoAvanzando::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}

EstadoJugador* EstadoEnemigoAvanzando::serGolpeado() {
	delete this;
	return (new EstadoEnemigoGolpeado(tipo));
}

void EstadoEnemigoAvanzando::cambiarFrame() {
	if (numeroDeFrame == 2) {
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((ancho * numeroDeFrame), 0, ancho, alto);
}

EstadoEnemigoAvanzando::~EstadoEnemigoAvanzando() {}


#include "EstadoEnemigoAvanzando.h"

EstadoEnemigoAvanzando::EstadoEnemigoAvanzando() {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	frameActual.modificar(0, 0, ancho, alto);
}

EstadoEnemigoAvanzando::EstadoEnemigoAvanzando(int x, int y, int ancho, int alto) {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	ancho=47;
	alto=78;
	frameActual.modificar(x,y,ancho,alto);
}

EstadoJugador* EstadoEnemigoAvanzando::parar() {
	delete this;
	return (new EstadoEnemigoParado());
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
    return (new EstadoEnemigoPegando());
}

EstadoJugador* EstadoEnemigoAvanzando::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo());
}

void EstadoEnemigoAvanzando::cambiarFrame() {
	if (numeroDeFrame == 2) {
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((47 * numeroDeFrame), 0, 47, 78);
}

EstadoEnemigoAvanzando::~EstadoEnemigoAvanzando() {}


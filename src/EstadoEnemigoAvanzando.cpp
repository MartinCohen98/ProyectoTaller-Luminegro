#include "EstadoEnemigoAvanzando.h"

EstadoEnemigoAvanzando::EstadoEnemigoAvanzando() {
	// TODO Auto-generated constructor stub
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	frameActual.modificar(0, 0, 47, 78);
}

EstadoEnemigoAvanzando::EstadoEnemigoAvanzando(int x, int y, int ancho, int alto) {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	frameActual.modificar(x,y,ancho,alto);
}

EstadoJugador* EstadoEnemigoAvanzando::parar() {
	delete this;
	return (new EstadoJugadorParado());
}

EstadoJugador* EstadoEnemigoAvanzando::avanzar() {
	framesTranscurridas++;
	if (framesTranscurridas == 2) {
		framesTranscurridas = 0;
		cambiarFrame();
	}
	return (this);
}

EstadoJugador* EstadoEnemigoAvanzando::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}

void EstadoEnemigoAvanzando::cambiarFrame() {
	if (numeroDeFrame == 2) {
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((47 * numeroDeFrame), 0, 47, 78);
}

EstadoEnemigoAvanzando::~EstadoEnemigoAvanzando() {
	// TODO Auto-generated destructor stub
}


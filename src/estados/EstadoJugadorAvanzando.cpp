#include "EstadoJugadorAvanzando.h"

EstadoJugadorAvanzando::EstadoJugadorAvanzando() {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	alto = 100;
	ancho = 50;
	frameActual.modificar(0, 0, ancho, alto);
}

EstadoJugador* EstadoJugadorAvanzando::parar() {
	delete this;
	return (new EstadoJugadorParado());
}

EstadoJugador* EstadoJugadorAvanzando::avanzar() {
	framesTranscurridas++;
	if (framesTranscurridas == 4) {
		framesTranscurridas = 0;
		cambiarFrame();
	}
	return (this);
}

EstadoJugador* EstadoJugadorAvanzando::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado());
}

EstadoJugador* EstadoJugadorAvanzando::pegar() {
	delete this;
	return (new EstadoJugadorPegando());
}

EstadoJugador* EstadoJugadorAvanzando::saltar() {
	delete this;
	return (new EstadoJugadorSaltando());
}

EstadoJugador* EstadoJugadorAvanzando::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo());
}

EstadoJugador* EstadoJugadorAvanzando::congelarse() {
    delete this;
   // printf("Desconectado");
    return (new EstadoJugadorCongelado());
}

void EstadoJugadorAvanzando::cambiarFrame() {
	if (numeroDeFrame == 5) {
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((ancho * numeroDeFrame), 0, ancho, alto);
}

EstadoJugadorAvanzando::~EstadoJugadorAvanzando() {}


#include "EstadoEnemigoPegando.h"

EstadoEnemigoPegando::EstadoEnemigoPegando(tipoDeSprite tipoNuevo) {
	tipo = tipoNuevo;
	ancho = 70;
	alto = 80;
	frameActual.modificar(0, alto, ancho, alto);
	if (tipo == EnemigoJefe) {
		ancho = 115;
		alto = 125;
		frameActual.modificar(0, 140, ancho, alto);
	}
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	golpeTerminado = false;
	frameDeDanio = true;
}


EstadoJugador* EstadoEnemigoPegando::parar() {
	return (pegar());
}


EstadoJugador* EstadoEnemigoPegando::avanzar() {
	return (pegar());
}


EstadoJugador* EstadoEnemigoPegando::pegar() {
	int framesLimite = 5;
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


EstadoJugador* EstadoEnemigoPegando::morir() {
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
	int framesLimite = 1;
	if (tipo == EnemigoJefe) {
		framesLimite = 3;
	}
	return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite)
			&& golpeTerminado);
}


bool EstadoEnemigoPegando::estaAtacando() {
	bool retorno = frameDeDanio;
	frameDeDanio = false;
	return retorno;
}


int EstadoEnemigoPegando::obtenerDanio() {
	return 20;
}


void EstadoEnemigoPegando::cambiarFrame() {
	int framesLimite = 1;
	if (tipo == EnemigoJefe) {
		framesLimite = 3;
	}
	if (numeroDeFrame == framesLimite) {
		golpeTerminado = true;
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((ancho * numeroDeFrame), alto, ancho, alto);
	if (tipo == EnemigoJefe) {
		frameActual.modificar((ancho * numeroDeFrame), 140, ancho, alto);
	}
}


EstadoEnemigoPegando::~EstadoEnemigoPegando() {}


#include "EstadoEnemigoPegando.h"

EstadoEnemigoPegando::EstadoEnemigoPegando(tipoDeSprite tipoNuevo) {

	tipo = tipoNuevo;

	switch (tipo) {
	case EnemigoJefe: {
		ancho = 115;
		alto = 125;
		frameActual.modificar(0, 140, ancho, alto);
	}
	case Enemigo1:
	case Enemigo2:
	case Enemigo3: {
		ancho = 70;
		alto = 80;
		frameActual.modificar(0, alto, ancho, alto);
	}
	}

	framesTranscurridas = 0;
	numeroDeFrame = 0;
	golpeTerminado = false;
	frameDeDanio = true;
}

EstadoJugador* EstadoEnemigoPegando::avanzar() {
	return (pegar());
}


EstadoJugador* EstadoEnemigoPegando::parar() {
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
	int framesLimite;
	switch (tipo) {
	case EnemigoJefe: {
		framesLimite = 3;
		break;
	}
	case Enemigo1:
	case Enemigo2:
	case Enemigo3: {
		framesLimite = 1;
		break;
	}
	}
	return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite)
			&& golpeTerminado);
}


void EstadoEnemigoPegando::cambiarFrame() {
	int framesLimite = 1;
	switch (tipo) {
	case EnemigoJefe: {
		framesLimite = 3;
		break;
	}
	case Enemigo1:
	case Enemigo2:
	case Enemigo3: {
		framesLimite = 1;
		break;
	}
	}
	if (numeroDeFrame == framesLimite) {
		golpeTerminado = true;
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}

	switch (tipo) {
		case EnemigoJefe: {
			frameActual.modificar((ancho * numeroDeFrame), 140, ancho, alto);
			break;
		}
		case Enemigo1:
		case Enemigo2:
		case Enemigo3: {
			frameActual.modificar((ancho * numeroDeFrame), alto, ancho, alto);
		}
	}
}

bool EstadoEnemigoPegando::estaAtacando() {
	bool retorno = frameDeDanio;
	frameDeDanio = false;
	return retorno;
}

int EstadoEnemigoPegando::obtenerDanio() {
	return 20;
}

EstadoEnemigoPegando::~EstadoEnemigoPegando() {}

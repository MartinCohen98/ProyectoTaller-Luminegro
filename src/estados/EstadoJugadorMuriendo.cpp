#include "EstadoJugadorMuriendo.h"


EstadoJugadorMuriendo::EstadoJugadorMuriendo(tipoDeArma tipoArma) {
    alto = 100;
    ancho = 80;
    arma=tipoArma;
    frameActual.modificar(35, 910, ancho, alto);
    numeroDeFrame = 0;
    framesTranscurridas = 0;
    caidaTerminada=false;
}

EstadoJugador* EstadoJugadorMuriendo::avanzar() {
    return (morir());
}

EstadoJugador* EstadoJugadorMuriendo::parar() {
	return (morir());
}


EstadoJugador* EstadoJugadorMuriendo::pegar() {
	return (morir());
}


bool EstadoJugadorMuriendo::estaAtacando(){
	return false;
}


EstadoJugador* EstadoJugadorMuriendo::morir() {
	if (!terminado()) {
		framesTranscurridas++;
		if (framesTranscurridas == 4) {
			framesTranscurridas = 0;
			cambiarFrame();
		}
		return (this);
	} else {
		delete this;
		return (new EstadoJugadorParado(arma));
	}
}


EstadoJugador* EstadoJugadorMuriendo::agacharse() {
	return morir();
}


EstadoJugador* EstadoJugadorMuriendo::acuchillar() {
	return morir();
}


EstadoJugador* EstadoJugadorMuriendo::apalear() {
	return morir();
}


EstadoJugador* EstadoJugadorMuriendo::saltar() {
	return morir();
}


EstadoJugador* EstadoJugadorMuriendo::congelarse() {
	delete this;
	return (new EstadoJugadorCongelado(arma));
}


bool EstadoJugadorMuriendo::terminado() {
	int framesLimite=3;
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && caidaTerminada);
}

void EstadoJugadorMuriendo::cambiarFrame(){
    if (numeroDeFrame == 3) {
        numeroDeFrame = 0;
        caidaTerminada = true;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame) + 35, 910, ancho, alto);
}

EstadoJugadorMuriendo::~EstadoJugadorMuriendo() {

}

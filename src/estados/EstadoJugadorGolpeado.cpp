#include "EstadoJugadorGolpeado.h"

EstadoJugadorGolpeado::EstadoJugadorGolpeado() {
	ancho = 70;
	alto = 100;
	frameActual.modificar(40, 910, ancho, alto);
	palizaTerminada = false;
	numeroDeFrame = 0;
	framesTranscurridas = 0;
}


EstadoJugador* EstadoJugadorGolpeado::avanzar() {
    return (serGolpeado());
}


EstadoJugador* EstadoJugadorGolpeado::parar() {
    return (serGolpeado());
}


bool EstadoJugadorGolpeado::estaAtacando(){
	return false;
}


EstadoJugador* EstadoJugadorGolpeado::serGolpeado() {
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
        return (new EstadoJugadorParado(arma));
    }
}


EstadoJugador* EstadoJugadorGolpeado::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}


EstadoJugador* EstadoJugadorGolpeado::agacharse() {
	return (serGolpeado());
}


EstadoJugador* EstadoJugadorGolpeado::acuchillar() {
	return (serGolpeado());
}


EstadoJugador* EstadoJugadorGolpeado::apalear() {
	return (serGolpeado());
}


EstadoJugador* EstadoJugadorGolpeado::saltar() {
	return (serGolpeado());
}


EstadoJugador* EstadoJugadorGolpeado::congelarse() {
	delete this;
	return (new EstadoJugadorCongelado(arma));
}



bool EstadoJugadorGolpeado::puedeMoverse() {
    return false;
}


bool EstadoJugadorGolpeado::terminado() {
	int framesLimite=1;
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && palizaTerminada);
}


void EstadoJugadorGolpeado::cambiarFrame() {
	int framesLimite = 1;
    if (numeroDeFrame == framesLimite) {
        palizaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame) + 40, 910, ancho, alto);
}


EstadoJugadorGolpeado::~EstadoJugadorGolpeado() {}


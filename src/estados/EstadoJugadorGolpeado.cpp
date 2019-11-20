#include "EstadoJugadorGolpeado.h"

EstadoJugadorGolpeado::EstadoJugadorGolpeado() {
	ancho = 47;
	alto = 78;
	frameActual.modificar(0, 0, ancho, alto);
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

bool EstadoJugadorGolpeado::puedeMoverse() {
    return false;
}

bool EstadoJugadorGolpeado::terminado() {
	int framesLimite=1;
    return ((numeroDeFrame == 0) && (framesTranscurridas == framesLimite) && palizaTerminada);
}

void EstadoJugadorGolpeado::cambiarFrame() {
	int framesLimite=1;
    if (numeroDeFrame == framesLimite) {
        palizaTerminada = true;
        numeroDeFrame = 0;
    } else {
        numeroDeFrame++;
    }
    frameActual.modificar((ancho * numeroDeFrame), alto, ancho, alto);
}

EstadoJugadorGolpeado::~EstadoJugadorGolpeado() {}


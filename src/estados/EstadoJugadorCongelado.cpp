#include "EstadoJugadorCongelado.h"


EstadoJugadorCongelado::EstadoJugadorCongelado(tipoDeArma tipoArma) {
    alto=100;
    ancho=50;
    arma=tipoArma;
    frameActual.modificar(150,100,ancho,alto);
    printf("Desconectado");
}


EstadoJugador* EstadoJugadorCongelado::parar() {
    return this;
}


EstadoJugador* EstadoJugadorCongelado::avanzar() {
    return this;
}


EstadoJugador* EstadoJugadorCongelado::agacharse() {
    return this;
}


EstadoJugador* EstadoJugadorCongelado::pegar() {
    delete this;
    return (new EstadoJugadorPegando(arma));
}


EstadoJugador* EstadoJugadorCongelado::saltar() {
    delete this;
    return (new EstadoJugadorSaltando(arma));
}


EstadoJugador* EstadoJugadorCongelado::acuchillar() {
    delete this;
    return (new EstadoJugadorAcuchillando(arma));
}


EstadoJugador* EstadoJugadorCongelado::apalear() {
	delete this;
	return (new EstadoJugadorApaleando(arma));
}


EstadoJugador* EstadoJugadorCongelado::serGolpeado() {
	return this;
}


EstadoJugador* EstadoJugadorCongelado::morir() {
	return this;
}

EstadoJugador* EstadoJugadorCongelado::congelarse() {
	return this;
}


bool EstadoJugadorCongelado::estaAtacando(){
	return false;
}


bool EstadoJugadorCongelado::puedeMoverse() {
    return true;
}

EstadoJugadorCongelado::~EstadoJugadorCongelado() {}


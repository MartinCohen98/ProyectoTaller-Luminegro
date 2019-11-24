#include "EstadoJugadorAgachado.h"

EstadoJugadorAgachado::EstadoJugadorAgachado(tipoDeArma tipoArma) {
	alto = 100;
	ancho = 50;
	arma=tipoArma;
	frameActual.modificar(100, 100, ancho, alto);
}

EstadoJugador* EstadoJugadorAgachado::parar() {
	delete this;
	return (new EstadoJugadorParado(arma));
}

EstadoJugador* EstadoJugadorAgachado::avanzar() {
	return this;
}

EstadoJugador* EstadoJugadorAgachado::agacharse() {
	return this;
}

EstadoJugador* EstadoJugadorAgachado::pegar() {
	delete this;
	return (new EstadoJugadorPegando(arma));
}

EstadoJugador* EstadoJugadorAgachado::saltar() {
	delete this;
	return (new EstadoJugadorSaltando(arma));
}

EstadoJugador* EstadoJugadorAgachado::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorAgachado::acuchillar(){
    delete this;
    return (new EstadoJugadorAcuchillando(arma));
}

EstadoJugador* EstadoJugadorAgachado::apalear(){
    delete this;
    return (new EstadoJugadorApaleando(arma));
}

EstadoJugador* EstadoJugadorAgachado::congelarse() {
    delete this;
    return (new EstadoJugadorCongelado(arma));
}

bool EstadoJugadorAgachado::estaAtacando(){
	return false;
}

bool EstadoJugadorAgachado::puedeMoverse() {
	return false;
}

EstadoJugadorAgachado::~EstadoJugadorAgachado() {}


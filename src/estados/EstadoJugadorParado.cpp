#include "EstadoJugadorParado.h"

EstadoJugadorParado::EstadoJugadorParado(tipoDeArma tipoArma) {
	alto = 100;
	ancho = 50;
	arma=tipoArma;
	int posY;
	switch(arma){
	case desarmado:{
		posY=100;
		break;
 	 }
	case cuchillo:{
	   posY=710;
	   break;
	 }
	case tubo:{
	   posY=810;
	   break;
	 }
	}
	frameActual.modificar(0, posY, ancho, alto);
}

EstadoJugador* EstadoJugadorParado::parar() {
	return (this);
}

EstadoJugador* EstadoJugadorParado::avanzar() {
	delete this;
	return (new EstadoJugadorAvanzando(arma));
}

EstadoJugador* EstadoJugadorParado::agacharse() {
	delete this;
	return (new EstadoJugadorAgachado(arma));
}

EstadoJugador* EstadoJugadorParado::pegar() {
	delete this;
	return (new EstadoJugadorPegando(arma));
}

EstadoJugador* EstadoJugadorParado::saltar() {
	delete this;
	return (new EstadoJugadorSaltando(arma));
}

EstadoJugador* EstadoJugadorParado::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorParado::acuchillar(){
    delete this;
    return (new EstadoJugadorAcuchillando(arma));
}

EstadoJugador* EstadoJugadorParado::apalear(){
    delete this;
    return (new EstadoJugadorApaleando(arma));
}

EstadoJugador* EstadoJugadorParado::serGolpeado(){
	delete this;
	return (new EstadoJugadorGolpeado());
}

EstadoJugador* EstadoJugadorParado::congelarse() {
    delete this;
    printf("Desconectado");
    return (new EstadoJugadorCongelado(arma));
}

bool EstadoJugadorParado::estaAtacando(){
	return false;
}

EstadoJugadorParado::~EstadoJugadorParado() {}


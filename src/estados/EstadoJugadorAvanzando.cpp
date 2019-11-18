#include "EstadoJugadorAvanzando.h"

EstadoJugadorAvanzando::EstadoJugadorAvanzando(tipoDeArma tipoArma) {
	framesTranscurridas = 0;
	numeroDeFrame = 0;
	alto = 100;
	ancho = 50;
	arma=tipoArma;
		switch(arma){
		case desarmado:{
			posYframe=0;
			break;
	 	 }
		case cuchillo:{
			posYframe=710;
		   break;
		 }
		case tubo:{
			posYframe=810;
		   break;
		 }
		}
	frameActual.modificar(0, posYframe, ancho, alto);
}

EstadoJugador* EstadoJugadorAvanzando::parar() {
	delete this;
	return (new EstadoJugadorParado(arma));
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
	return (new EstadoJugadorAgachado(arma));
}

EstadoJugador* EstadoJugadorAvanzando::pegar() {
	delete this;
	return (new EstadoJugadorPegando(arma));
}

EstadoJugador* EstadoJugadorAvanzando::saltar() {
	delete this;
	return (new EstadoJugadorSaltando(arma));
}

EstadoJugador* EstadoJugadorAvanzando::morir(){
    delete this;
    return (new EstadoJugadorMuriendo(arma));
}

EstadoJugador* EstadoJugadorAvanzando::acuchillar(){
    delete this;
    return (new EstadoJugadorAcuchillando(arma));
}

EstadoJugador* EstadoJugadorAvanzando::apalear(){
    delete this;
    return (new EstadoJugadorApaleando(arma));
}

EstadoJugador* EstadoJugadorAvanzando::serGolpeado(){
	delete this;
	return (new EstadoJugadorGolpeado());
}

EstadoJugador* EstadoJugadorAvanzando::congelarse() {
    delete this;
   // printf("Desconectado");
    return (new EstadoJugadorCongelado(arma));
}

void EstadoJugadorAvanzando::cambiarFrame() {
	if (numeroDeFrame == 5) {
		numeroDeFrame = 0;
	} else {
		numeroDeFrame++;
	}
	frameActual.modificar((ancho * numeroDeFrame), posYframe, ancho, alto);
}

EstadoJugadorAvanzando::~EstadoJugadorAvanzando() {}


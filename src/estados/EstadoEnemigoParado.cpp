#include "EstadoEnemigoParado.h"

EstadoEnemigoParado::EstadoEnemigoParado(tipoDeSprite tipoNuevo) {
	tipo = tipoNuevo;
	ancho = 47;
	alto = 78;
	if (tipo == EnemigoJefe) {
		ancho = 90;
		alto = 150;
	}
	frameActual.modificar(0, 0, ancho, alto);
}


EstadoJugador* EstadoEnemigoParado::parar() {
	return (this);
}


EstadoJugador* EstadoEnemigoParado::avanzar() {
	delete this;
	return (new EstadoEnemigoAvanzando(tipo));
}


EstadoJugador* EstadoEnemigoParado::pegar() {
    delete this;
    return (new EstadoEnemigoPegando(tipo));
}


EstadoJugador* EstadoEnemigoParado::serGolpeado() {
	delete this;
	return (new EstadoEnemigoGolpeado(tipo));
}


EstadoJugador* EstadoEnemigoParado::morir() {
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}


bool EstadoEnemigoParado::puedeMoverse() {
    return true;
}


EstadoEnemigoParado::~EstadoEnemigoParado() {}


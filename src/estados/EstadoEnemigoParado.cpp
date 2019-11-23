#include "EstadoEnemigoParado.h"

EstadoEnemigoParado::EstadoEnemigoParado(tipoDeSprite tipoNuevo){

	tipo=tipoNuevo;
    switch (tipo){
    case EnemigoJefe:{
    	ancho=90;
    	alto=150;
    	break;
     }
    case Enemigo1:
    case Enemigo2:
     case Enemigo3:{
    	 ancho=47;
    	 alto=78;
    	 break;
     }
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

EstadoJugador* EstadoEnemigoParado::morir(){
    delete this;
    return (new EstadoEnemigoMuriendo(tipo));
}

bool EstadoEnemigoParado::puedeMoverse() {
    return true;
}

EstadoJugador* EstadoEnemigoParado::serGolpeado() {
	delete this;
	return (new EstadoEnemigoGolpeado(tipo));
}

EstadoEnemigoParado::~EstadoEnemigoParado() {}


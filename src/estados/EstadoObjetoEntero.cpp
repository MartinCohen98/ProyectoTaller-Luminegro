#include "EstadoObjetoEntero.h"

EstadoObjetoEntero::EstadoObjetoEntero(tipoDeSprite tipoNuevo) {
	tipo = tipoNuevo;
	switch (tipo){
	 case Barril:
		ancho = 80;
		alto = 170;
		break;
	 case Caja:
		ancho = 100;
		alto = 170;
		break;
	}
	frameActual.modificar(0, 0, ancho, alto);
}


EstadoObjeto* EstadoObjetoEntero::romperse(tipoDeSprite tipo){
	delete this;
	return (new EstadoObjetoRoto(tipo));
}


EstadoObjetoEntero::~EstadoObjetoEntero() {}


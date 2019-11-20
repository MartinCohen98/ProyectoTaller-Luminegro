/*
 * EstadoObjetoEntero.cpp
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#include "EstadoObjetoEntero.h"

EstadoObjetoEntero::EstadoObjetoEntero(tipoDeSprite tipoNuevo) {
	// TODO Auto-generated constructor stub
	tipo = tipoNuevo;
	switch (tipo){
	 case Barril:{
		ancho = 150;
		alto = 300;
	  }
	 case Caja:{
		ancho = 120;
		alto = 250;
	  }
	}
	frameActual.modificar(0, 0, ancho, alto);
}

EstadoObjetoRoto* EstadoObjetoEntero::romperse(){
	delete this;
	return (new EstadoObjetoRoto(tipo));
}

EstadoObjetoEntero::~EstadoObjetoEntero() {
	// TODO Auto-generated destructor stub
}


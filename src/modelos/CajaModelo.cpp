#include <iostream>
#include "CajaModelo.h"

CajaModelo::CajaModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 170;
	alto = 340;
	golpes = 2;
	sprite = Caja;
	tipo = Caja;
	estado = new EstadoObjetoEntero(Caja);
	encuadre.modificar(0, 0, 96, 169);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}


int CajaModelo::recibirDanioDe(Colisionable* colisionable) {
	golpes--;
	int puntos = 0;
	if (golpes == 0) {
		romperse();
		puntos = 200;
	}
	return puntos;
}

void CajaModelo::romperse(){
	estado = estado->romperse(sprite);
	actualizarInsercion();

	if (!comenzoARomperse) {
        ejecutarSonidoDestruccion = true;
        comenzoARomperse = true;
    }
}


void CajaModelo::actualizar() {
	if (estado->estaRoto()) {
		romperse();
		if (estado->terminado()) {
			desaparecer();
		}
	}
}


CajaModelo::~CajaModelo() {}


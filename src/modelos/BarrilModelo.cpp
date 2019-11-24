#include "BarrilModelo.h"

BarrilModelo::BarrilModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 150;
	alto = 300;
	golpes = 1;
	sprite = Barril;
	tipo = Barril;
    estado = new EstadoObjetoEntero(Barril);
	encuadre.modificar(0, 0, 80, 175);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}


int BarrilModelo::recibirDanioDe(Colisionable* colisionable) {
	golpes--;
	int puntos = 0;
	if (golpes == 0) {
		romperse();
		puntos = 300;
        ejecutarSonidoDestruccion = true;
	}
	return puntos;
}

void BarrilModelo::romperse(){
	estado = estado->romperse(sprite);
	actualizarInsercion();
}


void BarrilModelo::actualizar() {
	if (estado->estaRoto()) {
		romperse();
		if (estado->terminado()) {
			desaparecer();
		}
	}
}


BarrilModelo::~BarrilModelo() {}


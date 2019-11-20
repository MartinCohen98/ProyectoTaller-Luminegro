#include "CajaModelo.h"

CajaModelo::CajaModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 120;
	alto = 250;
	golpes = 2;
	sprite = Caja;
	estado = new EstadoObjetoEntero(Caja);
	encuadre.modificar(0, 0, 96, 169);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}


int CajaModelo::recibirDanioDe(Colisionable* colisionable) {
	golpes--;
	int puntos = 0;
	if (golpes == 0) {
		desaparecer();
		//romperse();
		puntos = 200;
	}
	return puntos;
}

void CajaModelo::romperse(){
	estado = estado->romperse();
}

CajaModelo::~CajaModelo() {}


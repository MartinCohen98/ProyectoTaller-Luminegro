#include "CajaModelo.h"

CajaModelo::CajaModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 120;
	alto = 250;
	golpes = 2;
	sprite = Caja;

	encuadre.modificar(0, 0, 96, 169);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}

CajaModelo::~CajaModelo() {}


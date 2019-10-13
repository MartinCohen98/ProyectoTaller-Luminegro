#include "CajaModelo.h"

CajaModelo::CajaModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 96;
	alto = 160;

	encuadre.modificar(0, 0, 96, 160);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}

CajaModelo::~CajaModelo() {}


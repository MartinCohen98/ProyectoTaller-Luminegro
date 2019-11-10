#include "CajaModelo.h"

CajaModelo::CajaModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 96;
	alto = 170;
	golpesResistidos=2;
	sprite = Caja;

	encuadre.modificar(0, 0, 96, 169);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}

CajaModelo::~CajaModelo() {}


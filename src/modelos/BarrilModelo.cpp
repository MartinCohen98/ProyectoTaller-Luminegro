#include "BarrilModelo.h"

BarrilModelo::BarrilModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 90;
	alto = 96;
	golpesResistidos=1;
	sprite = Barril;

	encuadre.modificar(0, 0, 30, 32);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}

BarrilModelo::~BarrilModelo() {}


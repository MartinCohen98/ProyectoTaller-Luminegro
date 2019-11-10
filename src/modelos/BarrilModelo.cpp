#include "BarrilModelo.h"

BarrilModelo::BarrilModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 100;
	alto = 200;
	golpesResistidos=1;
	sprite = Barril;

	encuadre.modificar(0, 0, 80, 175);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}

BarrilModelo::~BarrilModelo() {}


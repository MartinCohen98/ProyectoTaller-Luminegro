#include "ElementoModelo.h"

ElementoModelo::ElementoModelo() {
	posicionX = 0;
	posicionY = 0;
	ancho = 0;
	alto = 0;
}

void ElementoModelo::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX, posicionY, ancho, alto);
}

ElementoModelo::~ElementoModelo() {
	// TODO Auto-generated destructor stub
}

